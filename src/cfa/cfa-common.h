#ifndef _regexsf_cfa_cfa_common_H_
#define _regexsf_cfa_cfa_common_H_

#include "../common.h"

namespace regexsf {

typedef int  TStateIdx;      // index to the state   array in the automaton (1-based)
typedef int  TCounterIdx;    // index to the counter array in the automaton (1-based)
typedef char TAlpha;         // alphabet (currently a-z A-Z only!); 0 is for nil-edges

};

#endif
