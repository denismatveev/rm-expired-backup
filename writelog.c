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

//TODO сделать функцию с переменным числом аргументов и можно будет передавать название файла и добавить loglevel(хотя есть LOG_ERR у syslog)
/*
example:
#define LOG_FATAL    (1)
#define LOG_ERR      (2)
#define LOG_WARN     (3)
#define LOG_INFO     (4)
#define LOG_DBG      (5)

#define LOG(level, ...) do {  \
                            if (level <= debug_level) { \
                                fprintf(dbgstream,"%s:%d:", __FILE__, __LINE__); \
                                fprintf(dbgstream, __VA_ARGS__); \
                                fprintf(dbgstream, "\n"); \
                                fflush(dbgstream); \
                            } \
                        } while (0)
extern FILE *dbgstream;
extern int  debug_level;

How to use:

LOG(LOG_ERR, "I/O error %s occured while opening file %s", strerror(errno), filename);

*/
/*

int WriteLog(const int loglevel,const char *formatstr,...)
{
    



}
 




*/
int WriteLog(const char *message)
{
     syslog(LOG_WARNING, "%s%s%s",message, ": ",strerror(errno));

    return 0;
}
