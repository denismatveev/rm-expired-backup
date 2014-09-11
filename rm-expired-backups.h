#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#define ARRAY_SIZE 14

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

typedef struct __DirElement *DirElement;


struct filelist {
    DirElement array*;
    unsigned int size;
};
typedef struct filelist* filelist;
filelist createfilelist(void);
int insertintofilelist(DirElement);
int removefromfilelist(DirElement);
void closefilelist(filelist);


