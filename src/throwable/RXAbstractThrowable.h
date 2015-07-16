#ifndef _regexsf_throwable_RXAbstractThrowable_H_
#define _regexsf_throwable_RXAbstractThrowable_H_

#include "../misc/Printable.h"

namespace regexsf {

/** A common superclass for all RX exceptions. */
class RXAbstractThrowable : public regexsf::Printable {
    public:
        RXAbstractThrowable();
        virtual ~RXAbstractThrowable();
};

};

#endif
