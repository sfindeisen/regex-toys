#ifndef _regexsf_misc_Printable_H_
#define _regexsf_misc_Printable_H_

#include <iostream>

#include "../common-defs.h"
#include "../common-macros.h"

namespace regexsf {

/** A base class for all printable objects. */
class Printable {
    public:
        virtual TString asString() const =0;

    protected:
        Printable();
};

std::ostream& operator<<(std::ostream& stream, const regexsf::Printable& p);

};

#endif
