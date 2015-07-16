#ifndef _regexsf_automaton_State_H_
#define _regexsf_automaton_State_H_

#include <map>
#include "../common.h"

namespace regexsf {

class State {
    public:
        State();
        virtual ~State();

        void putNext(char c, const State* s);
        TString asString() const;

    private:
        std::map<char,const State*> next;
};

};

#endif
