#pragma once
#include <cryptopp/dh.h>
#include <cryptopp/osrng.h>

class DHExchange {
    private:
        CryptoPP::DH dh;
        CryptoPP::Integer p;
        CryptoPP::Integer q;
        CryptoPP::Integer g;
        CryptoPP::SecByteBlock public_key;
        CryptoPP::SecByteBlock private_key;
        CryptoPP::AutoSeededRandomPool rng;
        CryptoPP::SecByteBlock shared_secret;
        CryptoPP::SecByteBlock aes_key;
    public:
        DHExchange();

        std::string convert_integer_to_hex(const CryptoPP::Integer& num);
        CryptoPP::Integer convert_hex_to_integer(const std::string& hexStr);

        std::string convert_key_to_hex(const CryptoPP::SecByteBlock& key);
        CryptoPP::SecByteBlock convert_hex_to_key(const std::string& hexStr);

        void generate_parameters();

        void set_parameters(const CryptoPP::Integer& prime, const CryptoPP::Integer& generator);

        void generate_keys();

        void generate_shared_secret(const CryptoPP::SecByteBlock& other_public_key);

        void derive_aes_key();

        std::string encrypt(const std::string& plaintext);
        std::string decrypt(const std::string& ciphertext);

        const CryptoPP::Integer& get_p() const {return p;};
        const CryptoPP::Integer& get_q() const {return q;};
        const CryptoPP::Integer& get_g() const {return g;};
        const CryptoPP::SecByteBlock& get_public_key() const {return public_key;};
        const CryptoPP::SecByteBlock& get_private_key() const {return private_key;};
        const CryptoPP::SecByteBlock& get_shared_secret() const {return shared_secret;};
        const CryptoPP::SecByteBlock& get_aes_key() const {return aes_key;};
};