#ifndef _regexsf_cfa_alphabet_H_
#define _regexsf_cfa_alphabet_H_

#include "../throwable/runtime/IllegalArgumentException.h"
#include "cfa-common.h"

namespace regexsf {

typedef char TAlpha;          // alphabet (currently a-z A-Z only!); 0 is for nil-edges
typedef int  TAlphaIdx;
const int AlphaLen = 1+26+26; // nil + a-z + A-Z

inline TAlphaIdx alpha2idx(char c) {
    if (c) {
        // TODO what if not ASCII?
        if (('a' <= c) && (c <= 'z'))
            return (1 + c - 'a');
        if (('A' <= c) && (c <= 'Z'))
            return (1 + 26 + c - 'A');
        RX_THROW_STREAM(IllegalArgumentException, "unknown character: " << ((int) c));
    } else {
        return 0;
    }
}

};

#endif
