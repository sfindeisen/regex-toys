#ifndef _regexsf_throwable_RXThrowableTemplate_H_
#define _regexsf_throwable_RXThrowableTemplate_H_

#include <typeinfo>

#include "RXAbstractThrowable.h"

namespace regexsf {

template <class T> class RXThrowableTemplate : public regexsf::RXAbstractThrowable, public T {
    public:
        RXThrowableTemplate(const TString& s);
        RXThrowableTemplate(const char *s);
        // RXThrowableTemplate(const RXThrowableTemplate& another);
        virtual ~RXThrowableTemplate() throw();
        // virtual RXThrowableTemplate& operator=(const RXThrowableTemplate& another);

        virtual TString getName() const =0;
        virtual TString asString() const;

        const TString& getMessage      () const;
        const TString& getFileName     () const;
        const TString& getFunctionName () const;
        int            getLineNumber   () const;

        void setFileName    (const TString& s);
        void setFunctionName(const TString& s);
        void setLineNumber  (const int i);

    private:
        TString message;
        TString fileName;
        TString funcName;
        int     lineNumber;
};

template <class T> RXThrowableTemplate<T>::RXThrowableTemplate(const char *s)
    : RXAbstractThrowable(), T(s), message(s), fileName(""), funcName(""), lineNumber(0)
{
}

template <class T> RXThrowableTemplate<T>::RXThrowableTemplate(const TString& s)
    : RXAbstractThrowable(), T(s), message(s), fileName(""), funcName(""), lineNumber(0)
{
}

template <class T> RXThrowableTemplate<T>::~RXThrowableTemplate() throw() {
}

template <class T> TString RXThrowableTemplate<T>::asString() const {
    TStringStream ss;
    ss << "RXThrowableTemplate<" << (typeid(T).name()) << "> " << getName() << " at " << getFileName() << ":" << getLineNumber() << " " << getFunctionName() << ": " << getMessage();
    return ss.str();
}

template <class T> const TString& RXThrowableTemplate<T>::getMessage() const {
    return message;
}
template <class T> const TString& RXThrowableTemplate<T>::getFileName() const {
    return fileName;
}
template <class T> const TString& RXThrowableTemplate<T>::getFunctionName() const {
    return funcName;
}
template <class T> int RXThrowableTemplate<T>::getLineNumber() const {
    return lineNumber;
}
template <class T> void RXThrowableTemplate<T>::setFileName(const TString& s) {
    this->fileName = s;
}
template <class T> void RXThrowableTemplate<T>::setFunctionName(const TString& s) {
    this->funcName = s;
}
template <class T> void RXThrowableTemplate<T>::setLineNumber(const int i) {
    this->lineNumber = i;
}

};

#endif
