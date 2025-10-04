#pragma once
#include <cryptopp/dh.h>

class DHExchange {
    private:
        CryptoPP::DH dh;
        CryptoPP::Integer p;
        CryptoPP::Integer q;
        CryptoPP::Integer g;
        CryptoPP::SecByteBlock public_key;
        CryptoPP::SecByteBlock private_key;
    public:
        DHExchange();

        std::string convert_integer_to_hex(const CryptoPP::Integer& num);
        CryptoPP::Integer convert_hex_to_integer(const std::string& hexStr);

        void generate_parameters();

        void set_parameters(const CryptoPP::Integer& prime, const CryptoPP::Integer& generator);

        const CryptoPP::Integer& get_p() const {return p;};
        const CryptoPP::Integer& get_q() const {return q;};
        const CryptoPP::Integer& get_g() const {return g;};
        const CryptoPP::SecByteBlock& get_public_key() const {return public_key;};
        const CryptoPP::SecByteBlock& get_private_key() const {return private_key;};
};