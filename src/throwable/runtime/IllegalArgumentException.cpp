#include "IllegalArgumentException.h"

using namespace std;
using namespace regexsf;

IllegalArgumentException::IllegalArgumentException()
    : RXRuntimeException("illegal argument exception")
{
}

IllegalArgumentException::IllegalArgumentException(const char * msg)
    : RXRuntimeException(msg)
{
}

IllegalArgumentException::IllegalArgumentException(const std::string& msg)
    : RXRuntimeException(msg)
{
}

IllegalArgumentException::~IllegalArgumentException() throw ()
{
}
