#include<stdio.h>
#include<syslog.h>

/*
    file  writelog.c is wrapper to syslog;
    writes logs to syslog's local0

*/

int WriteLog(const char *);
int WriteLog(const char *message)
{

    openlog(NULL,LOG_CONS | LOG_PERROR , LOG_LOCAL0);
    syslog(LOG_LOCAL0 | LOG_ERR, "%s",message);

    closelog();

    return 0;
}
