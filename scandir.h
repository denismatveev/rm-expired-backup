#ifndef SCANDIR_H
#define SCANDIR_H
#define WLOG 1 //0000001
#define SK_HIDN 3 //0000011

int myscandir(dirlist, filelist, const char*, const int, const int);
int recursivepass(dirlist, filelist, const char*, const int, const int, const unsigned int);
#endif // SCANDIR_H

