#include "challenge_1_4.h"

int main()
{
    std::vector<std::string> lines;
    if (!FileReadAllLines("4.txt", lines))
        puts("FileReadAllLines failed...");
    else
    {
        std::vector<std::vector<unsigned char>> dataList;
        dataList.resize(lines.size());
        for (size_t i = 0; i < lines.size(); i++)
            if (!FromHex(lines[i], dataList[i]))
                printf("FromHex failed on %s\n", lines[i].c_str());
        size_t bestIndex = 0;
        auto bestScore = 0;
        unsigned char bestKey = 0;
        FindBestSingleXorCandidate(dataList, bestIndex, bestKey, bestScore);
        printf("line: %d, score: %d, key: %02X\n", bestIndex + 1, bestScore, bestKey);
        auto bestDecrypted = SingleXorCipher(dataList[bestIndex], bestKey);
        puts(VectorToString(bestDecrypted).c_str());
    }
    getchar();
    return 0;
}
