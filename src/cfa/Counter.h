#ifndef _regexsf_cfa_Counter_H_
#define _regexsf_cfa_Counter_H_

#include "../misc/Printable.h"
#include "cfa-common.h"

namespace regexsf {

/** Counter description in a CFA */
class Counter : public regexsf::Printable {
    public:
        /** lo,INF */
        Counter(unsigned int lo);
        Counter(unsigned int lo, unsigned int hi);
        virtual ~Counter();
        TString asString() const;
    private:
        friend class Engine;
        unsigned int lo;
        unsigned int hi;    // 0 for lo,INF
};

};

#endif
