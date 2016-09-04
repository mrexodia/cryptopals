#include "../challenge_1_1/challenge_1_1.h"
#include "challenge_1_2.h"

int main()
{
    std::vector<unsigned char> data1;
    std::vector<unsigned char> data2;
    if (!FromHex("1c0111001f010100061a024b53535009181c", data1) || !FromHex("686974207468652062756c6c277320657965", data2))
        puts("FromHex failed...");
    else
    {
        std::vector<unsigned char> result;
        if (!EqualXor(data1, data2, result))
            puts("EqualXor failed...");
        else
            puts(ToHex(result).c_str());
    }
    getchar();
    return 0;
}