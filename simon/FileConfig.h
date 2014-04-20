#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SysLog.h"

class CFileConfig
{
private:
    FILE *m_fp;
public:
    CFileConfig();
    ~CFileConfig();

    unsigned int getIntByString(const char* str);
    float getFloatByString(const char *str);
    void getStringByString(const char *key, char *value);

    int getModules(char **buffer);
};
