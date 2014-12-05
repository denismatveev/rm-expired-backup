#ifndef _WRITELOG_
#define _WRITELOG_
#include<syslog.h>
#include<stdio.h>
/*

    wrapper to syslog
    writes logs to syslog

*/
int WriteLog(const char*);

#endif
