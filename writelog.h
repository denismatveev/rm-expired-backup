#ifndef WRITELOG_H
#define WRITELOG_H

#define LOG_FATAL    (1)
#define LOG_ERR      (2)
#define LOG_WARN     (3)
#define LOG_INFO     (4)
#define LOG_DBG      (5)
//http://stackoverflow.com/questions/327836/multi-file-c-program-how-best-to-implement-optional-logging
extern int loglevel;
int WriteLog(const char *, ...);
#endif // WRITELOG_H

