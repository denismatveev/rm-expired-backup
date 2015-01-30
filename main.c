#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"filelist.h"
#include"scandir.h"
#include"writelog.h"
#include<ctype.h>

/****************************************************************************************************

Требования к программе:

TODO: сделать функцию (void*)create_list(void) вместо create_filelist() и create_dirlist() и использовать приведение типов
TODO: wchar_t вместо char
TODO: добавить длинные опции
//TODO сделать static linking
//TODO повесить обработчик сигналов в версию с демоном чтобы перечитывать конфиг
**********************************************************************************************************/
#define FULLBACKUPS 2 // number of full backup
#define INCRBACKUPS 14 // number of incremental backups

int main(int argc, char ** argv)
{

    char *help_message;
    char oc;
    unsigned int i;
    char *path=NULL; //pointer to argv that contains path to backup dir
    filelist fl;
    dirlist dl;
    char *program_name=argv[0];
    int wlog=0;
    int skip_hidden=0;
    unsigned int max_depth=0;
    unsigned int j=0;
    char a;

    help_message="Usage: %s\n\t\t\t-p <path to directory where backups store>\n"
                 "          \t\t[-c check backups]\n"
                 "          \t\t[-r remove expired backups]\n"
                 "          \t\t[-f force. It works only with -r option]\n"
                 "         \t\t[-s skip hidden dirs and fils]\n"
                 "          \t\t[-m <number> maximum depth of scanning; default value is 0\n"
                 "         \t\t by default program just check backups and print expired on a terminal\n";

    if((fl=create_filelist()) == NULL)
      exit(EXIT_FAILURE);
    if((dl=create_dirlist()) == NULL)
       exit(EXIT_FAILURE);

   if(argc < 2)
      {
        fprintf(stderr, help_message, program_name);
        exit(EXIT_FAILURE);
      }

    while((oc=getopt(argc, argv, ":p:hlsm:")) != -1)
      {
        switch (oc)
          {
          case  'h':
            fprintf(stderr, help_message, program_name);
            exit(EXIT_FAILURE);
          case 'p':
            path=optarg;
            break;
          case 'l':
           wlog=1;
           break;
          case 's':
            skip_hidden=1;
            break;
            /*
              case 'r':

                    chdir("")
                    find_expires_backups(dir)
                    removebackups();

              case 'c':
                    find_expires_backups(dir);
              case 'f':
  */
          case 'm':
            while((a=*(optarg + j)))
              {
                if(!isdigit(a))
                  {
                    fprintf(stderr,"Option -%c requires a number\n", oc);
                    exit(EXIT_FAILURE);
                  }
                j++;

              }
            max_depth=(unsigned int)atoi(optarg);
            break;
          case '?':
            fprintf(stderr,help_message,program_name);
            exit(EXIT_FAILURE);
          case ':':
            fprintf(stderr, "Option -%c requires an argument\n",optopt);
            exit(EXIT_FAILURE);
          default:
            fprintf(stderr,help_message,program_name);
            exit(EXIT_FAILURE);
          }
      }
    if (optind != argc)
    {
        fprintf(stderr,help_message,program_name);
        exit(EXIT_FAILURE);
    }
/* temporary printing */

    recursivepass(dl, fl, path, wlog, skip_hidden, max_depth);
      //exit(EXIT_FAILURE);
    printf("dirs:\n");
    for(i=0; i < dl->q; i++)
        printf("%s%i %s\n","dir name #",i,dl->array[i]->fullpath);
    printf("files:\n");
    for(i=0; i < fl->q; i++)
        printf("%s%i %s\n","file name #",i, fl->array[i]->fullpath);
/*--------------------------*/

    close_filelist(fl);
    close_dirlist(dl);

    return 0;
}
