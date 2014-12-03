#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include"filelist.h"
#include<string.h>
#include<stdio.h>
#include<syslog.h>
/*

Possible filenames at an incremental backup dir:

ibdata1.delta
ibdata1.meta
ibdata2.delta
ibdata2.meta

digits in the general case may vary. At the current moment files present only ibdata1 and ibdata2

mysql-incr-[1][0-4].tar.gz
xtrabackup_checkpoints
xtrabackup_logfile

Possible filenames at a full backup dir are:

ibdata1
ibdata2
mysql-0.tar.gz
xtrabackup_checkpoints
xtrabackup_logfile

The best idea is to use conf file with a list of filenames. It is TODO.
Catalogs have got names like this 20141104-2000-0; date-time-number as YYYYMMDD-HHMM-N

*/
int WriteLog(const char*);
int myscandir(filelist, const char*);



int WriteLog(const char *message)
{

    openlog(NULL,LOG_CONS | LOG_PERROR , LOG_LOCAL0);
    syslog(LOG_LOCAL0 | LOG_ERR, "%s",message);

    closelog();

    return 0;
}



int myscandir(filelist fl, const char *path)
{
    DIR *fd;
    struct dirent *entry;
    struct stat *st;

    if((strlen(path) > L_NAME))
    {
        WriteLog("scan_dir: path is too long");
        return -1;
    }
    if((fd=opendir(path)) == NULL)
    {
        perror(path);
        return 1;
    }

    /* reading contents of the directory and filling the filelist */
    while((entry=readdir(fd)) != NULL)
    {
        d_element_t de;

        if((stat(entry->d_name,st)) == -1)
        {
            perror(entry->d_name);

            return 1;
        }


        switch(st->st_mode)
        {
        case S_IFDIR:
            de->el_type=dir;
            break;
        case S_IFREG:
            de->el_type=file;
            break;
        default:
            return -1;
        }

        strcpy(de->fullpath,path);
        strcat(de->fullpath,"/"); // adding a trailing slash
        strcat(de->fullpath,entry->d_name); //concatenate strings path + name

        de->mtime=st->st_mtime; //modification time

        de->parent_id=NULL; // default NULL. Will be filled at recursivepass() function
        de->to_delete=0; // default value is not to delete; Will be changed at moment of analysis
        insertintofilelist(de,fl); //inserting into filelist array
    }

    closedir(fd);

    return 0;
}
