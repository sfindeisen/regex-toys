#include "../throwable/runtime/IllegalArgumentException.h"
#include "Counter.h"

using namespace std;
using namespace regexsf;

Counter::Counter(const TCounterIdx& pc, unsigned int lo) : Printable(), parent(pc), lo(lo), hi(0) {
    if (! lo)
        RX_THROW(IllegalArgumentException);
}

Counter::Counter(const TCounterIdx& pc, unsigned int lo, unsigned int hi) : Printable(), parent(pc), lo(lo), hi(hi)  {
    if ((hi < lo) || ((hi==lo) && (hi<=1)))
        RX_THROW_STREAM(IllegalArgumentException, lo << "," << hi);
}

Counter::~Counter() {
}

TString Counter::asString() const {
    TStringStream ss;
    ss << "CTR parent: " << parent << " {" << lo << "," << hi << "}";
    return ss.str();
}
