#pragma once

#include "../challenge_1_1/challenge_1_1.h"
#include "../challenge_1_3/challenge_1_3.h"

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>

inline bool FileReadAllData(const std::string & filename, std::vector<unsigned char> & data)
{
    std::ifstream in(filename, std::ios::binary);
    if(!in.is_open())
        return false;
    data.clear();
    while (in)
    {
        char c;
        in.get(c);
        if (in)
            data.push_back(c);
    }
    return true;
}

inline bool FileReadAllText(const std::string & filename, std::string & str)
{
    std::vector<unsigned char> data;
    if (!FileReadAllData(filename, data))
        return false;
    str = VectorToString(data);
    return true;
}

inline bool FileReadAllLines(const std::string & filename, std::vector<std::string> & lines)
{
    std::string str;
    if (!FileReadAllText(filename, str))
        return false;
    lines.clear();
    std::string line;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '\r')
            continue;
        if (str[i] == '\n')
        {
            lines.push_back(line);
            line.clear();
        }
        else
            line.push_back(str[i]);
    }
    if (line.length())
        lines.push_back(line);
    return true;
}

inline std::string RemoveWhitespace(const std::string & str)
{
    std::string result;
    result.reserve(str.length());
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isspace(str[i]))
            continue;
        result.push_back(str[i]);
    }
    return std::move(result);
}

inline bool FileReadAllNoWhitespaceText(const std::string & filename, std::string & str)
{
    if (!FileReadAllText(filename, str))
        return false;
    str = RemoveWhitespace(str);
    return true;
}

inline void FindBestSingleXorCandidate(const std::vector<std::vector<unsigned char>> & dataList, size_t & bestIndex, unsigned char & bestKey, int & bestScore)
{
    bestScore = 0;
    for (size_t i = 0; i < dataList.size(); i++)
    {
        int score;
        unsigned char key;
        FindBestSingleXorKey(dataList[i], key, score);
        if (score > bestScore)
        {
            bestScore = score;
            bestKey = key;
            bestIndex = i;
        }
    }
}