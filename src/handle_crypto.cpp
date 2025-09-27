#include "handle_crypto.hpp"
#include <cryptopp/dh.h>

#include "cryptopp/nbtheory.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"

#include <iostream>

DHExchange::DHExchange() {};

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