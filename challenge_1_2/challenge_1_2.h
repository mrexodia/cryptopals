#pragma once

#include <string>
#include <vector>
#include <cstdint>

inline bool EqualXor(const std::vector<unsigned char> & data1, const std::vector<unsigned char> & data2, std::vector<unsigned char> & out)
{
    if (data1.size() != data2.size())
        return false;
    out = data1;
    for (size_t i = 0; i < out.size(); i++)
        out[i] ^= data2[i];
    return true;
}