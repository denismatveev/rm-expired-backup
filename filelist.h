#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#define ARRAY_SIZE 14
#define DISCR 5
enum __type {
    dir, 
    file
};
typedef __type type; 
struct __DirElement {
    char *name; // name of file or dir
    char *path; // path to file or dir
    time_t mtime; // modification file
    unsigned int type;//dir or file
};

typedef struct __DirElement* d_element_t;

struct __filelist {
    d_element_t array*;
    unsigned int size;
    unsigned int q;
};
typedef struct __filelist* filelist;
filelist createfilelist(void);
int insertintofilelist(const d_element_t, filelist);
void closefilelist(filelist); // delete list and free the memory


filelist createfilelist(void)
{
    filelist fl;

    if(fl=(filelist)malloc(sizeof(struct filelist) == NULL)
        return NULL;
    if((fl->array=(d_element_t)calloc(ARRAY_SIZE,sizeof(d_element_t))) == NULL)
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
    
    if(fl->q < fl->size)
    {
        fl->array[(fl->q)++]=de;

        return 0;

    }
    else if(fl->q >= fl->size)
    {
        if((newel=(d_element_t*)realloc(fl->array,(ARRAY_SIZE+DISCR)*sizeof(d_element_t) == NULL))
            return 1;

        fl->size=fl->size+DISCR;

    }
    else return 1;


    return 0;

}



