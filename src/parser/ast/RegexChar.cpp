#include "RegexChar.h"

using namespace regexsf;

RegexChar::RegexChar(const char c) : AbstractRegex(), value(c) {
}

RegexChar::~RegexChar() {
}

TString RegexChar::asString() const {
    TStringStream ss;
    ss << value << asString_multi();
    return ss.str();
}

