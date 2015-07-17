#include "IllegalStateException.h"

using namespace std;
using namespace regexsf;

IllegalStateException::IllegalStateException()
    : RXRuntimeException("illegal state exception")
{
}

IllegalStateException::IllegalStateException(const char * msg)
    : RXRuntimeException(msg)
{
}

IllegalStateException::IllegalStateException(const std::string& msg)
    : RXRuntimeException(msg)
{
}

IllegalStateException::~IllegalStateException() throw ()
{
}
