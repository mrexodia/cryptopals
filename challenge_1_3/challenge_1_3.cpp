#include "../challenge_1_1/challenge_1_1.h"
#include "challenge_1_3.h"

int main()
{
    std::vector<unsigned char> data;
    if (!FromHex("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", data))
        puts("FromHex failed...");
    else
    {
        auto bestScore = 0;
        unsigned char bestKey = 0;
        FindBestSingleXorKey(data, bestKey, bestScore);
        printf("best score: %d, best key: %02X\n", bestScore, bestKey);
        auto bestDecrypted = SingleXorCipher(data, bestKey);
        puts(VectorToString(bestDecrypted).c_str());
    }
    getchar();
    return 0;
}