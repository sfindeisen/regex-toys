#ifndef _regexsf_parser_ast_RegexChar_H_
#define _regexsf_parser_ast_RegexChar_H_

#include "AbstractRegex.h"

namespace regexsf {

class RegexChar : public AbstractRegex {
    public:
        RegexChar(const char c);
        virtual ~RegexChar();
    private:
        const char value;
};

};

#endif
