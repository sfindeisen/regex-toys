#ifndef _regexsf_misc_Utils_H_
#define _regexsf_misc_Utils_H_

#include "../common.h"

namespace regexsf {

// TODO some of this is in boost/utility?...
class Utils {
    public:

template <typename Iter> static Iter next(Iter iter) {
    return ++iter;
}

template <typename Iter, typename Cont> static bool isLast(Iter iter, const Cont& cont) {
    return (iter != cont.end()) && (next(iter) == cont.end());
}

static unsigned int parseUInt(const TString& s);

};

};

#endif
