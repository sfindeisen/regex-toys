#ifndef _regexsf_engine_Engine_H_
#define _regexsf_engine_Engine_H_

#include "../misc/Printable.h"
#include "../cfa/CFA.h"
#include "../parser/ast/AbstractRegex.h"

namespace regexsf {

class Engine : public regexsf::Printable {
    public:
        Engine(const AbstractRegex* regex);
        virtual ~Engine();
        virtual TString asString() const;
    protected:
        CFA* buildCFA(const AbstractRegex* regex) const;
    private:
        CFA* cfa;
};

};

#endif
