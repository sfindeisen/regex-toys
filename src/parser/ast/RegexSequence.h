#ifndef _regexsf_parser_ast_RegexSequence_H_
#define _regexsf_parser_ast_RegexSequence_H_

#include <vector>

#include "AbstractRegex.h"

namespace regexsf {

class RegexSequence : public AbstractRegex {
    public:
        RegexSequence(const std::vector<AbstractRegex*>& v);
        virtual ~RegexSequence();
    private:
        std::vector<AbstractRegex*> seq;    // owned
};

};

#endif
