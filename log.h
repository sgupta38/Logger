//----------------------------------------------------------------------------------------------------------------------
/*!
* @file      log.h
*
* @brief     Prototypes of the logger file.
*
* @details   Often while development of an application, we come across the scenario where we can't just debug the applications.
*            It becomes so tedious to trace for bugs and errors. By keeping that problem in mind, I have written this file.
             By using this file in your application, you can generate the log file which will contain any data in any format you want.

* @remark    Currently this logger can only be used with windows application. Anyone willing to make it compatible for cross-platform
*            can contribute here.
*
* @author   Sonu Gupta
*/
//----------------------------------------------------------------------------------------------------------------------

#ifndef __LOG_H__
#define __LOG_H__


/////////////////////////////////////////////////////////////////////
//  M A C R O S.
/////////////////////////////////////////////////////////////////////


//
//  Constants for buffer size.
//
#define MAX_LEN_SIZE      200
#define MAX_LEN_APPNAME     30
#define MAX_LEN_LOGFILEPATH   260

//
//  Header files
//

#include <windows.h>

//
//
//
enum LOG_TRACE_LEVEL
{
  WL_INFO = 1,
  WL_ERROR
};


/////////////////////////////////////////////////////////////////////
//  C L A S S E S.
/////////////////////////////////////////////////////////////////////

//*******************************************************************
//
//  Class:
//    CLogger
//
//  Description:
//    The class CLogger declares Member variable and Member functions
//    for creation of Log.
//
//*******************************************************************

class CLogger
{
private:

  DWORD m_dwcbLogFileSize;                            // Log File Size
  UINT m_uiSupportedTraceLevel;                       // Trace Level which indicates whether its Information / Error
  char m_szAppname[MAX_LEN_APPNAME];                  // Application Name
  char m_szLogFilePath[MAX_LEN_LOGFILEPATH];          // Log File Path: This is where log file will be created
  char m_szBackupFilePath[MAX_LEN_LOGFILEPATH];       // Backup File Path: When log file exceeds limit, backup file with this name will be created.

public:

  BOOLEAN
  SetLogConfiguration(
    char* pszAppname,
    char* pszLogFilePath,
    char* pszBackupFilePath = NULL,
    UINT uiSupportedTraceLevel = WL_INFO | WL_ERROR,
    DWORD dwcbLogFileSize = 1024
  );

  BOOLEAN
  WriteLog(
    UINT uiLogTraceLevel,
    char* pszFuncName,
    char* pszLogMsgFormat,
    ...
  );
};

//
//  Following Macro needs to be declared if you want to use Logger.
//

#define USE_LOG()     extern CLogger Log;

//
//  This macro sets the basic log configurations. 
//  Here you need to specify the log files name, application name, Trace levels, log file's maximum size (default 1024KB)
//  

#define SET_LOG_CONFIGURATION(v,w,x,y,z)    Log.SetLogConfiguration(v,w,x,y,z);
//
//  This is the main macro which is responsible for writing the logs in a logfile.
//  Variable arguments are used so that you can provide formatted string.
//
#define WRITE_LOG(TraceLevel, y, z,...)   Log.WriteLog(TraceLevel, y, z, __VA_ARGS__);


#endif  //__LOG_H__