#ifndef _regexsf_cfa_CFA_H_
#define _regexsf_cfa_CFA_H_

#include "../misc/Printable.h"
#include "cfa-common.h"

namespace regexsf {

class CFA : public regexsf::Printable {
    public:
        CFA();
        virtual ~CFA();
        TString asString() const;
};

};

#endif
