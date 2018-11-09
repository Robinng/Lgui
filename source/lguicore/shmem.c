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

#include "../include/common.h"
#include "../include/semaphore.h"
#include "../include/shmem.h"

#include "../include/blockheap.h"
#include "../include/rect.h"
#include "../include/invalidregion.h"
#include "../include/clipregion.h"
#include "../include/message.h"
#include "../include/hdc.h"


#define	SEM_ID		250					//Id of semaphore

#define SHMEM_ID	100					//ID of share memory
#define SHMEM_FLAG	IPC_CREAT | 0600	//flag for create share memory


int sem_set_id;		
int shm_id;			
char* _lGUI_pShm;	

//for all process only read the share memory
//It's unnecessary to lock share memory before each reading operation.
char* 
GetShmAddr()
{
	return _lGUI_pShm;
}
//Read share memory
//share memory id
//Dest pointer
//offset from _lGUI_pShm in byte.
//length
int 
shm_read(char* pDest, int iOffset, int iLen)
{
	memcpy(pDest,_lGUI_pShm+iOffset,iLen);
	return 0;
}
//Write share memory
//share memory id
//Dest pointer
//offset from _lGUI_pShm in byte
//length
int
shm_write(
	char* pSource, 
	int iOffset, 
	int iLen
)
{
	memcpy(_lGUI_pShm+iOffset,pSource,iLen);
	return 0;
}


BOOL 
InitShareMemServer()
{
    struct shmid_ds shm_desc;

	sem_set_id=sem_create(SEM_ID);
	if(sem_set_id==-1)
		return false;

	shm_id=shmget(SHMEM_ID,SHMEM_SIZE,SHMEM_FLAG);
	if(shm_id==-1){
		sem_remove(sem_set_id);
		return false;
	}
	_lGUI_pShm=shmat(shm_id,NULL,0);
	if(!_lGUI_pShm){
		sem_remove(sem_set_id);
		shmctl(shm_id,IPC_RMID,&shm_desc);
		return false;
	}
	return true;

}

BOOL 
InitShareMemClient()
{
    struct shmid_ds shm_desc;

	shm_id=shmget(SHMEM_ID,SHMEM_SIZE,SHMEM_FLAG);
	if(shm_id==-1){
		sem_remove(sem_set_id);
		return false;
	}
	_lGUI_pShm=shmat(shm_id,NULL,0);
	if(!_lGUI_pShm){
		sem_remove(sem_set_id);
		shmctl(shm_id,IPC_RMID,&shm_desc);
		return false;
	}
	return true;

}

void 
UnInitShareMem()
{
	struct shmid_ds shm_desc;
	if(IsServerProcess()){
		sem_remove(sem_set_id);

		shmdt(_lGUI_pShm);

		shmctl(shm_id,IPC_RMID,&shm_desc);
	}
	else{
		shmdt(_lGUI_pShm);
	}

}

void 
LockShMem()
{
	sem_lock(sem_set_id);
}

void 
UnLockShMem()
{
	sem_unlock(sem_set_id);
}

