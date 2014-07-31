#!/bin/bash
set -e
#set -x

######################
##### Settings #######
DBUSER=backup-user
DBPASS=changeme
BACKUPDIR=/mnt/debian/backups
THREADS=4
NUMBEROFFULLBACKUPS=1
NUMBERINCRBACKUPS=3
LOCKFILE=/var/run/cronbackup.lock
LOG=/var/log/cronbackup.log
###########################
#### lockfile ####
if [ -e "$LOCKFILE" ]
	then
	echo -e "Cannot obtain lock file\n";
	exit 1;
fi
touch "$LOCKFILE";
trap 'rm -f "$LOCKFILE"; exit $?' INT TERM EXIT # signals handler(analog sigaction() family? )
#########################
CURRENTNUMBEROFFULLBACKUPS=$(ls -1t "$BACKUPDIR" 2>/dev/null  | wc -l)
OLDESTBACKUP=$(ls -1t "$BACKUPDIR" 2>/dev/null|  tail -n1)
CURRENTFULLBACKUP=$(ls -1t "$BACKUPDIR" 2>/dev/null|  head -n1)
NUMBEROFINCREMENTALBACKUPSINOLDESTFULL=$(ls -1 "$BACKUPDIR"/"$OLDESTBACKUP"/INC 2>/dev/null| wc -l)
NUMBEROFCURRENTINCRBACKUPS=$(ls -1 "$BACKUPDIR"/"$CURRENTFULLBACKUP"/INC 2>/dev/null | wc -l)
########################
function makefull
{
	/root/bin/xb-backup-incremental.sh -r "$BACKUPDIR" -u  "$DBUSER" -p "$DBPASS" --backup-threads="$THREADS" >> "$LOG"

	return 0
}

function makeincremental
{

	/root/bin/xb-backup-incremental.sh -r "$BACKUPDIR" -u  "$DBUSER" -p "$DBPASS" --increment --backup-threads="$THREADS" >> "$LOG"

	return 0
}

function rmexpiredbackups
{
	
	if [[ "$CURRENTNUMBEROFFULLBACKUPS" -ge "$NUMBEROFFULLBACKUPS" ]] && [[ "$NUMBEROFCURRENTINCRBACKUPS" -ge "$NUMBERINCRBACKUPS" ]] && [[ "$NUMBEROFINCREMENTALBACKUPSINOLDESTFULL" -ge "$NUMBERINCRBACKUPS" ]]
        	then
		echo -e "deleting old backups: "$BACKUPDIR"/"$OLDESTBACKUP"\n" >> "$LOG"
        	rm -rf "$BACKUPDIR"/"$OLDESTBACKUP"
		echo -e "old backups deleted at `date +%F-%T`\n" >> "$LOG" 
	elif [[ "$CURRENTNUMBEROFFULLBACKUPS" -gt "$NUMBEROFFULLBACKUPS" ]] && ([[ "$NUMBEROFINCREMENTALBACKUPSINOLDESTFULL" -lt "$NUMBERINCRBACKUPS" ]] || [[ "$NUMBEROFCURRENTINCRBACKUPS" -lt "$NUMBERINCRBACKUPS" ]])
        	then
        	echo -e "not enough incremental backups to delete\n" >> "$LOG"
	elif [[ "$CURRENTNUMBEROFFULLBACKUPS" -lt "$NUMBEROFFULLBACKUPS" ]]
        	then
        	echo -e "not enough full backups to delete\n" >> "$LOG"
    	fi
    
	return 0;

}
#######################



	if ([[ "$CURRENTNUMBEROFFULLBACKUPS" -le "$NUMBEROFFULLBACKUPS" ]] && [[ "$NUMBEROFCURRENTINCRBACKUPS" -ge "$NUMBERINCRBACKUPS" ]]) || [[ "$CURRENTNUMBEROFFULLBACKUPS" -eq 0 ]] && [[ "$NUMBEROFFULLBACKUPS" -gt 0 ]]
		then makefull
	elif [[ "$NUMBEROFCURRENTINCRBACKUPS" -lt "$NUMBERINCRBACKUPS" ]] && [[ "$CURRENTNUMBEROFFULLBACKUPS" -gt 0 ]]
		then makeincremental
	else echo -e "some error ocurred!\n" >> "$LOG";exit 2
	fi	 

 
	rmexpiredbackups;

