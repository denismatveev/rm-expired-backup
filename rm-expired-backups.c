#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
/****************************************************************************************************

1. считать кол-во файлов в каталоге (n)
2. Создать структуру для хранения данных об элементе каталога
3. Создать динамический массив для хранения стрктур из п.2, но только тех, которые не удовлетворяют условиям, что дата их создания внутри последних 14 дней
4. удалить эти файлы или каталоги(которые в массиве)

функции:
init_filelist()
inserintofilelist()
removefromfilelist()

**********************************************************************************************************/
#define FULLBACKUPS 2 // number of full backup
#define INCRBACKUPS 14 // number of incremental backups

//struct dirent *readdir(DIR *dirp);


filelist list;


int scan_backupsdir_for_expired_files(char *dirname)
{   

    
    if(init_filelist() == 1)
    {
        perror(filelist);
        exit(1);
    }
while()
{
    readdir()
    stat();
    if

    strcpy(  //copy to our struct    
}
}


filelist createfilelist()
{
    filelist fl;

    if(fl=(filelist)malloc(sizeof(struct filelist) == NULL)
        return NULL;
    if((fl->array=(DirElement)calloc(ARRAY_SIZE,sizeof(DirElement))) == NULL)
        return NULL;
    fl->n=ARRAY_SIZE;

    return fl;
}

void closefilelist(filelist fl)
{

    free(fl->array);
    free (fl);

    return;
}




int main(int agrc, char ** argv)
{

    char *help_message;
    char oc;
    char path;
    DIR *dir;
    path=calloc(10, sizeof(char));//dynamic allocation
    help_message="Usage: %s [-c check backups]\n"
                 "          [-r remove expired backups]\n"
                 "          [-f force. It works only with -r option\n]"
                 "          [-p path to directory where backups store\n]";
    
    while((oc=getopt(argc, argv, ":crf:h")) != -1)
    {
        switch (oc)
        {
          case  '?':
              fprintf(stderr, help_message, argv[0]);
              exit(1);
          case 'p':
                path=opt

          case 'r':
                
                chdir("")
                find_expires_backups(dir)
                removebackups();          
          case 'c':
                find_expires_backups(dir);
          case 'f':
          case ':':
            fprintf(stderr, "Option -%c requires an argument\n",optopt); 
            exit(1);
          default:
              fprintf(stderr,%s,help_message);
              exit(2);
        }
    }

    free(path);


}
