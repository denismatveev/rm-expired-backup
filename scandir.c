#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filelist.h"
#define MAXDEPTH 1000
int scandir(int*, const char*);
int *n;// number of elements in a directory

struct dirent  *entry;
struct stat *st;



int scandir(int *n,const char *path)
{

    DIR *fd;

    if((fd=opendir(path)) == NULL)
    {
        perror(path);
        return 1;
    }
    while((entry=readdir(fd)) != NULL)
    {
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
   

