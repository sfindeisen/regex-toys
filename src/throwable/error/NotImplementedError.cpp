#include "NotImplementedError.h"

using namespace std;
using namespace regexsf;

NotImplementedError::NotImplementedError()
    : RXLogicError("Not implemented!")
{
}

NotImplementedError::~NotImplementedError() throw ()
{
}
