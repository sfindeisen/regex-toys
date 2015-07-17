#include "RegexSequence.h"

using namespace regexsf;

RegexSequence::RegexSequence(const std::vector<AbstractRegex*>& v) : AbstractRegexSequence(v) {
}

RegexSequence::~RegexSequence() {
}

TString RegexSequence::asString_seqType() const {
    return "SEQ";
}

