#ifndef _regexsf_cfa_CFA_H_
#define _regexsf_cfa_CFA_H_

#include <vector>
#include "../misc/Printable.h"
#include "Counter.h"
#include "Node.h"

namespace regexsf {

class CFA : public regexsf::Printable {
    public:
        CFA();
        virtual ~CFA();
        TString asString() const;
    protected:
        /** appends given counter to the end of counter array, and returns its new index (1-based) */
        TCounterIdx addCounter(const Counter& ctr);
    private:
        friend class Engine;
        std::vector<Node> nodes;
        std::vector<Counter> counters;
};

};

#endif