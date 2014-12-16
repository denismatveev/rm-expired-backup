/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2014 denis matveev <denis@ilmen-tau.ru>
 * 
 * removebackups is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * removebackups is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"filelist.h"

/****************************************************************************************************

1. считать кол-во файлов в каталоге (n) done
2. Создать структуру для хранения данных об элементе каталога
3. Создать динамический массив для хранения стрктур из п.2, но только тех, которые не удовлетворяют условиям, что дата их создания внутри последних 14 дней
4. удалить эти файлы или каталоги(которые в массиве)
5. Добавить логгирование действий в syslog()
6. Добавить ограничение на количество элементов(например, 100000)
функции:
createfilelist()
inserintofilelist()
removefromfilelist()

Требования к программе:



**********************************************************************************************************/
#define FULLBACKUPS 2 // number of full backup
#define INCRBACKUPS 14 // number of incremental backups


int main(int agrc, char ** argv)
{

    char *help_message;
    char oc;
    char *path; //pointer to argv that contains path to backup dir
    int i;
    filelist fl;

//    DIR *dir;
    help_message="Usage: %s [-c check backups]\n"
                 "          [-r remove expired backups]\n"
                 "          [-f force. It works only with -r option\n]"
                 "          [-p path to directory where backups store\n]";
    fl=createfilelist();

    if(myscandir(fl,"/home/"))
    {
        WriteLog("got error");
		
        exit(1);
    }

    for(i=0; i < fl->size; i++)
      printf("%s%i %s\n","entry name #",i,fl->array[i]->fullpath);




    closefilelist(fl);

    /*
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

    */

    return 0;
}