#include "Engine.h"
#include "../throwable/runtime/IllegalArgumentException.h"

using namespace regexsf;

Engine::Engine(const AbstractRegex *regex) : Printable(), cfa(nullptr) {
    RX_NEW(cfa, CFA);
    initCFA(*cfa, regex);
}

Engine::~Engine() {
    if (nullptr != cfa) {
        RX_DELETE(cfa);
    }
}

TSubCFAInitRes Engine::initCFA(CFA& cfa, const AbstractRegex *rx) const {
    if (nullptr == rx)
        RX_THROW(IllegalArgumentException);

    TSubCFAInitRes res;

    if (rx->hasMulti()) {
        unsigned int lo=1;
        unsigned int hi=1;
        bool hinf = false;      // lo..INF

        for (std::vector<Multi*>::const_iterator it = rx->multi.begin(); it != rx->multi.end(); ++it) {
            const Multi& m = **it;

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
        }

        if (hinf) {
            if (2 <= lo)
                cfa.addCounter(Counter(lo));
            else if (1 == lo) {
                // + : 1 or more
            } else {
                // * : 0 or more
            }
        } else {
            if (hi) {
                if (2 <= hi)
                    cfa.addCounter(Counter(lo,hi));
                else {
                    // 1 or less
                    if (lo) {
                        // exactly 1
                    } else {
                        // ? : 0 or 1
                    }
                }
            } else {
                // zero
            }
        }
    }

    return res;
}

bool Engine::match(const TString& string) const {
    // TODO implement this!
    return false;
}

TString Engine::asString() const {
    TStringStream ss;
    ss << "Engine";
    if (nullptr != cfa)
        ss << ": " << (*cfa);
    return ss.str();
}

