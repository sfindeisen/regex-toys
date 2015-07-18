#include "../throwable/runtime/IllegalArgumentException.h"
#include "Counter.h"

using namespace std;
using namespace regexsf;

Counter::Counter(unsigned int lo) : Printable(), lo(lo), hi(0) {
    if (! lo)
        RX_THROW(IllegalArgumentException);
}

Counter::Counter(unsigned int lo, unsigned int hi) : Printable(), lo(lo), hi(hi)  {
    if ((hi < lo) || ((hi==lo) && (hi<=1)))
        RX_THROW_STREAM(IllegalArgumentException, lo << "," << hi);
}

Counter::~Counter() {
}

TString Counter::asString() const {
    TStringStream ss;
    ss << lo << "," << hi;
    return ss.str();
}
