#include"filelist.h"
#include<string.h>

/* A collection of functions for building list of files and directories */

dirlist create_dirlist(void)
{
    dirlist dl;

    if((dl=(dirlist)malloc(sizeof(__dirlist))) == NULL)
        return NULL;
    if((dl->array=(d_element_t*)calloc(ARRAY_SIZE,sizeof(__DirElement))) == NULL)
        return NULL;
    dl->size=ARRAY_SIZE; //size of an array of structures d_element_t
    dl->q=0; //current number of elements

    return dl;
}

void close_dirlist(dirlist dl)
{
    unsigned int i;
    for(i=0;i < dl->q;i++)
        remove_d_element(dl->array[i]);

    free(dl->array);
    free (dl);


    return;
}

int insert_into_dirlist(dirlist dl, const d_element_t de)
{
    d_element_t *newarr;

    if(dl->q >= MAX_Q_EL)
        return 1;
    if(dl->q < dl->size)
    {
        dl->array[(dl->q)++]=de;

        return 0;

    }
    else if(dl->q >= dl->size)
    {
        if((newarr=(d_element_t*)realloc(dl->array,(dl->size+ARRAY_SIZE)*sizeof(__DirElement))) == NULL)
            return  ALLOCATION_ERROR;
        dl->array=newarr;

        dl->size+=ARRAY_SIZE;
        dl->array[(dl->q)++]=de;

        return 0;

    }
    else return 1;
}
