#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filelist.h"

int scandir(filelist*, const char*);

int scandir(filelist *fl, const char *path)
{
    DIR *fd;
    struct dirent  *entry;
    struct stat *st;
    d_element_t de;
   /* opening the directory */
    if((fd=opendir(path)) == NULL)
    {
        perror(path);
        return 1;
    }
    /* reading contents of the directory and filling the filelist */
    while((entry=readdir(fd)) != NULL)
    {
      de->name=
      de->path
      de->mtime
      de->el_type;
      de->parent_id
      de->to_delete
      insertintofilelist(,fl)

      if(stat(dirent->d_name,st) == -1)
      {
          perror(dirent->d_name);

          return 1;
      }
     if(S_ISDIR(st->st_mode))
         dir_element->el_type=0;
     else if(S_ISREG(st->st_mode))
         dir_element->el_type=1;
    else return -1;

    }

    closedir(fd);

    return 0;
}


