#include "RegexChar.h"

using namespace regexsf;

RegexChar::RegexChar(const char c) : AbstractRegex(), value(c) {
}

RegexChar::~RegexChar() {
}

TString RegexChar::asString(const TString& indent) const {
    TString s(indent);
    s.push_back(value);
    return s;
}

