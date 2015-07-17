#ifndef _regexsf_parser_ast_AbstractRegexSequence_H_
#define _regexsf_parser_ast_AbstractRegexSequence_H_

#include <vector>
#include "AbstractRegex.h"

namespace regexsf {

class AbstractRegexSequence : public AbstractRegex {
    public:
        virtual ~AbstractRegexSequence();
    protected:
        AbstractRegexSequence(const std::vector<AbstractRegex*>& v);
        virtual TString asString() const;
        virtual TString asString_seqType() const =0;
    private:
        std::vector<AbstractRegex*> seq;    // owned
};

};

#endif
