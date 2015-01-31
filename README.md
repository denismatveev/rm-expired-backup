rm-expired-backup
=================

utility for searching old(expired) backups and deleting these expired backups but leaves just the freshest

options:<br>
--force(-f) - don't ask anything<br>
--max-increments (-i)<br>
--max-full-backups (-fb)<br>
--path-to-backups (-p) - specify path to a directory with backups. Suppose full backups and incremental backups are located at the same directory <br>
--help (-h) - prints help message<br>
--log (-l) write logs.logs write via syslogd<br>
--skip-hidden (-s) - skip hidden directories(begining with dot(.))<br>
--max-depth(-m) - maximum depth of searching<br>


