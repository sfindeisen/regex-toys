#ifndef _regexsf_parser_ast_Multi_H_
#define _regexsf_parser_ast_Multi_H_

#include "../../misc/Printable.h"

namespace regexsf {

/** regex quantifier type */
enum class MultiType {ZeroOrMore, OneOrMore, ZeroOrOne, Exact, AtLeast, Range};

/**
 * regex quantifier
 *
 * It can be isZero, for example: Range from 5 to 2.
 */
class Multi : public regexsf::Printable {
    public:
        Multi(const MultiType& m);
        Multi(const MultiType& m, unsigned int value);
        Multi(const MultiType& m, unsigned int lo, unsigned int hi);
        virtual ~Multi();

        virtual TString asString() const;

        inline unsigned int getLo() const { return lo; }
        inline unsigned int getHi() const { return hi; }
        inline bool isZero() const {
            return (((MultiType::Exact == mt) || (MultiType::Range == mt)) && ((hi < lo) || (0==hi)));
        }
        inline bool hasUpperBound() const {
            return ((MultiType::ZeroOrOne == mt) || (MultiType::Exact == mt) || (MultiType::Range == mt));
        }
    private:
        MultiType mt;
        unsigned int lo;
        unsigned int hi;
};

};

#endif
