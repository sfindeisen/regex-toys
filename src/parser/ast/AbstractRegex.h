#ifndef _regexsf_parser_ast_AbstractRegex_H_
#define _regexsf_parser_ast_AbstractRegex_H_

#include <vector>
#include "../../common.h"
#include "Multi.h"

namespace regexsf {

class AbstractRegex : public regexsf::Printable {
    public:
        virtual ~AbstractRegex();

        /** this regex as at least 1 multiplicity specifier */
        bool hasMulti() const;

        /** push new multiplicity specifier on top of the stack (this one becoming the most external) */
        void pushMulti(Multi* p);
    protected:
        AbstractRegex();
        TString asString_multi() const;
    private:
        friend class Engine;
        /** multiplicity specifications (there can be more than 1, in which case the first is the deepest */
        std::vector<Multi*> multi;       // owned
};

};

#endif
