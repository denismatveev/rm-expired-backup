#ifndef SCANDIR_H
#define SCANDIR_H
#define WLOG 1 //0000001
#define SKHDN 2 //0000010
int myscandir(dirlist, filelist, const char*, const int);
int recursivepass(dirlist, filelist, const char*, const int, const unsigned int);
#endif // SCANDIR_H

