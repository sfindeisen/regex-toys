#ifndef _regexsf_parser_ast_AbstractRegex_H_
#define _regexsf_parser_ast_AbstractRegex_H_

#include "Multi.h"

namespace regexsf {

class AbstractRegex {
    public:
        virtual ~AbstractRegex();

        bool hasMulti() const;
        void setMulti(Multi* p);
    protected:
        AbstractRegex();
    private:
        Multi* multi;       // owned
};

};

#endif
