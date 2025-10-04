#include "handle_crypto.hpp"
#include <cryptopp/dh.h>

#include "cryptopp/nbtheory.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"

#include <iostream>

DHExchange::DHExchange() {};

std::string DHExchange::convert_integer_to_hex(const CryptoPP::Integer& num) {
    std::string encoded;

    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(encoded));

    num.Encode(encoder, num.MinEncodedSize() );

    return encoded;

};

CryptoPP::Integer DHExchange::convert_hex_to_integer(const std::string& hexStr) {
    CryptoPP::Integer num(("0x" + hexStr).c_str());
    return num;
};

void DHExchange::generate_parameters() {


    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::PrimeAndGenerator pg;

    // Should use 512, 512 but was generating slowly
    pg.Generate(1, prng, 1024, 160);
    p = pg.Prime();
    q = pg.SubPrime();
    g = pg.Generator();

    CryptoPP::DH dh(p, q, g);

    public_key.resize(dh.PublicKeyLength());
    private_key.resize(dh.PrivateKeyLength());

    dh.GenerateKeyPair(prng, private_key, public_key);

    // Testing with integer representation
    // CryptoPP::Integer k1(public_key, public_key.size());
    // CryptoPP::Integer k2(private_key, private_key.size());

};

void DHExchange::set_parameters(const CryptoPP::Integer& prime, const CryptoPP::Integer& generator) {
    p = prime;
    g = generator;

    dh.AccessGroupParameters().Initialize(p, g);
};