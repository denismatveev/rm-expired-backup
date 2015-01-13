#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include"filelist.h"
#include<string.h>
#include<stdio.h>
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
fnmatch - match filename or pathname
*/
int myscandir(filelist, const char*);
int myscandir(filelist fl, const char *path)
{
    DIR *fd;
    struct dirent *entry;
    struct stat st;
    char *currentdir;//absolute path to working directory

    currentdir=(char*)malloc(L_NAME*sizeof(char));

    if((fd=opendir(path)) == NULL)
    {
        perror(path);
        return -1;
    }

    if((getcwd(currentdir,L_NAME)) == NULL)
    {
        perror("getcwd:");
        exit(EXIT_FAILURE);
    }


    if(((chdir(path)) < 0))
    {
        WriteLog("scandir: Can't change directory");
        exit(EXIT_FAILURE);
    }

    /* reading contents of the directory and filling the filelist */
    rewinddir(fd);
    while((entry=readdir(fd)) != NULL)
    {
        d_element_t de;

        de=create_d_element(path);
        /* if directories . and .. */
        if(!(strcmp(entry->d_name,".")) || !(strcmp(entry->d_name, "..")))
            continue;


        if((stat(entry->d_name, &st) == -1))
        {
            perror(entry->d_name);

            return -1;
        }


        switch(st.st_mode & S_IFMT)
        {
        case S_IFDIR:
            de->el_type=0;
            break;
        case S_IFREG:
            de->el_type=1;
            break;
        default:
            return -1;

        }

        if(*(path+strlen(path)) != '/')
        {
            if(expand_d_element(de, 1))
                return 1;

            strcat(de->fullpath,"/"); // adding a trailing slash
        }

        if(expand_d_element(de, strlen(entry->d_name)))
            return 1;

        strcat(de->fullpath,entry->d_name); //concatenate strings path + name

        //strcat(de->fullpath,"\0"); //null terminated string
        de->mtime=st.st_mtime; //modification time

        de->parent_id=NULL; // default NULL. Will be filled at recursivepass() function
        de->to_delete=0; // default value is not to delete; Will be changed at moment of analysis

        insertintofilelist(fl,de); //inserting into filelist array

    }

    closedir(fd);
    chdir(currentdir);
    free(currentdir);


    return 0;
}
