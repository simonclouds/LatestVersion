#include "StdAfx.h"
#include "SysLog.h"
#include <string.h>
#include "../global.h"

CSysLog::CSysLog()
{
    m_fp = fopen("syslog.txt", "a+");
	if(m_fp == NULL) {
        //std::cout<<"open syslog file failed!"<<std::endl;
	}
}

CSysLog::~CSysLog()
{
    if (m_fp)
        fclose(m_fp);
}

//只写一条信息
void CSysLog::writeLog(const char *message)
{
	char ts[30]={0};
	GetCurrentTimeStr(ts);
	fputs(ts,m_fp);
	fputs("|",m_fp);
	fputs(message, m_fp);
	fputs("\n",m_fp);
}
//消息包含文件名，出错行
void CSysLog::writeLog(const char *message, const char *file, int line)
{
	char error[200];
	sprintf(error, "File=%s|Line=%d|", file, line);
	strcat(error, message);
	strcat(error,"\n");
	writeLog(error);
}
//消息包含文件名，函数名，出错行
void CSysLog::writeLog(const char *message, const char *file,const char *func, int line)
{
	char error[200];
	//char ts[20];
	//GetCurrentTimeStr(ts);
	const char *filename = GetFilenameFromPath(file);
	sprintf(error, "File=%s|Line=%d|Func=%s|", filename, line, func);
	strcat(error, message);
	strcat(error,"\n");
	writeLog(error);
}
