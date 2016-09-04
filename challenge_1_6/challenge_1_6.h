#pragma once

#include "../challenge_1_5/challenge_1_5.h"
#include <climits>
#include <numeric>

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
    if (start + size > data.size())
        return false;
    out.resize(size);
    for (size_t i = 0; i < size; i++)
        out[i] = data[start + i];
    return true;
}

inline size_t FindRepeatingXorKeysize(const std::vector<unsigned char> & ciphertext, size_t lowerBound = 2, size_t upperBound = 40)
{
    double smallestDistance = INT_MAX;
    auto bestKeysize = lowerBound;
    for (auto KEYSIZE = lowerBound; KEYSIZE < upperBound; KEYSIZE++)
    {
        std::vector<unsigned char> blocks[4];
        for (size_t i = 0; i < _countof(blocks); i++)
            if (!TakeBytes(ciphertext, i * KEYSIZE, KEYSIZE, blocks[i]))
            {
                puts("TakeBytes failed...");
                return bestKeysize;
            }

        std::vector<double> distances;
        distances.reserve(_countof(blocks) * 2);
        for (size_t i = 0; i < _countof(blocks); i++)
            for (auto j = i + 1; j < _countof(blocks); j++)
                distances.push_back(double(HammingDistance(blocks[i], blocks[j])) / KEYSIZE);
        auto averageDistance = std::accumulate(distances.begin(), distances.end(), 0.0) / distances.size();

        //printf("size: %d, dist: %f\n", KEYSIZE, averageDistance);
        if (averageDistance <= smallestDistance)
        {
            //printf("found better %f from %f, keysize: %d\n", averageDistance, smallestDistance, KEYSIZE);
            smallestDistance = averageDistance;
            bestKeysize = KEYSIZE;
        }
    }
    return bestKeysize;
}

inline void BreakRepeatingXor(const std::vector<unsigned char> & ciphertext, std::vector<unsigned char> & foundKey)
{
    //find keysize
    auto KEYSIZE = FindRepeatingXorKeysize(ciphertext);
    foundKey.resize(KEYSIZE);

    //break ciphertext into blocks of KEYSIZE
    std::vector<std::vector<unsigned char>> blocks;
    blocks.resize(ciphertext.size() / KEYSIZE);
    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (!TakeBytes(ciphertext, i * KEYSIZE, KEYSIZE, blocks[i]))
        {
            puts("TakeBytes failed...");
            return;
        }
    }

    //transpose the blocks
    std::vector<std::vector<unsigned char>> transposed;
    transposed.resize(KEYSIZE);
    for (size_t i = 0; i < transposed.size(); i++)
    {
        transposed[i].resize(blocks.size());
        for (size_t j = 0; j < blocks.size(); j++)
            transposed[i][j] = blocks[j][i];
    }

    //solve single-byte xor key for each transposed block
    for (size_t i = 0; i < transposed.size(); i++)
    {
        auto bestScore = 0;
        unsigned char bestKey = 0;
        FindBestSingleXorKey(transposed[i], bestKey, bestScore);
        foundKey[i] = bestKey;
    }
}