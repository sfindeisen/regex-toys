#include "Multi.h"
#include "../../throwable/runtime/IllegalArgumentException.h"

using namespace regexsf;

Multi::Multi(const MultiType& m)
    : mt(m)
{
    if (! ((MultiType::ZeroOrMore == m) || (MultiType::OneOrMore == m) || (MultiType::ZeroOrOne == m)))
        RX_THROW(IllegalArgumentException);
}

Multi::Multi(const MultiType& m, unsigned int value)
    : mt(m), lo(value), hi(value)
{
    if (MultiType::Exact != m)
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
