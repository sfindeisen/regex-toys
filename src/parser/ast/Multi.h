#ifndef _regexsf_parser_ast_Multi_H_
#define _regexsf_parser_ast_Multi_H_

#include "../../misc/Printable.h"

namespace regexsf {

enum class MultiType {ZeroOrMore, OneOrMore, ZeroOrOne, Exact, AtLeast, Range};

class Multi : public regexsf::Printable {
    public:
        Multi(const MultiType& m);
        Multi(const MultiType& m, unsigned int value);
        Multi(const MultiType& m, unsigned int lo, unsigned int hi);
        virtual ~Multi();

        virtual TString asString() const;
    private:
        MultiType mt;
        unsigned int lo;
        unsigned int hi;
};

};

#endif
