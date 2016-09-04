#pragma once

#include <string>
#include <vector>
#include <cstdint>

inline std::vector<unsigned char> SingleXorCipher(const std::vector<unsigned char> & data, unsigned char key)
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

//Implemented from https://en.wikipedia.org/wiki/Letter_frequency#Relative_frequencies_of_letters_in_the_English_language
inline int ScoreFrequency(size_t frequency[256])
{
    auto score = 0;
    std::string priority = " etaoinshrdlcumwfgypbvkjxqz"; //notice the space
    for (auto i = 0; i < 256; i++)
    {
        if (!frequency[i])
            continue;
        if (!isgraph(i) && !isspace(i))
        {
            score = 0;
            continue;
        }
        auto basescore = 1;
        auto pos = priority.find(tolower(i));
        if (pos != std::string::npos)
            basescore = priority.length() - pos;
        score += frequency[i] * basescore;
        //printf("found %c at position %u, frequency: %u, basescore: %u!\n", i, pos, frequency[i], basescore);
    }
    return score;
}

inline void FindBestSingleXorKey(const std::vector<unsigned char> & data, unsigned char & bestKey, int & bestScore)
{
    bestScore = 0;
    bestKey = 0;
    for (auto i = 0; i < 256; i++)
    {
        auto key = (unsigned char)i;
        auto decrypted = SingleXorCipher(data, key);
        size_t frequency[256];
        AnalyzeFrequency(decrypted, frequency);
        auto score = ScoreFrequency(frequency);
        if (score > bestScore)
        {
            bestScore = score;
            bestKey = key;
        }
        //printf("score for key %02X: %d\n", key, score);
    }
}