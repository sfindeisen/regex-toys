#ifndef _regexsf_parser_Parser_H_
#define _regexsf_parser_Parser_H_

#include "ast/AbstractRegex.h"

namespace regexsf {

class Parser {
    public:
        Parser();
        virtual ~Parser();

        /** Parse regex tree from a string. */
        AbstractRegex* parse(const TString& s) const;
};

};

#endif
