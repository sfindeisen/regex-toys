#ifndef _regexsf_engine_Engine_H_
#define _regexsf_engine_Engine_H_

#include <cstring>
#include <tuple>
#include <vector>

#include "../cfa/CFA.h"
#include "../parser/ast/AbstractRegexSequence.h"

namespace regexsf {

struct TState {
    TNodeIdx node;
    int *counters;  // counter values: 0, 1, ... TotalCounters-1
                    // v >= 0 means this is the counter value
                    // v <  0 means that the counter value is -v, and we haven't yet traversed
                    //              a character transition in this iteration of the sub-automaton
                    //              governed by this counter.

    inline TState(const TNodeIdx& i, const unsigned int& ctrTotal, bool zeroCtr=true) : node(i), counters(nullptr) {
        if (1 <= ctrTotal) {
            counters = new int[ctrTotal];
            if (zeroCtr)
                memset(counters, 0, ctrTotal * sizeof(int));
        }
    }

    inline ~TState() {
        if (counters) {
            delete [] counters;
        }
    }

private:
    inline TState(const TState& a) : node(a.node), counters(nullptr) {
        // do not use
    }
};

typedef std::vector<TState*> TQueue;

class Engine {
    public:
        /** match the whole string */
        bool match(const CFA& cfa, const TString& s) const;

    protected:
        bool checkAccept(const CFA& cfa, TQueue& queue) const;
        TString asString(const CFA& cfa, const TState& t) const;
        TState* initState(const CFA& cfa, const TNodeIdx& ni) const;
        TState* copyState(const CFA& cfa, const TState& old) const;
        void followNilTransitions(const CFA& cfa, const TState *s, const Node& node, TQueue& queue) const;
        void bfs(const CFA& cfa, TQueue& queue, TQueue& q2, const TAlphaIdx& alphaIdx) const;
        void clearQueue(TQueue& q) const;
        bool checkMatch(const CFA& cfa, const TString& s) const;
};

inline TState* Engine::copyState(const CFA& cfa, const TState& old) const {
    const unsigned int ctrTotal = cfa.counters.size();
    TState* s = new TState(old.node, ctrTotal, false);
    memcpy(s->counters, old.counters, ctrTotal * sizeof(unsigned int));
    return s;
}

};

#endif
