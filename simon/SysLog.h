#pragma once
#include <stdio.h>

class CSysLog
{
public:
    CSysLog();
    ~CSysLog();

    void writeLog(const char *s);
    void writeLog(const char *message, const char *file, int line);
    void writeLog(const char *message, const char *file, const char *func, int line);

private:
    FILE *m_fp;
};
#define WRITE_LOG(msg)  do{         \
                            CSysLog sl;          \
                            sl.writeLog(msg,__FILE__,__FUNCTION__,__LINE__);\
                        }while(0)
