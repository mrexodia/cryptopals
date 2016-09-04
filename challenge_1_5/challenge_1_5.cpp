#include "../challenge_1_1/challenge_1_1.h"
#include "challenge_1_5.h"

int main()
{
    auto line = StringToVector("Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal");
    auto key = StringToVector("ICE");
    puts(ToHex(RepeatingXorCipher(line, key)).c_str());
    getchar();
    return 0;
}