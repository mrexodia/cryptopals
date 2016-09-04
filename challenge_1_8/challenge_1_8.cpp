#include "../challenge_1_1/challenge_1_1.h"
#include "../challenge_1_4/challenge_1_4.h"
#include "challenge_1_8.h"
#include "../challenge_1_7/challenge_1_7.h"

int main()
{
    std::vector<std::string> lines;
    if (!FileReadAllLines("8.txt", lines))
        puts("FileReadAllLines failed...");
    else
    {
        std::vector<std::vector<unsigned char>> dataList;
        dataList.resize(lines.size());
        auto success = true;
        for (size_t i = 0; i < lines.size(); i++)
            if (!FromHex(lines[i], dataList[i]))
            {
                success = false;
                break;
            }
        if (!success)
            puts("FromHex failed...");
        else
        {
            size_t index;
            if (!DetectAesEcb(dataList, index))
                puts("DetectAesEcb failed...");
            else
            {
                printf("detected ECB mode at line %u\n", index + 1);
                puts(ToHex(dataList[index]).c_str());
            }
        }
    }
    getchar();
    return 0;
}
