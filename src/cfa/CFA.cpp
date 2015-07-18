#include "CFA.h"

using namespace std;
using namespace regexsf;

CFA::CFA() : Printable() {
}

CFA::~CFA() {
}

TCounterIdx CFA::addCounter(const Counter& ctr) {
    counters.push_back(ctr);
    return counters.size();
}

TString CFA::asString() const {
    TStringStream ss;
    ss << "CFA";
    return ss.str();
}
