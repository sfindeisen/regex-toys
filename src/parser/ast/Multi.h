#ifndef _regexsf_parser_ast_Multi_H_
#define _regexsf_parser_ast_Multi_H_

#include "../../common.h"

namespace regexsf {

enum class MultiType {ZeroOrMore, OneOrMore, ZeroOrOne, Exact, Range};

class Multi {
    public:
        Multi(const MultiType& m);
        Multi(const MultiType& m, unsigned int value);
        Multi(const MultiType& m, unsigned int lo, unsigned int hi);
        virtual ~Multi();
    private:
        MultiType mt;
        unsigned int lo;
        unsigned int hi;
};

};

#endif
