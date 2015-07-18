#ifndef _regexsf_parser_ast_RegexChar_H_
#define _regexsf_parser_ast_RegexChar_H_

#include "AbstractRegex.h"

namespace regexsf {

class RegexChar : public AbstractRegex {
    public:
        RegexChar(const TAlpha c);
        virtual ~RegexChar();

        inline TAlpha getValue() const { return value; }
        virtual RegexType getType() const;
        virtual TString asString() const;
    private:
        const TAlpha value;
};

};

#endif
