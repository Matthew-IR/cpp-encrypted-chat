#include "handle_crypto.hpp"
#include <cryptopp/dh.h>

#include "cryptopp/nbtheory.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
#include <cryptopp/files.h>
#include <cryptopp/secblock.h>

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

std::string DHExchange::convert_key_to_hex(const CryptoPP::SecByteBlock& key) {
    std::string encoded_hex;

    // Create a pipeline to encode the key data into hex
    CryptoPP::StringSource ss(key.data(), key.size(), true,
            new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded_hex))
    );

    return encoded_hex;
};

CryptoPP::SecByteBlock DHExchange::convert_hex_to_key(const std::string& hexStr) {
    // SecByteBlockSink is deprecated, use ArraySink
    CryptoPP::SecByteBlock key(hexStr.length() / 2);
    CryptoPP::StringSource ss(hexStr, true,
        new CryptoPP::HexDecoder(new CryptoPP::ArraySink(key, key.size()))
    );
    return key;
};

void DHExchange::generate_parameters() {


    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::PrimeAndGenerator pg;

    // Should use 512, 512 but was generating slowly
    pg.Generate(1, prng, 1024, 160);
    p = pg.Prime();
    q = pg.SubPrime();
    g = pg.Generator();

    dh.AccessGroupParameters().Initialize(p, q, g);

    public_key.resize(dh.PublicKeyLength());
    private_key.resize(dh.PrivateKeyLength());

    dh.GenerateKeyPair(prng, private_key, public_key);

    // Testing with integer representation
    // CryptoPP::Integer k1(public_key, public_key.size());
    // CryptoPP::Integer k2(private_key, private_key.size());

};

void DHExchange::generate_keys() {
    public_key.New(dh.PublicKeyLength());
    private_key.New(dh.PrivateKeyLength());
    dh.GenerateKeyPair(rng, private_key, public_key);
};

void DHExchange::set_parameters(const CryptoPP::Integer& prime, const CryptoPP::Integer& generator) {
    p = prime;
    g = generator;

    dh.AccessGroupParameters().Initialize(p, g);
};

void DHExchange::generate_shared_secret(const CryptoPP::SecByteBlock& other_public_key) {
    shared_secret.New(dh.AgreedValueLength());
    if (!dh.Agree(shared_secret, private_key, other_public_key)) {
        throw std::runtime_error("Failed shared secret.");
    }
};

void DHExchange::derive_aes_key() {
        CryptoPP::SecByteBlock derived_key;
        derived_key.New(32); // 256 bit key
        CryptoPP::SHA256 hash;
        hash.Update(shared_secret, shared_secret.size());
        hash.TruncatedFinal(derived_key, derived_key.size());
        aes_key = derived_key;
};