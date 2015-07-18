#include "RegexSequence.h"

using namespace regexsf;

RegexSequence::RegexSequence(const std::vector<AbstractRegex*>& v) : AbstractRegexSequence(v) {
}

RegexSequence::~RegexSequence() {
}

inline RegexType RegexSequence::getType() const {
    return RegexType::RXSeq;
}

TString RegexSequence::asString_seqType() const {
    return "SEQ";
}

