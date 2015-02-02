#include<stdlib.h>
#include"filelist.h"
#include"scandir.h"
#include"writelog.h"


int sort_files_by_name(filelist);
int sort_files_by_date(filelist);

/* Function for passing all subdirectories. Use linked list and binary tree data structures. */
/* Passing of the tree by the method of pass in width (aka BFS, Breadth-first search)             */
//TODO добавить flags чтобы не использовать 100500 аргументов

int recursivepass(dirlist dl, filelist fl, const char *path, const int flags, const unsigned int max_depth)
{

  unsigned int i=0;
  unsigned int level=1;
  unsigned int n=0;//number of elements on the current step
  if(flags == 3)
    {
      /* read parent dir (the first iteration) */
      if((myscandir(dl,fl,path,WLOG | SKHDN)) == -1) //max_depth  = 1
        return -1;

      if(!max_depth) //maxdepth = 0
        {
          for(i=0;i < dl->q;i++)
            if(myscandir(dl,fl,dl->array[i]->fullpath, WLOG | SKHDN ) == -1)
              return -1;
        }
      else if(max_depth > 1) //max_depth > 1
        {
          i=0;
          for(;level < max_depth;level++)
            {
              n=dl->q;
              for(;i < n;i++)
                if((myscandir(dl,fl,dl->array[i]->fullpath, WLOG | SKHDN)) == -1)
                  return -1;

            }
        }
    }
  else if(flags == 2)
    {
      /* read parent dir (the first iteration) */
      if((myscandir(dl,fl,path, SKHDN)) == -1) //max_depth  = 1
        return -1;

      if(!max_depth) //maxdepth = 0
        {
          for(i=0;i < dl->q;i++)
            if(myscandir(dl,fl,dl->array[i]->fullpath, SKHDN ) == -1)
              return -1;
        }
      else if(max_depth > 1) //max_depth > 1
        {
          i=0;
          for(;level < max_depth;level++)
            {
              n=dl->q;
              for(;i < n;i++)
                if((myscandir(dl,fl,dl->array[i]->fullpath, SKHDN)) == -1)
                  return -1;

            }
        }
    }

  else if(flags == 1)
    {
      if((myscandir(dl,fl,path,WLOG)) == -1) //max_depth  = 1
        return -1;

      if(!max_depth) //maxdepth = 0
        {
          for(i=0;i < dl->q;i++)
            if(myscandir(dl,fl,dl->array[i]->fullpath, WLOG) == -1)
              return -1;
        }
      else if(max_depth > 1) //max_depth > 1
        {
          i=0;
          for(;level < max_depth;level++)
            {
              n=dl->q;
              for(;i < n;i++)
                if((myscandir(dl,fl,dl->array[i]->fullpath, WLOG)) == -1)
                  return -1;

            }
        }
    }
  else
    {
      if((myscandir(dl,fl,path,0)) == -1) //max_depth  = 1
        return -1;

      if(!max_depth) //maxdepth = 0
        {
          for(i=0;i < dl->q;i++)
            if(myscandir(dl,fl,dl->array[i]->fullpath, 0) == -1)
              return -1;
        }
      else if(max_depth > 1) //max_depth > 1
        {
          i=0;
          for(;level < max_depth;level++)
            {
              n=dl->q;
              for(;i < n;i++)
                if((myscandir(dl,fl,dl->array[i]->fullpath, 0)) == -1)
                  return -1;

            }
        }
    }

  return 0;
}
