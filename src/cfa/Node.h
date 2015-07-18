#ifndef _regexsf_cfa_Node_H_
#define _regexsf_cfa_Node_H_

#include <array>
#include <vector>

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
        void setAccept(bool accept);
        void setAlphaTransition(const TAlpha& c, const TNodeIdx& i);
        void addNilTransition(const TNodeIdx& i);
        void setCounterId(const TCounterIdx& counterId);
        void setIncNode(const TNodeIdx& idx);
        void setExitNode(const TNodeIdx& idx);

    private:
        friend class Engine;

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

        /**
         * counter-agnostic nil-transitions. They can be used, for example, with
         * alternative or concatenation.
         */
        std::vector<TNodeIdx> nilTransitions;
};

inline void Node::setAccept(bool accept) {
    isAccept = accept;
}

inline void Node::setAlphaTransition(const TAlpha& c, const TNodeIdx& i) {
    if (1 <= i)
        alphaTransitions[alpha2idx(c)] = i;
    else
        RX_THROW(IllegalArgumentException);
}

inline void Node::addNilTransition(const TNodeIdx& i) {
    if (1 <= i)
        nilTransitions.push_back(i);
    else
        RX_THROW(IllegalArgumentException);
}

inline void Node::setCounterId(const TCounterIdx& counterId) {
    if (1 <= counterId)
        this->counterId = counterId;
    else
        RX_THROW(IllegalArgumentException);
}

inline void Node::setIncNode(const TNodeIdx& idx) {
    if (1 <= idx)
        this->incNode = idx;
    else
        RX_THROW(IllegalArgumentException);
}

inline void Node::setExitNode(const TNodeIdx& idx) {
    if (1 <= idx)
        this->exitNode = idx;
    else
        RX_THROW(IllegalArgumentException);
}

};

#endif
