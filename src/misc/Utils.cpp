#include "Utils.h"
#include "../throwable/runtime/IllegalArgumentException.h"

using namespace regexsf;

unsigned int Utils::parseUInt(const TString& s) {
    unsigned int k=0;
    unsigned int i=0;

    for (; i < s.length(); ++i) {
        if (('0' <= s[i]) && (s[i] <= '9')) {
            k *= 10;
            k += (s[i] - '0');
        } else {
            break;
        }
    }

    if (i)
        return k;
    else
        RX_THROW(IllegalArgumentException);
}
