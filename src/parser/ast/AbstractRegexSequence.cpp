#include <iostream>

#include "AbstractRegexSequence.h"

using namespace std;
using namespace regexsf;

AbstractRegexSequence::AbstractRegexSequence(const std::vector<AbstractRegex*>& v) : AbstractRegex(), seq(v) {
}

AbstractRegexSequence::~AbstractRegexSequence() {
    for (std::vector<AbstractRegex*>::iterator it = seq.begin(); it != seq.end(); ++it) {
        RX_DELETE(*it);
    }
    seq.clear();
}

TString AbstractRegexSequence::asString(const TString& indent) const {
    TStringStream ss;
    for (std::vector<AbstractRegex*>::const_iterator it = seq.begin(); it != seq.end(); ++it) {
        ss << asString_other(**it, indent + "  ") << endl;
    }
    return ss.str();
}

