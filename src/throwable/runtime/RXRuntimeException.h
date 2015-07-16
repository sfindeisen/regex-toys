#ifndef _regexsf_throwable_runtime_EBRuntimeException_H_
#define _regexsf_throwable_runtime_EBRuntimeException_H_

#include <stdexcept>

#include "../EBThrowableTemplate.h"

namespace regexsf {

typedef RXThrowableTemplate<std::runtime_error> RXRuntimeException;

};

#endif
