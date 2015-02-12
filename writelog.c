#include<stdio.h>
#include<syslog.h>
#include<errno.h>
#include<string.h>
/*
    file  writelog.c is wrapper to syslog;
    writes logs to syslog's local0
    It is needed for writing logs when program works as a daemon
    //http://stackoverflow.com/questions/327836/multi-file-c-program-how-best-to-implement-optional-logging
*/

//TODO сделать функцию с переменным числом аргументов и можно будет передвать название файла и добавить loglevel(хотя есть LOG_ERR у syslog)
int WriteLog(const char *message)
{
     syslog(LOG_WARNING, "%s%s%s",message, ": ",strerror(errno));

    return 0;
}
