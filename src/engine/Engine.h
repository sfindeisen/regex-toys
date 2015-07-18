#ifndef _regexsf_engine_Engine_H_
#define _regexsf_engine_Engine_H_

#include "../misc/Printable.h"
#include "../cfa/CFA.h"
#include "../parser/ast/AbstractRegex.h"

namespace regexsf {

struct TState {
    TNodeIdx node;
    unsigned int cc;         // number of active counters
    unsigned int *counters;  // counter values: 0, 1, ... TotalCounters-1
                             // but only the first cc are relevant
                             // with the current counter stored at index cc-1
};

/** sub-CFA initialization result */
struct TSubCFAInitRes {
    TNodeIdx initialNd;
    TNodeIdx   finalNd;

    TSubCFAInitRes() : initialNd(0), finalNd(0) {
    }

    /** no sub-CFA built (empty regex) */
    bool isSkip() const {
        return ((0 == initialNd) || (0 == finalNd));
    }
};

class Engine : public regexsf::Printable {
    public:
        Engine(const AbstractRegex* regex);
        virtual ~Engine();

        /** match the whole string */
        bool match(const TString& string) const;
        TString asString() const;
    protected:
        /** initializes given CFA from given regex (but do not take top multi into account) */
        TSubCFAInitRes initCFA_simple(CFA& cfa, const AbstractRegex* regex) const;
        /** initializes given CFA from given regex */
        TSubCFAInitRes initCFA(CFA& cfa, const AbstractRegex* regex) const;
    private:
        CFA* cfa;
};

};

#endif
