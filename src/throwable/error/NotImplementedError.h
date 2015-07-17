#ifndef _regexsf_throwable_error_NotImplementedError_H_
#define _regexsf_throwable_error_NotImplementedError_H_

#include "RXLogicError.h"

namespace regexsf {

class NotImplementedError : public regexsf::RXLogicError {
    public:
        NotImplementedError();
        NotImplementedError(const TString& s);
        virtual ~NotImplementedError() throw();

        virtual TString getName() const;
};

inline TString NotImplementedError::getName() const {
    return "regexsf::NotImplementedError";
}

};

#endif
