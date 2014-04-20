#include "StdAfx.h"
#include "FileConfig.h"

CFileConfig::CFileConfig()
{
    m_fp = fopen("config.ini", "r");
	if(m_fp == NULL){
        WRITE_LOG("Open config.ini Failed!");
	}
}

CFileConfig::~CFileConfig()
{
    if (m_fp)
        fclose(m_fp);
}

unsigned int CFileConfig::getIntByString(const char* s)
{
    char buffer[50];
	int len;
	char *p;

	while(fgets(buffer, 50, m_fp)!=NULL)
	{
		p = strtok(buffer, "=");
		if(strcmp(p, s)==0)
			break;
	}
	p = strtok(NULL, "=");
	fseek(m_fp, 0, SEEK_SET);

	return atoi(p);
}

float CFileConfig::getFloatByString(const char *s)
{
    char buffer[50];
	int len;
	char *p;

	while(fgets(buffer, 50, m_fp)!=NULL)
	{
		p = strtok(buffer, "=");
		if(strcmp(p, s)==0)
			break;
	}
	p = strtok(NULL, "=");
	fseek(m_fp, 0, SEEK_SET);

	return atof(p);
}

int CFileConfig::getModules(char **buffer)	//注意在外面要释放内存。
{
	char tmp[50];
	int len;
	char *p;
	int i = 0;
	int num = 0;

	fseek(m_fp, 0, SEEK_SET);

	while(fgets(tmp, 50, m_fp)!=NULL)
	{
		p = strtok(tmp, "=");
		if(strcmp(p, "MODULENUM")==0)
			break;
	}
	p = strtok(NULL, "=");
	num = atoi(p);

	for(; i < num; i++)
	{
		memset(tmp , 0, 50);
		fgets(tmp, 50, m_fp);
		strncpy(buffer[i], tmp, strlen(tmp)-1);
	}

	fseek(m_fp, 0, SEEK_SET);
	return 1;
}

void CFileConfig::getStringByString(const char * key, char * value)
{
	char buffer[50];
	int len;
	char *p;
    fseek(m_fp, 0, SEEK_SET);
	while(fgets(buffer, 50, m_fp)!=NULL)
	{
		p = strtok(buffer, "=");
		if(strcmp(p, key)==0)
			break;
	}
	p = strtok(NULL, "=");
	strncpy(value, p, strlen(p)-1);
	fseek(m_fp, 0, SEEK_SET);
}
