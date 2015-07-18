#ifndef _regexsf_cfa_alphabet_H_
#define _regexsf_cfa_alphabet_H_

#include "../throwable/runtime/IllegalArgumentException.h"
#include "cfa-common.h"

namespace regexsf {

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

inline char idx2alpha(const TAlphaIdx& i) {
    if (i) {
        if ((1 <= i) && (i <= 26))
            return 'a' - 1 + i;
        if ((1+26 <= i) && (i <= 26+26))
            return 'A' - (1+26) + i;
        RX_THROW_STREAM(IllegalArgumentException, "char index out of range: " << i);
    } else {
        return '-';
    }
}

};

#endif
