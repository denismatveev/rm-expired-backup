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
#include"writelog.h"

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


int main(int argc, char ** argv)
{

    char *help_message;
    char oc;
    char *path; //pointer to argv that contains path to backup dir
    unsigned int i;
    filelist fl;

    help_message="Usage: %s\t[-c check backups]\n"
                 "          \t\t[-r remove expired backups]\n"
                 "          \t\t[-f force. It works only with -r option]\n"
                 "          \t\t[-p path to directory where backups store]\n";

    fl=createfilelist();

    while((oc=getopt(argc, argv, ":p:h")) != -1)
    {
        switch (oc)
        {
        case  'h':
            fprintf(stderr, help_message, *argv);
            exit(1);
        case 'p':
            path=optarg;
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
        case ':':
            fprintf(stderr, "Option -%c requires an argument\n",optopt);
            exit(1);
        default:
            fprintf(stderr,help_message,*argv);
            exit(2);
        }
    }
    if (optind != argc)
    {
        fprintf(stderr, "%s",help_message);
        exit(EXIT_FAILURE);
    }

    if((myscandir(fl,path)))
    {
        WriteLog("got error");
        exit(1);
    }

    for(i=0; i < fl->q; i++)
        printf("%s%i %s\n","entry name #",i,fl->array[i]->fullpath);


    closefilelist(fl);

    return 0;
}
