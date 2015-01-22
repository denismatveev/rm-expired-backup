/***************************************************************************
 *            filelist.h
 *
 *  Пн. Декабрь 15 15:18:28 2014
 *  Copyright  2014  denis matveev
 *  <denis@ilmen-tau.ru>
 ****************************************************************************/
#ifndef __FILELIST__
#define __FILELIST__
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#define ARRAY_SIZE 14 //initial size of an array
#define ALLOCATION_ERROR 2
#define MAX_Q_EL 100000 //limit for a hundred thousand records


/* element types */
enum __type {
    dir,
    file,
    other
};
typedef enum __type* type_t;

/* Dir element */
typedef struct  {
    char *fullpath; // absolute path to file or dir;
    //unsigned int fullpathlength;
    time_t mtime; // modification time of file
    unsigned short int el_type;//element type dir or file
    struct  __DirElement *parent_id; //parent id; NULL if no parent or it is a directory
    unsigned short int to_delete; //flag if element marked to delete
}__DirElement;
typedef __DirElement* d_element_t;

d_element_t create_d_element(const char *);
int expand_d_element(d_element_t, const unsigned int);
void remove_d_element(d_element_t);

/* filelist */
typedef struct {
    d_element_t *array;
    unsigned int size;//size of an array of d_element_t
    unsigned int q;//current number of elements
} __filelist;
typedef __filelist* filelist;

filelist create_filelist(void);
int insert_into_filelist(filelist, const d_element_t);
void close_filelist(filelist); // delete list and free the memory

/* dirlist */

typedef struct {
    d_element_t *array;
    unsigned int size;//size of an array of d_element_t
    unsigned int q;//current number of elements
} __dirlist;
typedef __dirlist* dirlist;

dirlist create_dirlist(void);
int insert_into_dirlist(dirlist, const d_element_t);
void close_dirlist(dirlist); // delete list and free the memory

#endif



