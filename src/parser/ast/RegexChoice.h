#ifndef _regexsf_parser_ast_RegexChoice_H_
#define _regexsf_parser_ast_RegexChoice_H_

#include <vector>

#include "AbstractRegex.h"

namespace regexsf {

class RegexChoice : public AbstractRegex {
    public:
        RegexChoice(const std::vector<AbstractRegex*>& v);
        virtual ~RegexChoice();
    private:
        std::vector<AbstractRegex*> alt;    // owned
};

};

#endif
