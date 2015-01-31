#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include"filelist.h"
#include<string.h>
#include<stdio.h>
#include"scandir.h"
#include<errno.h>
#include"writelog.h"

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
//TODO: ввести wchar_t для отображения символов национальных алфавитов в названии файлов, каталогов


//TODO Добавить поиск по шаблону regex в массиве имен, который получается при чтении конфига
//TODO Добавить аргумент flags чтобы не использовать 100500 аргументов, тем более они могут добавляться/удаляться
//например, WLOG & SK_HIDN будет как писать лог и не показывать скрытые каталоги.
// glob, globfree - find pathnames matching a pattern, free memory from glob()
// fnmatch - match filename or pathname

int myscandir(dirlist dl, filelist fl, const char *path, const int flags)
{
    unsigned short wlog=0;
    unsigned short skip_hidden=0;
    DIR *fd;
    struct dirent *entry;
    struct stat st;

    if(flags == 3)
      {
        wlog=1;
        skip_hidden=1;
      }
    else if(flags == 1)
      wlog=1;
    else if(flags == 2)
      skip_hidden=1;
    else;



/* open a directory and get an descriptor */
    if((fd=opendir(path)) == NULL)
    {
        perror(path);
        if(wlog)
          WriteLog(path);
        return -2;

    }
    /* reading contents of the directory and filling the filelist and the dirlist */
    rewinddir(fd);
    while((entry=readdir(fd)) != NULL)
    {

        d_element_t de;

        if((de=create_d_element(path)) == NULL)
           return 1;
        /* if directories are . and ..  skipping it */
        if(!(strcmp(entry->d_name,".")) || !(strcmp(entry->d_name, "..")))
            continue;
        /* skip hidden dirs and files */
        if(skip_hidden)
          {
            if(entry->d_name[0] == '.')
            continue;
          }


        if( *(path + strlen(path) -1) != '/')
        {
            if(expand_d_element(de, 1))
                return -1;

            strcat(de->fullpath,"/"); // adding a trailing slash
        }

        if(expand_d_element(de, strlen(entry->d_name)))
          /* if got an error of allocation memory */
            return -1;

        strcat(de->fullpath,entry->d_name); //concatenate strings path + name

        if(lstat(de->fullpath, &st))
        {
            if(wlog)
              WriteLog("Cannot stat file or directory");
           perror(entry->d_name);

           return -1;
        }


        switch(st.st_mode & S_IFMT)
        {
        case S_IFREG:
            de->el_type=file;
            break;
        case S_IFDIR:
            de->el_type=dir;
            break;
        default:
            remove_d_element(de);
            continue;
            //de->el_type=other;
            //break;

        }

        de->mtime=st.st_mtime; //modification time
        de->parent_id=NULL; // default NULL. Will be filled at recursivepass() function, points to parent dir
        de->to_delete=0; // default value is not to delete; Will be changed at moment of analysis
        switch(de->el_type)
          {
          case dir:
            if ( insert_into_dirlist(dl,de))
              return -1;
            break;
          case file:
            if(insert_into_filelist(fl,de))
              return -1;
            break;
          default:
            break;
          }
    }


    if(closedir(fd) < 0)
      {
      if(wlog)
        WriteLog("Cannot close directory");
      perror("Cannot close directory\n");
      }


    return dl->q;
}
