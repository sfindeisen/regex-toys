#include "CFABuilder.h"
#include "../parser/ast/RegexChar.h"
#include "../parser/ast/RegexChoice.h"
#include "../parser/ast/RegexSequence.h"
#include "../throwable/runtime/IllegalArgumentException.h"
#include "../throwable/runtime/IllegalStateException.h"

using namespace std;
using namespace regexsf;

CFA* CFABuilder::compile(const AbstractRegex *regex) const {
    CFA* cfa = nullptr;
    RX_NEW(cfa, CFA);
    TSubCFAInitRes ir(initCFA(*cfa, 0, regex));

    if (ir.isSkipped()) {
        RX_DELETE(cfa);
        RX_THROW(IllegalArgumentException);
    } else {
        cfa->setStartNode(ir.initialNode);
        cfa->setFinalNode(ir.finalNode);
        return cfa;
    }
}

std::vector<TSubCFAInitRes> CFABuilder::initCFA_seq(CFA& cfa, const TCounterIdx& parentCounter, const AbstractRegexSequence* rx) const {
    std::vector<TSubCFAInitRes> res;
    for (std::vector<AbstractRegex*>::const_iterator it = rx->seq.begin(); it != rx->seq.end(); ++it) {
        TSubCFAInitRes initRes(initCFA(cfa, parentCounter, *it));
        if (! initRes.isSkipped())
            res.push_back(initRes);
    }
    return res;
}

TSubCFAInitRes CFABuilder::initCFA_simple(CFA& cfa, const TCounterIdx& parentCounter, const AbstractRegex* rx) const {
    if (nullptr == rx)
        RX_THROW(IllegalArgumentException);
    
    switch (rx->getType()) {
        case RegexType::RXChar:
        {
            const RegexChar *rc = dynamic_cast<const RegexChar*>(rx);

            if (rc) {
                const TNodeIdx i1 = cfa.appendNode();
                Node n2;
                n2.setAccept(true);
                const TNodeIdx i2 = cfa.appendNode(n2);
                cfa.getNode(i1).setAlphaTransition(rc->getValue(), i2);
                return TSubCFAInitRes(i1, i2);
            } else {
                RX_THROW(IllegalArgumentException);
            }
        }
        case RegexType::RXAlt:
        {
            const RegexChoice *rc = dynamic_cast<const RegexChoice*>(rx);

            if (rc) {
                std::vector<TSubCFAInitRes> subIR(initCFA_seq(cfa, parentCounter, rc));

                if (subIR.empty()) {
                    return TSubCFAInitRes();    // skip
                } else {
                    if (2 <= subIR.size()) {
                        const TNodeIdx i1 = cfa.appendNode();
                        Node& startNode = cfa.getNode(i1);
                        Node acceptNode;
                        acceptNode.setAccept(true);
                        const TNodeIdx i2 = cfa.appendNode(acceptNode);

                        for (std::vector<TSubCFAInitRes>::const_iterator it = subIR.begin(); it != subIR.end(); ++it) {
                            startNode.addNilTransition(it->initialNode);
                            Node& n2 = cfa.getNode(it->finalNode);
                            n2.setAccept(false);
                            n2.addNilTransition(i2);
                        }

                        return TSubCFAInitRes(i1, i2);
                    } else {
                        // singleton
                        return subIR.at(0);
                    }
                }
            } else {
                RX_THROW(IllegalArgumentException);
            }
        }
        case RegexType::RXSeq:
        {
            const RegexSequence *rs = dynamic_cast<const RegexSequence*>(rx);

            if (rs) {
                std::vector<TSubCFAInitRes> subIR(initCFA_seq(cfa, parentCounter, rs));

                if (subIR.empty()) {
                    return TSubCFAInitRes();    // skip
                } else {
                    if (2 <= subIR.size()) {
                        for (unsigned int j=1; j < subIR.size(); ++j) {
                            Node& np = cfa.getNode(subIR[j-1].finalNode);
                            np.setAccept(false);
                            np.addNilTransition(subIR[j].initialNode);
                        }
                        return TSubCFAInitRes(subIR.front().initialNode, subIR.back().finalNode);
                    } else {
                        // singleton
                        return subIR.at(0);
                    }
                }
            } else {
                RX_THROW(IllegalArgumentException);
            }
        }
        default:
            RX_THROW(IllegalArgumentException);
    }
}

