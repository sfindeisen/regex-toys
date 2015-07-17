#ifndef _regexsf_parser_ast_RegexChoice_H_
#define _regexsf_parser_ast_RegexChoice_H_

#include <vector>

#include "AbstractRegexSequence.h"

namespace regexsf {

class RegexChoice : public AbstractRegexSequence {
    public:
        RegexChoice(const std::vector<AbstractRegex*>& v);
        virtual ~RegexChoice();
    protected:
        virtual TString asString_seqType() const;
};

};

#endif
