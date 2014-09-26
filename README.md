rm-expired-backup
=================

utility for searching old(expired) backups and delete it and leave just the freshest

rm-expired-backup

<<<<<<< HEAD
--force(-f) - don't ask anything
=======
--force - don't ask anything

>>>>>>> d5bf1e0c48c9270df42450e7016533203b5ea17a
--max-increments (-i)

--max-full-backups (-fb)

--path-to-backups (-p) - specify path to a directory with backups. Suppose full backups and incremental backups are located at the same directory 

--help (-h) - prints help message

--log (-l) write logs.logs write via syslogd

-- some option

<<<<<<< HEAD
dir-dir-files
files 
    ibdata*
    mysql*tar.gz
    xtrabackup_checkpoints
    xtrabackup_logfile
    если что-то другое - значит это не бекап

Сканируем директорию, получаем массив объектов, проверяем содержимое файлов и принимаем решение об удалении.
=======

>>>>>>> d5bf1e0c48c9270df42450e7016533203b5ea17a
