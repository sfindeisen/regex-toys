#include "RegexSequence.h"

using namespace regexsf;

RegexSequence::RegexSequence(const std::vector<AbstractRegex*>& v) : AbstractRegex(), seq(v) {
}

RegexSequence::~RegexSequence() {
}

