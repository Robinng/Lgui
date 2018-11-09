/*
	Copyright (C) 2004-2005 Li Yudong
*/
/*
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include <sys/types.h>
#include <sys/sem.h>
#include "../include/semaphore.h"

//create semaphore

int 
sem_create(
	key_t sem_id
)
{
	union semun sem_val;
	int sem_set_id;
	int rc;
	sem_set_id=semget(sem_id,1,IPC_CREAT | 0600);
	if(sem_set_id==-1)
		return -1;
	sem_val.val=1;
	rc=semctl(sem_set_id,0,SETVAL,sem_val);
	if(rc==-1)
		return -1;
	else
		return sem_set_id;
}

//Lock
void
sem_lock(
	int sem_set_id
)
{
	struct sembuf sem_op;
	sem_op.sem_num	=0;
	sem_op.sem_op	=-1;
	sem_op.sem_flg	=0;
	semop(sem_set_id,&sem_op,1);
}

//unlock
void 
sem_unlock(
	int sem_set_id
)
{
	struct sembuf sem_op;
	sem_op.sem_num	=0;
	sem_op.sem_op	=1;
	sem_op.sem_flg	=0;
	semop(sem_set_id,&sem_op,1);
}

//destroy
void 
sem_remove(
	int sem_set_id
)
{
	semctl(sem_set_id,0,IPC_RMID);
}
