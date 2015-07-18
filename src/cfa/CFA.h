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
        /** returns the number of counters in this CFA */
        unsigned int getCounterCount() const;

        /** appends given counter to the end of counter array, and returns its new index (1-based) */
        TCounterIdx appendCounter(const Counter& ctr);
        Counter& getCounter(const TCounterIdx& i);

        TNodeIdx    appendNode(const Node& node);
        TNodeIdx    appendNode();

        Node& getNode(const TNodeIdx& i);
        void setStartNode(const TNodeIdx& i);
        void setFinalNode(const TNodeIdx& i);

    private:
        friend class CFABuilder;
        friend class Engine;

        TNodeIdx startNode;
        TNodeIdx finalNode;
        std::vector<Node> nodes;
        std::vector<Counter> counters;
};

inline unsigned int CFA::getCounterCount() const {
    return counters.size();
}

};

#endif
