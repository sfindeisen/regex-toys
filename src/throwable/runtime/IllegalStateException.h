#ifndef _regexsf_throwable_runtime_IllegalStateException_H_
#define _regexsf_throwable_runtime_IllegalStateException_H_

#include "RXRuntimeException.h"

namespace regexsf {

class IllegalStateException : public regexsf::RXRuntimeException {
    public:
        IllegalStateException();
        IllegalStateException(const char * msg);
        IllegalStateException(const std::string& msg);
        virtual ~IllegalStateException() throw();

        virtual TString getName() const;
};

inline TString IllegalStateException::getName() const {
    return "regexsf::IllegalStateException";
}

};

#endif
