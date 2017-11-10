//----------------------------------------------------------------------------------------------------------------------
/*!
* @file      log.cpp
*
* @brief     Function definitions of the logger file.
*
* @details   Often while development of an application, we come across the scenario where we can't just debug the applications.
*            It becomes so tedious to trace for bugs and errors. By keeping that problem in mind, I have written this file.
*            By using this file in your application, you can generate the log file which will contain any data in any format you want.

* @remark    Currently this logger can only be used with windows application. Anyone willing to make it compatible for cross-platform
*            can contribute here.
*
*@remark     For now following parameters are printed in log file: LogTime, ThreadID, AppName, FuncName, LogMsg.
*            You have liberty to modify the functions as per your requirement.
*
* @author   Sonu Gupta
*/
//----------------------------------------------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////
//  H E A D E R S.
/////////////////////////////////////////////////////////////////////
#include<time.h>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<fstream>
#include<strsafe.h>
#include<conio.h>
#include<io.h>
#include "log.h"
using namespace std;


USE_LOG();

//----------------------------------------------------------------------------------
/*!
* @brief Sets Log file configuration such as file name, Application name, trace levels etc.
* @param[in] pszAppname   Pointer to message filled with the COM_MESSAGE structure
* @param[in] pszLogFilePath  Server or Client entry
* @param[in] pszBackupFilePath  Server or Client entry
* @param[in] uiSupportedTraceLevel  Server or Client entry
* @param[in] dwcbLogFileSize  Server or Client entry
* @return Boolean value based on success or failure.
*/
//----------------------------------------------------------------------------------
BOOLEAN
CLogger::SetLogConfiguration(
  char* pszAppname,
  char* pszLogFilePath,
  char* pszBackupFilePath,
  UINT uiSupportedTraceLevel,
  DWORD dwcbLogFileSize
)
{
  if (NULL == pszAppname)
  {
    return FALSE;
  }
  else
  {
    strcpy_s(m_szAppname, _countof(m_szAppname), pszAppname);
  }

  if (NULL == pszLogFilePath)
  {
    return FALSE;
  }
  else
  {
    strcpy_s(m_szLogFilePath, _countof(m_szLogFilePath), pszLogFilePath);
  }

  if (NULL == pszBackupFilePath)
  {
    pszBackupFilePath = pszLogFilePath;
    strcpy_s(m_szBackupFilePath, _countof(m_szBackupFilePath), pszBackupFilePath);
  }
  else
  {
    strcpy_s(m_szBackupFilePath, _countof(m_szBackupFilePath), pszBackupFilePath);

  }

  m_uiSupportedTraceLevel = uiSupportedTraceLevel;
  m_dwcbLogFileSize = dwcbLogFileSize ;
  return TRUE;
}

//----------------------------------------------------------------------------------
/*!
* @brief Writes log to log file.
* @param[in] uiLogTraceLevel  Trace level which indicates whether the log is about information / error
* @param[in] pszFuncName  Name of the function in which this function is being called
* @param[in] pszLogMsgFormat  String message to be written
* @return Boolean value based on success or failure.
*/
//----------------------------------------------------------------------------------

BOOLEAN
CLogger::WriteLog(
  UINT uiLogTraceLevel,
  char* pszFuncName,
  char* pszLogMsgFormat,
  ...
)
{
  int i;
  int iCheck;
  int iExists;
  FILE* fp;
  long size;
  time_t now;
  char s[30];
  DWORD dwID;
  va_list args;
  struct tm tim;
  char szLogMsg[MAX_LEN_SIZE];

  //
  //  @details  Gets the time at which log is written,use 'strftime' function
  //  with specified format to get current time.
  //
  now = time(NULL);
  tim = *(localtime(&now));
  i = strftime(s, 30, "%c", &tim);

  //
  //  @details  Gets the thread id by using 'GetcurrentthreadId()'
  //  included in <windows.h>
  //
  dwID = GetCurrentThreadId();

  //
  // @details  write logs with variable arguments.
  //
  va_start(args, pszLogMsgFormat);

  //
  //  @details  Writes formatted data to the specified string. The size of the destination buffer is
  //  provided to the function to ensure that it does not write past the end of this buffer.
  //
  StringCchVPrintfA(szLogMsg, _countof(szLogMsg), pszLogMsgFormat, args);
  va_end(args);

  fp = fopen(m_szLogFilePath, "a");

  if (NULL != fp)
  {
    fprintf(fp, "\n%s\t%08ld\t\%s\t%s\t\t%s", s, dwID, m_szAppname, pszFuncName, szLogMsg);
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    //
    //  @details  Checks the file size ,if size is >1024 create new bakup file of'bak' extension
    //
    if ((size) > (m_dwcbLogFileSize))
    {
      //
      //  @details  Check file exists or not,if exists,delete previous one.
      //  '_access(filename,mode)' is used...must include <io.h>
      //
      iExists = _access(m_szBackupFilePath, 0);

      if (0 == iExists)
      {
        remove(m_szBackupFilePath);
      }
      else
      {
        //
        // @details  file should be closed before renaming
        //
        fclose(fp);
        rename(m_szLogFilePath, m_szBackupFilePath);
        fp = fopen(m_szLogFilePath, "a");
      }
    }
  }
  else
  {
    return FALSE;
  }

  return TRUE;
}

CLogger Log;