#pragma once

#include "aes.h"
#include "../challenge_1_6/challenge_1_6.h"

inline bool DecryptAesEcb(const std::vector<unsigned char> & data, const std::vector<unsigned char> & key, std::vector<unsigned char> & out)
{
    if (key.size() != 16)
        return false;
    
    out.reserve(data.size());

    WORD aeskey[60];
    std::vector<unsigned char> aesin, aesout;
    aesout.resize(AES_BLOCK_SIZE);
    const auto aeskeysize = 128;
    aes_key_setup(key.data(), aeskey, aeskeysize);

    auto blocks = data.size() / AES_BLOCK_SIZE;
    for (size_t i = 0; i < blocks; i++)
    {
        if (!TakeBytes(data, i * AES_BLOCK_SIZE, AES_BLOCK_SIZE, aesin))
        {
            puts("TakeBytes failed...");
            return false;
        }
        aes_decrypt(aesin.data(), aesout.data(), aeskey, aeskeysize);
        for (size_t j = 0; j < aesout.size(); j++)
            out.push_back(aesout[j]);
    }

    return true;
}

inline void RemovePKCS7Padding(std::vector<unsigned char> & plaintext, int blocksize = AES_BLOCK_SIZE)
{
    if (!plaintext.size())
        return;
    auto padsize = plaintext[plaintext.size() - 1];
    if (padsize >= blocksize)
        return;
    for (size_t i = 0; i < padsize; i++)
        if (plaintext[plaintext.size() - 1 - i] != padsize)
            return;
    plaintext.resize(plaintext.size() - padsize);
}