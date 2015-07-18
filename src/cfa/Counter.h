#ifndef _regexsf_cfa_Counter_H_
#define _regexsf_cfa_Counter_H_

#include "../misc/Printable.h"
#include "cfa-common.h"

namespace regexsf {

/** Counter description in a CFA */
class Counter : public regexsf::Printable {
    public:
        virtual ~Counter();
        TString asString() const;

    protected:
        /** lo,INF */
        Counter(const TCounterIdx& parent, unsigned int lo);
        Counter(const TCounterIdx& parent, unsigned int lo, unsigned int hi);

    private:
        friend class Engine;

        TCounterIdx parent; // parent counter in the counter tree (1-based) (or 0 if root)
        unsigned int lo;
        unsigned int hi;    // 0 for lo,INF

};

};

#endif
