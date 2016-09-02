#pragma once

#include "../challenge_1_5/challenge_1_5.h"
#include <climits>

inline int BitsSet(unsigned char c)
{
    auto set = 0;
    set += c >> 0 & 1;
    set += c >> 1 & 1;
    set += c >> 2 & 1;
    set += c >> 3 & 1;
    set += c >> 4 & 1;
    set += c >> 5 & 1;
    set += c >> 6 & 1;
    set += c >> 7 & 1;
    return set;
}

inline int HammingDistance(const std::vector<unsigned char> & first, const std::vector<unsigned char> & second)
{
    auto smallerPtr = &first;
    auto biggerPtr = &second;
    if (first.size() < second.size())
        std::swap(smallerPtr, biggerPtr);
    const auto & smaller = smallerPtr[0];
    const auto & bigger = biggerPtr[0];
    auto distance = 0;
    for (size_t i = 0; i < smaller.size(); i++)
        distance += BitsSet(smaller[i] ^ bigger[i]);
    auto diff = bigger.size() - smaller.size();
    for (size_t i = 0; i < diff; i++)
        distance += BitsSet(bigger[smaller.size() + i]);
    return distance;
}

inline bool TakeBytes(const std::vector<unsigned char> & data, size_t start, size_t size, std::vector<unsigned char> & out)
{
    if (start + size >= data.size())
        return false;
    out.resize(size);
    for (size_t i = 0; i < size; i++)
        out[i] = data[start + i];
    return true;
}

inline int FindRepeatingXorKeysize(const std::vector<unsigned char> & ciphertext, int lowerBound = 2, int upperBound = 40)
{
    int smallestDistance = INT_MAX;
    auto smallestKeysize = lowerBound;
    for (auto KEYSIZE = lowerBound; KEYSIZE < upperBound; KEYSIZE++)
    {
        std::vector<unsigned char> first, second;
        if (!TakeBytes(ciphertext, 0, KEYSIZE, first) || !TakeBytes(ciphertext, KEYSIZE, KEYSIZE, second))
        {
            puts("TakeBytes failed...");
            break;
        }
        auto distance = HammingDistance(first, second);
        auto normalized = distance / KEYSIZE;
        if (normalized < smallestDistance)
        {
            printf("found better %d from %d (distance: %d), keysize: %d\n", normalized, smallestDistance, distance, KEYSIZE);
            smallestDistance = normalized;
            smallestKeysize = KEYSIZE;
        }
    }
    return smallestKeysize;
}

inline void BreakRepeatingXor(const std::vector<unsigned char> & ciphertext, std::vector<unsigned char> & foundKey)
{
    auto KEYSIZE = FindRepeatingXorKeysize(ciphertext);
}