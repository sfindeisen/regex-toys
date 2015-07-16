#include <cstdint>
#include <climits>

#ifndef _regexsf_common_defs_H_
#define _regexsf_common_defs_H_

#if ((CHAR_BIT) != (8))
#error unsupported char size
#endif

#if ((__SIZEOF_INT__)<(2))
#error sizeof int must be at least 2
#endif
#if ((__SIZEOF_LONG__)<(4))
#error sizeof long must be at least 4
#endif
#if ((__SIZEOF_LONG_LONG__)<(8))
#error sizeof long long must be at least 8
#endif

#include <string>
#include <sstream>

namespace regexsf {

typedef std::string       TString;
typedef std::stringstream TStringStream;

typedef unsigned long ulong;
typedef     long long bigint;

}

#endif
