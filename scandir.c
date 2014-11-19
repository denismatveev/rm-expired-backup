#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include"filelist.h"
#include<string.h>

int myscandir(filelist, const char*);

int myscandir(filelist fl, const char *path)
{
    DIR *fd;
    struct dirent *entry;
    struct stat *st;


    /* opening the directory */
    if(strlen(path) > 1024)
        return 2;
    if((fd=opendir(path)) == NULL)
    {
        perror(path);
        return 1;
    }

    /* reading contents of the directory and filling the filelist */
    while((entry=readdir(fd)) != NULL)
    {
        d_element_t de;

        if(stat(entry->d_name,st) == -1)
        {
            perror(entry->d_name);

            return 1;
        }

        strcpy(de->name,entry->d_name); // copy name of directory

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

        strcpy(de->path,path);
        strcat(de->path,"/"); // adding a trailing slash
        strcat(de->path,de->name); //concatenate strings path + name

        de->mtime=st->st_mtime; //modification time

        de->parent_id=NULL; // default NULL. Will be filled at recursivepass() function
        de->to_delete=0; // default value is not to delete; Will be changed at moment of analysis
        insertintofilelist(de,fl);
    }

    closedir(fd);

    return 0;
}
