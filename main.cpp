//----------------------------------------------------------------------------------------------------------------------
/*!
* @file      main.cpp
*
* @brief     Sample file delineates usage of logger 
*
* @author   Sonu Gupta
*/
//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "log.h"
using namespace std;

//
// This is must if you want to use logger.
//
USE_LOG();

int
main()
{

  //
  //@details This is must at startup
  //
  SET_LOG_CONFIGURATION("Looger.exe", "TestLog.log", "TestLog.bak", WL_INFO | WL_ERROR, 1024);

  //
  //@details  Start writing Logs
  //
  WRITE_LOG(WL_INFO, "In Main()", "Here, you will write the message you want to write be it info/error.");

  return 0;
}