#include<stdio.h>
#include<syslog.h>
#include<errno.h>
#include<string.h>
/*
    file  writelog.c is wrapper to syslog;
    writes logs to syslog's local0
    It is needed for writing logs when program works as a daemon

*/

//TODO сделать функцию с переменным числом аргументов и можно будет передвать название файла и добавить loglevel(хотя есть LOG_ERR у syslog)
int WriteLog(const char *message)
{
    openlog(NULL, LOG_CONS, LOG_LOCAL0);

    syslog(LOG_LOCAL0 | LOG_ERR, "%s%s",message, strerror(errno));

    closelog();
    return 0;
}
