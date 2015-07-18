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
    unsigned int cc;         // number of active counters
    unsigned int *counters;  // counter values: 0, 1, ... TotalCounters-1
                             // but only the first cc are relevant
                             // with the current counter stored at index cc-1

    inline TState(const TNodeIdx& i) : node(i), cc(0), counters(nullptr) {
    }

    inline TState(const TNodeIdx& i, const unsigned int& ctrTotal) : node(i), cc(1), counters(nullptr) {
        counters = new unsigned int[ctrTotal];
        memset(counters, 0, ctrTotal * sizeof(unsigned int));
    }

    inline ~TState() {
        if (counters) {
            delete [] counters;
        }
    }

private:
    inline TState(const TState& a) : node(a.node), cc(a.cc), counters(nullptr) {
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
        TString asString(const TState& t) const;
        TState* initState(const CFA& cfa, const TNodeIdx& ni) const;
        TState* copyState(const CFA& cfa, const TState& old) const;
        void followNilTransitions(const CFA& cfa, const TState *s, const Node& node, TQueue& queue) const;
        void bfs(const CFA& cfa, TQueue& queue, TQueue& q2, const TAlphaIdx& alphaIdx) const;
        void clearQueue(TQueue& q) const;
        bool checkMatch(const CFA& cfa, const TString& s) const;
};

inline TState* Engine::copyState(const CFA& cfa, const TState& old) const {
    TState* s = new TState(old.node);
    if (old.counters) {
        const unsigned int ctrTotal = cfa.counters.size();
        s->counters = new unsigned int[ctrTotal];
        memset(s->counters, 0, ctrTotal * sizeof(unsigned int));
        memcpy(s->counters, old.counters, old.cc * sizeof(unsigned int));
    }
    s->cc = old.cc;
    return s;
}

};

#endif
