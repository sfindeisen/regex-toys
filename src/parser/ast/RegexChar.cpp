#include "RegexChar.h"

using namespace regexsf;

RegexChar::RegexChar(const char c) : AbstractRegex(), value(c) {
}

RegexChar::~RegexChar() {
}

inline RegexType RegexChar::getType() const {
    return RegexType::RXChar;
}

TString RegexChar::asString() const {
    TStringStream ss;
    ss << value << asString_multi();
    return ss.str();
}

