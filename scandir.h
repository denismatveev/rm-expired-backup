#ifndef SCANDIR_H
#define SCANDIR_H
#define L_NAME 1024
int myscandir(dirlist, filelist, const char*, const int, const int);
int recursivepass(dirlist, filelist, const char*, const int, const int, const unsigned int);
#endif // SCANDIR_H

