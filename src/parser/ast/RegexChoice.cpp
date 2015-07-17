#include "RegexChoice.h"

using namespace regexsf;

RegexChoice::RegexChoice(const std::vector<AbstractRegex*>& v) : AbstractRegexSequence(v) {
}

RegexChoice::~RegexChoice() {
}

