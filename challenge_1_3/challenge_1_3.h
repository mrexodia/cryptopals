#pragma once

#include <string>
#include <vector>
#include <cstdint>

inline std::vector<unsigned char> XorCipher(const std::vector<unsigned char> & data, unsigned char key)
{
    auto result = data;
    for (size_t i = 0; i < result.size(); i++)
        result[i] ^= key;
    return std::move(result);
}

inline void AnalyzeFrequency(const std::vector<unsigned char> & data, size_t frequency[256])
{
    memset(frequency, 0, 256 * sizeof(size_t));
    for (size_t i = 0; i < data.size(); i++)
        frequency[data[i]]++;
}

inline int ScoreFrequency(size_t frequency[256])
{
    auto score = 0;
    std::string priority = "etaoinshrdlcumwfgypbvkjxqz";
    for (auto i = 0; i < 256; i++)
    {
        if (!frequency[i])
            continue;
        char ch = tolower(i) != -1 ? tolower(i) : i;
        auto pos = priority.find(ch);
        if (pos == std::string::npos)
            continue;
        auto basescore = priority.length() - pos;
        score += frequency[i] * basescore;
        //printf("found %c at position %u, frequency: %u, basescore: %u!\n", ch, pos, frequency[i], basescore);
    }
    return score;
}