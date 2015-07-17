#ifndef _regexsf_parser_Parser_H_
#define _regexsf_parser_Parser_H_

#include <utility>
#include "ast/AbstractRegex.h"
#include "ast/Multi.h"

namespace regexsf {

class Parser {
    public:
        Parser();
        virtual ~Parser();

        /** Parse regex tree from a string. */
        AbstractRegex* parse(const TString& s) const;

    private:
        std::pair<AbstractRegex*, unsigned int> parseRegex (const TString& s, const unsigned int pos) const;
        std::pair<AbstractRegex*, unsigned int> parseTerm  (const TString& s, const unsigned int pos) const;
        std::pair<AbstractRegex*, unsigned int> parseFactor(const TString& s, const unsigned int pos) const;
        std::pair<AbstractRegex*, unsigned int> parseAtom  (const TString& s, const unsigned int pos) const;
        std::pair<Multi*,         unsigned int> parseMulti (const TString& s, const unsigned int pos) const;
        std::pair<unsigned int,   unsigned int> parseUInt  (const TString& s, const unsigned int pos) const;
};

};

#endif
