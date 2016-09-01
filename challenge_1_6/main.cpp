#include "../challenge_1_1/challenge_1_1.h"
#include "../challenge_1_4/challenge_1_4.h"
#include "challenge_1_6.h"

int main()
{
    printf("distance: %d\n", HammingDistance(StringToVector("this is a test"), StringToVector("wokka wokka!!!")));
    std::string base64;
    if (!FileReadAllNoWhitespaceText("6.txt", base64))
        puts("FileReadAllNoWhitespaceText failed...");
    else
    {
        std::vector<unsigned char> data;
        if (!FromBase64(base64, data))
            puts("FromBase64 failed...");
        else
        {
            
        }
    }
    getchar();
    return 0;
}