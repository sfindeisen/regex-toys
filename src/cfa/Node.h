#ifndef _regexsf_cfa_Node_H_
#define _regexsf_cfa_Node_H_

#include <array>
#include "../misc/Printable.h"
#include "alphabet.h"

namespace regexsf {

/**
 * CFA graph node (it differs from a state: counter values are not stored here).
 *
 * The Node can be (exactly 1 of):
 *
 * (1) associated with exactly 1 counter
 * (2) not associated with a counter.
 *
 * In the first case, there are 2 special nil-edges outgoing from this Node:
 *
 *  incEdge: [counter <  max], counter += 1
 * exitEdge: [counter >= min], counter := 0
 */
class Node : public regexsf::Printable {
    public:
        Node();
        virtual ~Node();
        virtual TString asString() const;

    protected:
        void setAlphaTransition(const TAlpha& c, const TNodeIdx& i);

    private:
        TCounterIdx counterId;  // counter this Node is associated with (1-based) or 0
                                // YAY, checking for ==0 is going to be fast! :-)
        TNodeIdx  incNode;      // Node associated with  incEdge (if counterId)
        TNodeIdx exitNode;      // Node associated with exitEdge (if counterId)
        bool isAccept;          // accepting Node? this has nothing to do with the counters!
                                // (will accept for any counter values)

        /**
         * simple transitions: each of them is associated with exactly 1 alphabet symbol,
         * has no counter actions nor conditions, and each alphabet symbol has 0-1 such
         * transitions.
         */
        std::array<TNodeIdx,AlphaLen> alphaTransitions;
};

};

#endif
