#include"filelist.h"
/* A collection of functions for building list of files and directories */

#define MAX_Q_EL 100000 //limit for a hundred thousand records

filelist createfilelist(void)
{
    filelist fl;

    if((fl=(filelist)malloc(sizeof(filelist))) == NULL)
        return NULL;
    if((fl->array=(d_element_t*)calloc(ARRAY_SIZE,sizeof(d_element_t))) == NULL)
        return NULL;
    fl->size=ARRAY_SIZE; //size of an array of structures d_element_t
    fl->q=0; //current number of elements

    return fl;
}

void closefilelist(filelist fl)
{

    free(fl->array);
    free (fl);

    return;
}

int insertintofilelist(const d_element_t de, filelist fl)
{
    d_element_t *newel;
    
    if(fl->q >= MAX_Q_EL)
        return 2;    
    if(fl->q < fl->size)
    {
        fl->array[(fl->q)++]=de;

        return 0;

    }
    else if(fl->q >= fl->size)
    {
        newel=(d_element_t*)realloc(fl->array,(ARRAY_SIZE+INCR)*sizeof(d_element_t));
        if(newel == NULL)
            return 1;
        
        fl->size=fl->size+INCR;
        fl->array[(fl->q)++]=de;
         
        return 0;

    }
    else return 1;
}
