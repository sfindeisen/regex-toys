#ifndef _regexsf_parser_ast_AbstractRegexSequence_H_
#define _regexsf_parser_ast_AbstractRegexSequence_H_

#include <vector>
#include "AbstractRegex.h"

namespace regexsf {

class AbstractRegexSequence : public AbstractRegex {
    public:
        virtual ~AbstractRegexSequence();

        /** Returns true if this abstract sequence has no subexpressions. */
        bool isEmpty() const;
        /** Returns the number of subexpressions in this abstract sequence. */
        int seqLength() const;

    protected:
        AbstractRegexSequence(const std::vector<AbstractRegex*>& v);
        virtual TString asString() const;
        virtual TString asString_seqType() const =0;

    private:
        friend class CFABuilder;

        std::vector<AbstractRegex*> seq;    // owned
};

};

#endif
