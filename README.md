rm-expired-backup
=================

utility for searching old(expired) backups and deleting these expired backups but leaves just the freshest

options:

--force(-f) - don't ask anything
--max-increments (-i)
--max-full-backups (-fb)
--path-to-backups (-p) - specify path to a directory with backups. Suppose full backups and incremental backups are located at the same directory 
--help (-h) - prints help message
--log (-l) write logs.logs write via syslogd
--skip-hidden (-s) - skip hidden directories(begining with dot(.))
--max-depth(-m) - maximum depth of searching


