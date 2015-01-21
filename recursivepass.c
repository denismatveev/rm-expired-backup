#include<stdlib.h>
#include"filelist.h"
#include"scandir.h"
#define MAXDEPTH 1000

int recursivepass(dirlist, filelist, const char*);
int sort_files_by_name(filelist);
int sort_files_by_date(filelist);

/* Function for passing all subdirectories. Use linked list and binary tree data structures. */
/* Passing of the tree by the method of pass in width                                        */
/* level is a set of dirs having the same path */
int recursivepass(dirlist dl, filelist fl, const char *path)
{
  /* counter of depth level */
  //int level=0;
  //int ndirs;
  unsigned int i=0;
  /* read parent dir (the first iteration) */

  if(myscandir(dl,fl,path))
    return -1;
  //ndirs=dl->q;
  for(i = 0; i < dl->q; i++)
    {
      if(myscandir(dl,fl,dl->array[i]->fullpath))
        return -1;
   //   level++;
    }



  return 0;
}

int sort_files_by_name(filelist fl)
{



  return 0;
}
