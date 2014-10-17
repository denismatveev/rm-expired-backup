#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filelist.h"
int scandir(filelist*, const char*);




int scandir(filelist *fl, const char *path)
{
    DIR *fd;
    char *path;
    struct dirent  *entry;
    struct stat *st;
  
   /* opening the directory */ 
    if((fd=opendir(path)) == NULL)
    {
        perror(path);
        return 1;
    }
    /* reading contetnts of the directory and filling the filelist */
    while((entry=readdir(fd)) != NULL)
    {
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

    


// closing all opend resources
    free(path);
    closefilelist(fl);


    }

    closedir(fd);

    return 0;
}
   

