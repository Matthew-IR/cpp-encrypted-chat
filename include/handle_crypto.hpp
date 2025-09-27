#pragma once
#include <cryptopp/dh.h>

class DHExchange {
    private:
        CryptoPP::DH dh;
    public:
        DHExchange();

        void generate_parameters();
};