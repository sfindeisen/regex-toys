#ifndef _regexsf_parser_ast_RegexSequence_H_
#define _regexsf_parser_ast_RegexSequence_H_

#include <vector>

#include "AbstractRegexSequence.h"

namespace regexsf {

class RegexSequence : public AbstractRegexSequence {
    public:
        RegexSequence(const std::vector<AbstractRegex*>& v);
        virtual ~RegexSequence();
};

};

#endif
