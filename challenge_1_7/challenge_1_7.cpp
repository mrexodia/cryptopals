#include "../challenge_1_1/challenge_1_1.h"
#include "../challenge_1_4/challenge_1_4.h"
#include "challenge_1_7.h"

int main()
{
    std::string base64;
    if (!FileReadAllNoWhitespaceText("7.txt", base64))
        puts("FileReadAllNoWhitespaceText failed...");
    else
    {
        std::vector<unsigned char> data;
        if (!FromBase64(base64, data))
            puts("FromBase64 failed...");
        else
        {
            std::vector<unsigned char> decrypted;
            if (!DecryptAesEcb(data, StringToVector("YELLOW SUBMARINE"), decrypted))
                puts("aes_ecb_decrypt failed...");
            else
            {
                RemovePKCS7Padding(decrypted);
                puts(VectorToString(decrypted).c_str());
            }
        }
    }
    getchar();
    return 0;
}