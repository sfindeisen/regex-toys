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

inline bool AbstractRegexSequence::isEmpty() const {
    return seq.empty();
}
inline int AbstractRegexSequence::seqLength() const {
    return seq.size();
}

TString AbstractRegexSequence::asString() const {
    TStringStream ss;
    ss << asString_seqType() << '(';
    for (std::vector<AbstractRegex*>::const_iterator it = seq.begin(); it != seq.end(); ++it)
        ss << (**it);
    ss << ')' << asString_multi();
    return ss.str();
}

