#include<stdlib.h>
#include"filelist.h"
#include"scandir.h"
#include"writelog.h"
#define MAXDEPTH 1000

int recursivepass(dirlist, filelist, const char*, const int, const int);
int sort_files_by_name(filelist);
int sort_files_by_date(filelist);

/* Function for passing all subdirectories. Use linked list and binary tree data structures. */
/* Passing of the tree by the method of pass in width                                        */
/* level is a set of dirs having the same path */
int recursivepass(dirlist dl, filelist fl, const char *path, const int wlog, const int skip_hidden)
{
  /* counter of depth level */
  //int level=0;
  //int ndirs;
  unsigned int i=0;

  /* read parent dir (the first iteration) */
  if(myscandir(dl,fl,path,wlog, skip_hidden))
    return -1;
  //ndirs=dl->q;
  while(i < dl->q)
    {
      if(myscandir(dl,fl,dl->array[i]->fullpath, wlog, skip_hidden))
        return -1;
    i++;
      //   level++;
    }

  return 0;
}

int sort_files_by_name(filelist fl)
{



  return 0;
}
