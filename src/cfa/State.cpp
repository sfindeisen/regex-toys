#include "State.h"

using namespace std;
using namespace regexsf;

State::State() : counterId(0), incState(0), exitState(0), isAccept(false) {
}

State::~State() {
}

void State::setAlphaTransition(const TAlpha& c, const TStateIdx& i) {
    alphaTransitions[c] = i;
}

TString State::asString() const {
    TStringStream ss;
    ss << "state";
    return ss.str();
}
