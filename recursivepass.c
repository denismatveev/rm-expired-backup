#include<stdlib.h>
#include"filelist.h"
#include"scandir.h"
#include"writelog.h"


int sort_files_by_name(filelist);
int sort_files_by_date(filelist);

/* Function for passing all subdirectories. Use linked list and binary tree data structures. */
/* Passing of the tree by the method of pass in width(BFS, Breadth-first search)             */
/* level is a set of dirs that has the same parent  */
int recursivepass(dirlist dl, filelist fl, const char *path, const int wlog, const int skip_hidden, const unsigned int max_depth)
{

  unsigned int i=0;
  unsigned int level=1;
  unsigned int b;

  /* read parent dir (the first iteration) */
  if(myscandir(dl,fl,path,wlog, skip_hidden)) //max_depth  = 1
    return -1;

  if(!max_depth) //maxdepth = 0
    while(i < dl->q)
      {
        if(myscandir(dl,fl,dl->array[i]->fullpath, wlog, skip_hidden))
          return -1;
        i++;
      }

  else if(max_depth > 1)
    while(level < max_depth && i < dl->q)
      {
        b=dl->q;// how many elements were in a list
        if(myscandir(dl,fl,dl->array[i]->fullpath, wlog, skip_hidden))
          return -1;

        if(i<b) // how many elements has been added
          level++;
         i++;
      }
  else ;

  return 0;
}

int sort_files_by_name(filelist fl)
{



  return 0;
}
