#ifndef _regexsf_cfa_State_H_
#define _regexsf_cfa_State_H_

#include <map>

#include "../misc/Printable.h"
#include "cfa-common.h"

namespace regexsf {

/**
 * NFA with nil transitions - state.
 *
 * The state can be (exactly 1 of):
 *
 * (1) associated with exactly 1 counter
 * (2) not associated with a counter.
 *
 * In the first case, there are 2 special nil-edges outgoing from this state:
 *
 *  incEdge: [counter <  max], counter += 1
 * exitEdge: [counter >= min], counter := 0
 */
class State : public regexsf::Printable {
    public:
        State();
        virtual ~State();
        virtual TString asString() const;

    protected:
        void setAlphaTransition(const TAlpha& c, const TStateIdx& i);

    private:
        TCounterIdx counterId;  // counter this state is associated with (1-based) or 0
                                // YAY, checking for ==0 is going to be fast! :-)
        TStateIdx  incState;    // state associated with  incEdge (if counterId)
        TStateIdx exitState;    // state associated with exitEdge (if counterId)
        bool isAccept;          // accepting state? this has nothing to do with the counters!

        /**
         * simple transitions: each of them is associated with exactly 1 alphabet symbol,
         * has no counter actions nor conditions, and each alphabet symbol has 0-1 such
         * transitions.
         */
        std::map<TAlpha,TStateIdx> alphaTransitions;
};

};

#endif
