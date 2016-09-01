#pragma once

#include <string>
#include <vector>
#include <cstdint>

static int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

inline std::string ToHex(const std::vector<unsigned char> & data)
{
    std::string result;
    auto size = data.size();
    result.resize(size * 2);
    auto hextable = "0123456789abcdef";
    for (size_t i = 0, j = 0; i < size; i++, j += 2)
    {
        auto high = data[i] >> 4 & 0xF;
        auto low = data[i] & 0xF;
        result[j] = hextable[high];
        result[j + 1] = hextable[low];
    }
    return std::move(result);
}

inline bool FromHex(const std::string & hex, std::vector<unsigned char> & out)
{
    auto length = hex.length();
    if (length % 2)
        return false;
    out.resize(length / 2);
    for (size_t i = 0, j = 0; i < length; i += 2, j++)
    {
        auto high = hex2int(hex[i]);
        auto low = hex2int(hex[i + 1]);
        if (high == -1 || low == -1)
            return false;
        out[j] = high << 4 | low;
    }
    return true;
}

//Implemented from https://en.wikipedia.org/wiki/Base64
inline std::string ToBase64(const std::vector<unsigned char> & data)
{
    std::string result = "";
    auto base64table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    auto size = data.size();
    auto padsize = size % 3;
    size_t i;
    for (i = 0; i < size - padsize; i += 3)
    {
        uint32_t joined = data[i] << 16 | data[i + 1] << 8 | data[i + 2];
        //printf("joined: %X\n", joined);
        auto group1 = joined >> 18 & 0x3F;
        auto group2 = joined >> 12 & 0x3F;
        auto group3 = joined >> 6 & 0x3F;
        auto group4 = joined & 0x3F;
        //printf("group1: %u, group2: %u, group3: %u, group4: %u\n", group1, group2, group3, group4);
        result.push_back(base64table[group1]);
        result.push_back(base64table[group2]);
        result.push_back(base64table[group3]);
        result.push_back(base64table[group4]);
    }
    if (padsize == 2)
    {
        uint32_t joined = data[i] << 16 | data[i + 1] << 8;
        //printf("joined: %X\n", joined);
        auto group1 = joined >> 18 & 0x3F;
        auto group2 = joined >> 12 & 0x3F;
        auto group3 = joined >> 6 & 0x3F;
        //printf("group1: %u, group2: %u, group3: %u\n", group1, group2, group3);
        result.push_back(base64table[group1]);
        result.push_back(base64table[group2]);
        result.push_back(base64table[group3]);
        result.push_back('=');
    }
    else if (padsize == 1)
    {
        uint32_t joined = data[i] << 16;
        //printf("joined: %X\n", joined);
        auto group1 = joined >> 18 & 0x3F;
        auto group2 = joined >> 12 & 0x3F;
        //printf("group1: %u, group2: %u\n", group1, group2);
        result.push_back(base64table[group1]);
        result.push_back(base64table[group2]);
        result.push_back('=');
        result.push_back('=');
    }
    return std::move(result);
}

inline bool FromBase64(const std::string & base64, std::vector<unsigned char> & out)
{
    auto length = base64.length();
    if (length % 4)
        return false;
    out.clear();
    std::string base64table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    for (size_t i = 0; i < length; i += 4)
    {
        auto group1 = base64table.find(base64[i]);
        auto group2 = base64table.find(base64[i + 1]);
        auto group3 = base64table.find(base64[i + 2]);
        auto group4 = base64table.find(base64[i + 3]);
        if (group1 == std::string::npos || group2 == std::string::npos || group3 == std::string::npos || group4 == std::string::npos)
            return false;

        auto joined = group1 << 18 | group2 << 12;
        size_t blocksize = 3;
        if (base64table[group3] == '=' && base64table[group4] == '=') //1 byte
            blocksize = 1;
        else if (base64table[group4] == '=') //2 bytes
        {
            joined |= group3 << 6;
            blocksize = 2;
        }
        else //3 bytes
            joined |= group3 << 6 | group4;
        //printf("joined: %X, blocksize: %d\n", joined, blocksize);

        unsigned char bytes[3] = { joined >> 16 & 0xFF, joined >> 8 & 0xFF, joined & 0xFF };
        for (size_t j = 0; j < blocksize; j++)
            out.push_back(bytes[j]);
    }
    return true;
}

inline std::vector<unsigned char> StringToVector(const std::string & str)
{
    std::vector<unsigned char> result;
    result.resize(str.length());
    memcpy(result.data(), str.c_str(), result.size());
    return std::move(result);
}

inline std::string VectorToString(const std::vector<unsigned char> & data)
{
    return std::string((char*)data.data(), data.size());
}