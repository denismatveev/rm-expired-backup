#include"filelist.h"
#include<string.h>
/* A collection of functions for building list of files and directories */

filelist create_filelist(void)
{
    filelist fl;

    if((fl=(filelist)malloc(sizeof(__filelist))) == NULL)
        return NULL;
    if((fl->array=(d_element_t*)calloc(ARRAY_SIZE,sizeof(__DirElement))) == NULL)
        return NULL;
    fl->size=ARRAY_SIZE; //size of an array of structures d_element_t
    fl->q=0; //current number of elements

    return fl;
}

void close_filelist(filelist fl)
{
    unsigned int i;
    for(i=0;i < fl->q;i++)
        remove_d_element(fl->array[i]);

    free(fl->array);
    free (fl);


    return;
}

int insert_into_filelist(filelist fl, const d_element_t de)
{
    d_element_t *newarr;
    
    if(fl->q >= MAX_Q_EL)
        return 1;
    if(fl->q < fl->size)
    {
        fl->array[(fl->q)++]=de;

        return 0;

    }
    else if(fl->q >= fl->size)
    {
        if((newarr=(d_element_t*)realloc(fl->array,(fl->size+ARRAY_SIZE)*sizeof(__DirElement))) == NULL)
            return  ALLOCATION_ERROR;
        fl->array=newarr;

        fl->size+=ARRAY_SIZE;
        fl->array[(fl->q)++]=de;

        return 0;

    }
    else return 1;
}

d_element_t create_d_element (const char *path)
{
    d_element_t a;
    /* size including '\0' */
    unsigned int size=strlen(path)+1;

    if((a=(d_element_t)malloc(sizeof(__DirElement))) == NULL)
        return NULL;
    if((a->fullpath=(char*)calloc(size, sizeof(char*))) == NULL)
        return NULL;

    a->fullpathlength=size;
    strcpy(a->fullpath,path);

    return a;
}
/* size - это размер на который нужно увеличить буфер */
int expand_d_element(d_element_t a, const unsigned int size)
{
    //d_element_t a_t;
    char *new;
    unsigned int newsize=a->fullpathlength+size+1;

    if((new=(char*)realloc(a->fullpath,(newsize)*sizeof(char*))) == NULL)
        return ALLOCATION_ERROR;
    a->fullpath=new;
    a->fullpathlength=newsize;

    return 0;
}
/* remove_d_element() is used only in closefilelist() and due to it doesn't require filelist as its argument */
void remove_d_element(d_element_t t)
{
    free(t->fullpath);
    free (t);

    return;
}

