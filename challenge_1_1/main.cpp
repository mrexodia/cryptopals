#include "challenge_1_1.h"

int main()
{
    std::vector<unsigned char> data;
    if (FromHex("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d", data))
    {
        puts(ToHex(data).c_str());
        auto base64 = ToBase64(data);
        puts(base64.c_str());
        if (FromBase64(base64, data))
            puts(VectorToString(data).c_str());
        else
            puts("FromBase64 failed...");
    }
    else
        puts("FromHex failed...");
    getchar();
    return 0;
}