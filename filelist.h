#ifndef __FILELIST__
#define __FILELIST__
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#define ARRAY_SIZE 14
#define INCR 5
enum __type {
    dir, 
    file
};
typedef __type type; 
struct __DirElement {
    char *name; // name of file or dir
    char *path; // path to file or dir
    time_t mtime; // modification file
    unsigned short int type;//dir or file
    unsigned short int id;
    unsigned short int parent_id; //parent id; 0 
    unsigned short int do_delete;
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

#endif