std::tuple<bool, unsigned int, unsigned int> CFABuilder::computeCounter(const AbstractRegex& rx) const {
    if (! rx.hasMulti())
        RX_THROW(IllegalArgumentException);

    unsigned int lo=1;
    unsigned int hi=1;
    bool hinf = false;      // lo..INF

    for (std::vector<Multi*>::const_iterator it = rx.multi.begin(); it != rx.multi.end(); ++it) {
        const Multi& m = **it;
        RX_DEBUG("computeCounter: " << m);

        if (m.isZero()) {
            lo=hi=0;        // no occurences at all
            break;
        } else {
            lo *= m.getLo();

            if (! hinf) {
                if (m.hasUpperBound())
                    hi *= m.getHi();
                else
                    hinf = true;
            }
        }

        RX_DEBUG("computeCounter: " << lo << ".." << hi << " (" << hinf << ")");
    }

    RX_DEBUG("computeCounter: result: " << lo << ".." << hi << " (" << hinf << ")");
    return tuple<bool, unsigned int, unsigned int>(hinf, lo, hi);
}

TSubCFAInitRes CFABuilder::initCFA_wrapWithCounter(CFA& cfa, const TCounterIdx& counterIdx, const AbstractRegex *rx) const {
    TSubCFAInitRes initRes(initCFA_simple(cfa, counterIdx, rx));

    if (initRes.isSkipped()) {
        return initRes;
    } else {
        Node acceptNode;
        acceptNode.setAccept(true);
        const TNodeIdx i2 = cfa.appendNode(acceptNode);

        Node startNode;
        startNode.setCounterId(counterIdx);
        startNode.setIncNode(initRes.initialNode);
        startNode.setExitNode(i2);
        const TNodeIdx i1 = cfa.appendNode(startNode);

        Node& oldAcc = cfa.getNode(initRes.finalNode);
        oldAcc.setAccept(false);
        oldAcc.addNilTransition(i1);

        return TSubCFAInitRes(i1, i2);
    }               
}

TSubCFAInitRes CFABuilder::initCFA(CFA& cfa, const TCounterIdx& parentCounter, const AbstractRegex *rx) const {
    if (nullptr == rx)
        RX_THROW(IllegalArgumentException);

    if (rx->hasMulti()) {
        tuple<bool, unsigned int, unsigned int> t = computeCounter(*rx);
        unsigned int lo = get<1>(t);
        unsigned int hi = get<2>(t);

        if (get<0>(t)) {
            // lo..INF
            if (2 <= lo) {
                // 2+
                TCounterIdx cidx = cfa.appendCounter(Counter(parentCounter, lo));
                return initCFA_wrapWithCounter(cfa, cidx, rx);
            } else if (1 == lo) {
                // 1+
                TSubCFAInitRes initRes(initCFA_simple(cfa, parentCounter, rx));

                if (initRes.isSkipped()) {
                    return initRes;
                } else {
                    // TODO this could be optimized a bit (1 node less)
                    Node acceptNode;
                    acceptNode.setAccept(true);
                    acceptNode.addNilTransition(initRes.initialNode);
                    const TNodeIdx i2 = cfa.appendNode(acceptNode);

                    Node& oldAcc = cfa.getNode(initRes.finalNode);
                    oldAcc.setAccept(false);
                    oldAcc.addNilTransition(i2);

                    return TSubCFAInitRes(initRes.initialNode, i2);
                }
            } else {
                // 0+
                TSubCFAInitRes initRes(initCFA_simple(cfa, parentCounter, rx));

                if (initRes.isSkipped()) {
                    return initRes;
                } else {
                    // TODO this could be optimized a bit (2 nodes less)
                    Node acceptNode;
                    acceptNode.setAccept(true);
                    acceptNode.addNilTransition(initRes.initialNode);
                    const TNodeIdx i2 = cfa.appendNode(acceptNode);

                    Node startNode;
                    startNode.addNilTransition(initRes.initialNode);
                    startNode.addNilTransition(i2);
                    const TNodeIdx i1 = cfa.appendNode(startNode);

                    Node& oldAcc = cfa.getNode(initRes.finalNode);
                    oldAcc.setAccept(false);
                    oldAcc.addNilTransition(i2);

                    return TSubCFAInitRes(i1, i2);
                }
            }
        } else {
            // lo..hi (both inclusive)
            if (hi) {
                if (2 <= hi) {
                    TCounterIdx cidx = cfa.appendCounter(Counter(parentCounter, lo, hi));
                    return initCFA_wrapWithCounter(cfa, cidx, rx);
                } else {
                    // 0 or 1
                    if (lo) {
                        // exactly 1
                        return initCFA_simple(cfa, parentCounter, rx);
                    } else {
                        // 0 or 1
                        TSubCFAInitRes initRes(initCFA_simple(cfa, parentCounter, rx));

                        if (initRes.isSkipped()) {
                            return initRes;
                        } else {
                            Node startNode;
                            startNode.addNilTransition(initRes.initialNode);
                            startNode.addNilTransition(initRes.finalNode);
                            const TNodeIdx i1 = cfa.appendNode(startNode);
                            return TSubCFAInitRes(i1, initRes.finalNode);
                        }
                    }
                }
            } else {
                // 0: skip
                return TSubCFAInitRes();
            }
        }
    } else {
        return initCFA_simple(cfa, parentCounter, rx);
    }
}
