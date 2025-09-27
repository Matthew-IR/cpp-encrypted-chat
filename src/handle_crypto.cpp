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
    CryptoPP::Integer p, q, g;
    CryptoPP::PrimeAndGenerator pg;

    // Should use 512, 512 but was generating slowly
    pg.Generate(1, prng, 1024, 160);
    p = pg.Prime();
    q = pg.SubPrime();
    g = pg.Generator();

    CryptoPP::DH dh(p, q, g);

    CryptoPP::SecByteBlock t1(dh.PrivateKeyLength()), t2(dh.PublicKeyLength());
    dh.GenerateKeyPair(prng, t1, t2);
    CryptoPP::Integer k1(t1.size()), k2(t2, t2.size());

    std::cout << "PrivK: " << k1 << std::endl;
    std::cout << "PubK: " << k2 << std::endl;
};