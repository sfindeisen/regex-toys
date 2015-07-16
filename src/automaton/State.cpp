#include "State.h"

using namespace std;
using namespace regexsf;

State::State() {
}

State::~State() {
}

void State::putNext(char c, const State* s) {
    next[c] = s;
}

TString State::asString() const {
    TStringStream ss;
    ss << "state";
    return ss.str();
}
