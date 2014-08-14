#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int removebackups(char *dirname);

int find_expires_backups(DIR);
int init_stack(void);

struct __DirElement {
    dname[256];
    time_t mtime;
}

typedef struct __DirElement DirElement;
typedef DirElement stack_t;

struct __Stack {
    stack_t Element;
    unsigned int q;
}

typedef __Stack Stack;


