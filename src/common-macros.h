#ifndef _regexsf_common_macros_H_
#define _regexsf_common_macros_H_

namespace regexsf {

// TODO wyrugowac uzycia RX_STRING (speed) (przerobic loggery)
#define RX_STRING(e) (((std::stringstream&)(((std::stringstream()).flush())<<e)).str())
#define RX_STRING_C(e) ((RX_STRING(e)).c_str())
#define RX_FILE_LOCATION      "["<<__FILE__<<":"<<__LINE__<<" "<<__FUNCTION__<<"] "

#define RX_ERROR(e)                     \
{                                       \
    std::cerr << "ERROR " << (__FILE__) << ":" << (__LINE__) << " " << (__FUNCTION__) << ": " << (RX_STRING(e)) << std::endl; \
}
#define RX_WARNING(e)                   \
{                                       \
    std::cerr << "WARN  " << (__FILE__) << ":" << (__LINE__) << " " << (__FUNCTION__) << ": " << (RX_STRING(e)) << std::endl; \
}
#define RX_INFO(e)                      \
{                                       \
    std::cerr << "INFO  " << (__FILE__) << ":" << (__LINE__) << " " << (__FUNCTION__) << ": " << (RX_STRING(e)) << std::endl; \
}
#define RX_DEBUG(e)                     \
{                                       \
    std::cerr << "DEBUG " << (__FILE__) << ":" << (__LINE__) << " " << (__FUNCTION__) << ": " << (RX_STRING(e)) << std::endl; \
}

#define RX_TRACE                        \
{                                       \
    std::cerr << "TRACE " << (__FILE__) << ":" << (__LINE__) << " " << (__FUNCTION__) << std::endl; \
}

#define RX_TRACE_MSG(e)                 \
{                                       \
    std::cerr << "TRACE " << (__FILE__) << ":" << (__LINE__) << " " << (__FUNCTION__) << ": " << (RX_STRING(e)) << std::endl; \
}

#define RX_NEW(p,e)                     \
{                                       \
    regexsf::MemoryManager::getInstance().registerNew(__FILE__, __LINE__); \
    p = new e;                          \
}

#define RX_NEW_ARRAY(p,e,sz)            \
{                                       \
    regexsf::MemoryManager::getInstance().registerNewArray(__FILE__, __LINE__); \
    p = new e[sz];                      \
}

#define RX_DELETE(p)                    \
{                                       \
    regexsf::MemoryManager::getInstance().registerDelete(__FILE__, __LINE__); \
    delete p;                           \
    p = NULL;                           \
}

#define RX_DELETE_VALUE(p)              \
{                                       \
    regexsf::MemoryManager::getInstance().registerDelete(__FILE__, __LINE__); \
    delete p;                           \
}

#define RX_DELETE_ARRAY(p)              \
{                                       \
    regexsf::MemoryManager::getInstance().registerDeleteArray(__FILE__, __LINE__); \
    delete [] p;                        \
    p = NULL;                           \
}

#define RX_THROW_OBJ(e)                 \
{                                       \
    throw e;                            \
}

#define RX_THROW(t)                     \
{                                       \
    t e;                                \
    e.setFileName(__FILE__);            \
    e.setFunctionName(__FUNCTION__);    \
    e.setLineNumber(__LINE__);          \
    throw e;                            \
}

#define RX_THROW_ARGS(t,args)           \
{                                       \
    t e(args);                          \
    e.setFileName(__FILE__);            \
    e.setFunctionName(__FUNCTION__);    \
    e.setLineNumber(__LINE__);          \
    throw e;                            \
}

#define RX_THROW_STREAM(t,s)            \
{                                       \
    TStringStream ss;                   \
    ss << s;                            \
    RX_THROW_ARGS(t,ss.str());          \
}

#define RX_MEMCPY(dest,src,sz)          \
{                                       \
    memcpy(dest,src,sz);                \
}

#define RX_MEMZERO(p,sz)                \
{                                       \
    memset(p,0,sz);                     \
}

};

#endif
