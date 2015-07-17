#ifndef _regexsf_parser_ast_AbstractRegex_H_
#define _regexsf_parser_ast_AbstractRegex_H_

#include "../../common.h"
#include "Multi.h"

namespace regexsf {

class AbstractRegex : public regexsf::Printable {
    public:
        virtual ~AbstractRegex();

        bool hasMulti() const;
        void setMulti(Multi* p);

        virtual TString asString() const;
    protected:
        AbstractRegex();
        virtual TString asString(const TString& indent) const =0;
        TString asString_other(const AbstractRegex& other, const TString& indent) const;
    private:
        Multi* multi;       // owned
};

};

#endif
