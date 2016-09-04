#pragma once
#include "../challenge_1_6/challenge_1_6.h"

inline bool DetectAesEcb(const std::vector<std::vector<unsigned char>> & dataList, size_t & index, int blocksize = 16)
{
    for (size_t i = 0; i < dataList.size(); i++)
    {
        std::vector<std::vector<unsigned char>> blocks;
        blocks.resize(dataList[i].size() / blocksize);
        for (size_t j = 0; j < blocks.size(); j++)
            if (!TakeBytes(dataList[i], j * blocksize, blocksize, blocks[j]))
            {
                puts("TakeBytes failed...");
                return false;
            }

        for (size_t j = 0; j < blocks.size(); j++)
            for (auto k = j + 1; k < blocks.size(); k++)
            {
                if (blocks[j] == blocks[k])
                {
                    //printf("duplicate blocks found %u (%u) and %u (%u) at line %u\n", j, j * blocksize, k, k * blocksize, i);
                    index = i;
                    return true;
                }
            }
    }
    return true;
}
