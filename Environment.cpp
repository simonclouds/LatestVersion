#include "stdafx.h"
#include "Environment.h"
#include "global.h"

static inline CString getCStringFromFileConfig(const char * name);

CEnvironment::CEnvironment(void)
{
	m_COMnStrForChangerYuan = getCStringFromFileConfig("ChangerYuan");
	m_COMnStrForChangerJiao = getCStringFromFileConfig("ChangerJiao");
	m_COMnStrForNoteAcceptor= getCStringFromFileConfig("NoteAcceptor");
	m_COMnStrForCoinAcceptor= getCStringFromFileConfig("CoinAcceptor");
	m_COMnStrForCardTerminal= getCStringFromFileConfig("CardTerminal");
}


CEnvironment::~CEnvironment(void)
{
}

int CEnvironment::getPapersLast()
{
	return m_papers_last;
}

CString CEnvironment::getCOMForChangerYuan()
{
	return m_COMnStrForChangerYuan;
}

CString CEnvironment::getCOMForChangerJiao()
{
	return m_COMnStrForChangerJiao;
}

CString CEnvironment::getCOMForNoteAcceptor()
{
	return m_COMnStrForNoteAcceptor;
}

CString CEnvironment::getCOMForCoinAcceptor()
{
	return m_COMnStrForCoinAcceptor;
}

CString CEnvironment::getCOMForCardTerminal()
{
	return m_COMnStrForCardTerminal;
}

void CEnvironment::SetNoteAcceptorStatus( bool status )
{
	m_NoteAcceptorStatus = status;
}

bool CEnvironment::GetNoteAcceptorStatus()
{
	return m_NoteAcceptorStatus;
}

void CEnvironment::SetNoteAcceptorEnable( bool status )
{
	m_bNoteAcceptorEnabled = status;
}

bool CEnvironment::IsNoteAcceptorEnabled()
{
	return m_bNoteAcceptorEnabled;
}

static inline CString getCStringFromFileConfig(const char * name)
{
	CFileConfig fc;
	char key[10];
	CString keyStr;
	keyStr.Empty();

	memset(key,0,sizeof(key));
	fc.getStringByString(name,key);
	keyStr.Format("%s",key);

	return keyStr;
}