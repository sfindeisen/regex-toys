#ifndef _regexsf_engine_CFABuilder_H_
#define _regexsf_engine_CFABuilder_H_

#include <tuple>

#include "../misc/Printable.h"
#include "../cfa/CFA.h"
#include "../parser/ast/AbstractRegexSequence.h"

namespace regexsf {

/** sub-CFA initialization result */
struct TSubCFAInitRes {
    TNodeIdx initialNode;
    TNodeIdx   finalNode;

    TSubCFAInitRes() : initialNode(0), finalNode(0) {
    }

    TSubCFAInitRes(const TNodeIdx& i1, const TNodeIdx& i2) : initialNode(i1), finalNode(i2) {
    }

    /** no sub-CFA built (empty regex) */
    bool isSkipped() const {
        return ((0 == initialNode) || (0 == finalNode));
    }
};

class CFABuilder {
    public:
        CFA* compile(const AbstractRegex* regex) const;
    protected:
        std::tuple<bool, unsigned int, unsigned int> computeCounter(const AbstractRegex& rx) const;

        /** builds sub-CFA from given regex sequence; the result is a list of sub-CFAs */
        std::vector<TSubCFAInitRes> initCFA_seq(CFA& cfa, const TCounterIdx& parentCounter, const AbstractRegexSequence* regex) const;

        /**
         * builds sub-CFA from given regex (but does not take top quantifier into account).
         *
         * parentCounter: If not zero, is a 1-based index of the most immediate counter
         *                this regex is governed by.
         */
        TSubCFAInitRes initCFA_simple(CFA& cfa, const TCounterIdx& parentCounter, const AbstractRegex* regex) const;

        /** builds sub-CFA from given regex (simple) and wraps it with a counter */
        TSubCFAInitRes initCFA_wrapWithCounter(CFA& cfa, const TCounterIdx& counterIdx, const AbstractRegex* regex) const;

        /** builds sub-CFA from given regex */
        TSubCFAInitRes initCFA(CFA& cfa, const TCounterIdx& parentCounter, const AbstractRegex* regex) const;
};

};

#endif
