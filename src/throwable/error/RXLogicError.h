#ifndef _regexsf_throwable_error_RXLogicError_H_
#define _regexsf_throwable_error_RXLogicError_H_

#include <stdexcept>

#include "../RXThrowableTemplate.h"

namespace regexsf {

typedef RXThrowableTemplate<std::logic_error> RXLogicError;

};

#endif
