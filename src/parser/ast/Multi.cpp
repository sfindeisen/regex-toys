#include "Multi.h"
#include "../../throwable/error/NotImplementedError.h"
#include "../../throwable/runtime/IllegalArgumentException.h"

using namespace regexsf;

Multi::Multi(const MultiType& m)
    : Printable(), mt(m), lo(0), hi(0)
{
    switch (m) {
        case MultiType::ZeroOrMore:
            break;
        case MultiType::OneOrMore:
            lo = 1;
            break;
        case MultiType::ZeroOrOne:
            hi = 1;
            break;
        default:
            RX_THROW(IllegalArgumentException);
    }
}

Multi::Multi(const MultiType& m, unsigned int value)
    : mt(m), lo(value), hi(value)
{
    if (! ((MultiType::Exact == m) || (MultiType::AtLeast == m)))
        RX_THROW(IllegalArgumentException);
}

Multi::Multi(const MultiType& m, unsigned int lo, unsigned int hi)
    : mt(m), lo(lo), hi(hi)
{
    if (MultiType::Range != m)
        RX_THROW(IllegalArgumentException);
}

Multi::~Multi() {
}

TString Multi::asString() const {
    TStringStream ss;

    switch (mt) {
        case MultiType::ZeroOrMore:
            return "*";
        case MultiType::OneOrMore:
            return "+";
        case MultiType::ZeroOrOne:
            return "?";
        case MultiType::Exact:
            ss << '{' << lo << '}';
            return ss.str();
        case MultiType::AtLeast:
            ss << '{' << lo << "+}";
            return ss.str();
        case MultiType::Range:
            ss << '{' << lo << ';' << hi << '}';
            return ss.str();
        default:
            RX_THROW(NotImplementedError);
    }
}

