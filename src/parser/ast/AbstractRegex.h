#ifndef _regexsf_parser_ast_AbstractRegex_H_
#define _regexsf_parser_ast_AbstractRegex_H_

#include "../../common.h"

namespace regexsf {

class AbstractRegex {
    public:
        virtual ~AbstractRegex();
    protected:
        AbstractRegex();
};

};

#endif
