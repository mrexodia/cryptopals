#pragma once

#include <vector>

inline std::vector<unsigned char> RepeatingXorCipher(const std::vector<unsigned char> & data, const std::vector<unsigned char> & key)
{
    auto result = data;
    for (size_t i = 0, j = 0; i < result.size(); i++, j++)
    {
        if (j == key.size())
            j = 0;
        result[i] ^= key[j];
    }
    return std::move(result);
}