#include "RegexChoice.h"

using namespace regexsf;

RegexChoice::RegexChoice(const std::vector<AbstractRegex*>& v) : AbstractRegex(), alt(v) {
}

RegexChoice::~RegexChoice() {
}

