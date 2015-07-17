#include "NotImplementedError.h"

using namespace std;
using namespace regexsf;

NotImplementedError::NotImplementedError()
    : RXLogicError("Not implemented!")
{
}

NotImplementedError::NotImplementedError(const TString& s)
    : RXLogicError(s)
{
}

NotImplementedError::~NotImplementedError() throw ()
{
}
