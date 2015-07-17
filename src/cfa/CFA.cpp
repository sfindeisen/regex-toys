#include "CFA.h"

using namespace std;
using namespace regexsf;

CFA::CFA() {
}

CFA::~CFA() {
}

TString CFA::asString() const {
    TStringStream ss;
    ss << "CFA";
    return ss.str();
}
