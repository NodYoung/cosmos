#include "glog/logging.h"

#define DISALLOW_COPY_AND_ASSIGN(classname)\
private:\
classname(const classname&);\
classname& operator = (const classname&);

#define DISALLOW_IMPLICIT_CONSTRUCTORS(classname)\
private:\
classname();\
DISALLOW_COPY_AND_ASSIGN(classname)

#define DECLARE_PERCEPTION_SINGLETON(classname)\
public:\
    static classname * instance() {\
        static classname instance;\
        return &instance;\
    };\
\
DISALLOW_IMPLICIT_CONSTRUCTORS(classname)\
\
private:

#define QUIT_IF(condition, ret, format, ...) \
do { \
    const int max_len = 8192 * 16; \
    char msg[max_len]; \
    snprintf(msg, max_len, format, ##__VA_ARGS__); \
    char msg_err[max_len]; \
    snprintf(msg_err, max_len, "[errno:%d]", static_cast<int>(ret)); \
    if (condition) { \
        LOG(ERROR) << msg << msg_err; \
        return ret; \
    } \
} while (0);

