#ifndef _regexsf_throwable_runtime_IllegalArgumentException_H_
#define _regexsf_throwable_runtime_IllegalArgumentException_H_

#include "RXRuntimeException.h"

namespace regexsf {

class IllegalArgumentException : public regexsf::RXRuntimeException {
    public:
        IllegalArgumentException();
        IllegalArgumentException(const char * msg);
        IllegalArgumentException(const std::string& msg);
        virtual ~IllegalArgumentException() throw();

        virtual TString getName() const;
};

inline TString IllegalArgumentException::getName() const {
    return "regexsf::IllegalArgumentException";
}

};

#endif
