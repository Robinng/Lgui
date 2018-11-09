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
#include "../include/mouse_ps2.h"
#include "../include/mouse.h"
#include "../include/framebuffer.h"
#include "../include/blockheap.h"
#include "../include/rect.h"
#include "../include/invalidregion.h"
#include "../include/clipregion.h"
#include "../include/message.h"
#include "../include/hdc.h"
#include "../include/caret.h"
#include "../include/winnc.h"
#include "../include/winbase.h"
#include "../include/window.h"
#include "../include/shmem.h"
#include "../include/mouse_ial.h"

#define TRANSCOLOR	RGB(255,0,0)

extern PWindowsTree	_lGUI_pWindowsTree;

static pthread_t thread_mouse;
static MOUSEINFO MouseInfo={false,0,0,true,0,0,NULL,NULL};

void inline 
LockMouse()
{
	LockShMem();
}

void inline 
UnLockMouse()
{
	UnLockShMem();
}

BOOL 
WithinCursorBox(
	int x,
	int y
)
{
	if((x>=MouseInfo.x && x<(MouseInfo.x + MouseInfo.nWidth))&&
	   (y>=MouseInfo.y && y<(MouseInfo.y + MouseInfo.nHeight)))
	   	return true;
	else
		return false;
}

BOOL 
IntersectCursorBox(
	PRECT lpRect
)
{
	RECT rc;
	SetRect(&rc, MouseInfo.x, MouseInfo.y, 
		MouseInfo.x+MouseInfo.nWidth, MouseInfo.y+MouseInfo.nHeight);
	if(IsIntersect (lpRect,&rc))
		return true;
	else
		return false;
}

void 
ShowMouse()
{
	//save the dot color value for the current position of mouse
	GetBoxFromScreenRaw(MouseInfo.x,MouseInfo.y,
		MouseInfo.nWidth,MouseInfo.nHeight,MouseInfo.pSaveBox);
	PutBox2ScreenWithTrColor(MouseInfo.x,MouseInfo.y,
		MouseInfo.nWidth,MouseInfo.nHeight,MouseInfo.pCursorBox,TRANSCOLOR);
	MouseInfo.fHide=false;
}

void
HideMouse()
{
	int i,j;
	//restore the points of current position of the mouse
	for(i=0;(i<MouseInfo.nHeight)&&(MouseInfo.y+i<SCREEN_HEIGHT);i++){
		for(j=0;(j<MouseInfo.nWidth)&&(MouseInfo.x+j<SCREEN_WIDTH);j++){
			lGUI_SetPixel_Direct(MouseInfo.x+j,MouseInfo.y+i,
				*(MouseInfo.pSaveBox+i*MouseInfo.nWidth+j));
		}
	}
	MouseInfo.fHide=true;
}

BOOL inline 
MouseHided()
{
	return MouseInfo.fHide;
}

void 
InitMouseClient()
{
#ifdef _PC_VERSION
	MouseInfo.pCursorBox = (PCOLORREF)(GetShmAddr() + SHMEM_CURSORBOX_OFFSET);
	MouseInfo.pSaveBox = (PCOLORREF)(GetShmAddr() + SHMEM_SAVEBOX_OFFSET);
	GetMouseDimension();
#else
	return;
#endif
}

void 
InitMouseServer()
{
	int i,j;
	FILE* fp;
	UINT16 iType=0;
	UINT16 iBitCount=0;

	UINT08 r,g,b;
	InstallMouseDevice();

#ifdef _PC_VERSION

	MouseInfo.pCursorBox = (PCOLORREF)(GetShmAddr() + SHMEM_CURSORBOX_OFFSET);
	MouseInfo.pSaveBox = (PCOLORREF)(GetShmAddr() + SHMEM_SAVEBOX_OFFSET);

	fp=fopen(RESOURCEFILE,"rb");
	fseek(fp,0,0);
	fread(&iType,sizeof(iType),1,fp);
	fseek(fp,0x12,0);
	fread(&MouseInfo.nWidth,sizeof(MouseInfo.nWidth),1,fp);
	fread(&MouseInfo.nHeight,sizeof(MouseInfo.nHeight),1,fp);
	fseek(fp,0x1c,0);
	fread(&iBitCount,1,1,fp);
	fseek(fp,0x36,0);

	for(i=0;i<MouseInfo.nHeight;i++){
		fseek(fp,0x36+(MouseInfo.nHeight-i-1)*MouseInfo.nWidth*3,0);
		for(j=0;j<MouseInfo.nWidth;j++){
			fread(&b,1,1,fp);
			fread(&g,1,1,fp);
			fread(&r,1,1,fp);
			*(MouseInfo.pCursorBox+i*MouseInfo.nWidth+j)=RGB(r,g,b);
		}
	}

	SetMouseDimension();
	SetMousePos();
#endif
	OpenMouse();
#ifdef _PC_VERSION
	ShowMouse();//show cursor here
#endif
	//create mouse thread
	pthread_create(&thread_mouse,NULL,
				(void*)MouseMainLoop,NULL);
	//pthread_detach(threads[MOUSE_THREADS_INDEX]);
}

void 
TerminateMouseServer()
{
	pthread_cancel(thread_mouse);
	pthread_join(thread_mouse,NULL);
}

//thread cleanup function
void 
cleanup_memory(
	void* para
)
{

	if(MouseInfo.pCursorBox)
		free(MouseInfo.pCursorBox);
	if(MouseInfo.pSaveBox)
		free(MouseInfo.pSaveBox);
	CloseMouse();
}

void* 
MouseMainLoop(
	void* para
)
{
	int x,y,event;
	int old_cancel_type;
	int iRetVal;
#ifdef _PC_VERSION
	//register thread cleanup function
	pthread_cleanup_push(cleanup_memory,NULL);
#endif

	while(1){
		pthread_testcancel();
		iRetVal = ReadMouse(&x,&y,&event);
		if(!iRetVal)
			continue;


#ifdef _PC_VERSION

		LockMouse();
		HideMouse();
		MouseInfo.x=x;
		MouseInfo.y=y;

		SetMousePos();

		ShowMouse();
		UnLockMouse();

#else
		MouseInfo.x = x;
		MouseInfo.y = y;

#endif
		//printf("%d,%d,%d\n",x,y,event);
		//send message
		switch(event){
		case MOUSE_EVENT_LBUTTON_DOWN:
  			PostMessage(_lGUI_pWindowsTree,LMSG_RAW_MOUSEDOWN,
				MouseInfo.x,MouseInfo.y);
			//printf("down\n");
			break;
		case MOUSE_EVENT_LBUTTON_UP:
			PostMessage(_lGUI_pWindowsTree,LMSG_RAW_MOUSEUP,
				MouseInfo.x,MouseInfo.y);
			//printf("up\n");
			break;
		case MOUSE_EVENT_MOVE:
			//printf("MOVE\n");
			PostMessage(_lGUI_pWindowsTree,LMSG_RAW_MOUSEMOVE,
				MouseInfo.x,MouseInfo.y);
			break;
		}
	}

#ifdef _PC_VERSION
	//cleanup function
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,&old_cancel_type);
	pthread_cleanup_pop(1);
	pthread_setcanceltype(old_cancel_type,NULL);
#endif

}




void inline 
RequestPaint(
	PRECT lpRect
)
{
#ifdef _PC_VERSION

	LockMouse();

	GetMousePos();

	if(IntersectCursorBox(lpRect))
		HideMouse();

	MouseInfo.fPaintCompleted=false;
	//signal(SIGALRM,PaintTimerOutRoutine);
	//alarm(5);
#else
	return;
#endif
	
}

void inline 
CompletePaint()
{
#ifdef _PC_VERSION
	if(MouseInfo.fHide)
		ShowMouse();
	MouseInfo.fPaintCompleted=true;
	UnLockMouse();
#else
	return;
#endif
	
}

void 
PaintTimerOutRoutine(
	int sig_num
)
{
	alarm(0);
	if(MouseInfo.fPaintCompleted)
		return;
	if(MouseHided())
		ShowMouse();
	UnLockMouse();
}


void inline 
SetMousePos()
{
	char* pShMemAddr;
	pShMemAddr = GetShmAddr();
	*((int*)(pShMemAddr + SHMEM_MOUSE_OFFSET_X))=MouseInfo.x;
	*((int*)(pShMemAddr + SHMEM_MOUSE_OFFSET_Y))=MouseInfo.y;
}

void inline 
GetMousePos()
{
	char* pShMemAddr;
	pShMemAddr = GetShmAddr();
	MouseInfo.x = *((int*)(pShMemAddr + SHMEM_MOUSE_OFFSET_X));
	MouseInfo.y = *((int*)(pShMemAddr + SHMEM_MOUSE_OFFSET_Y));
}

void inline 
GetMouseDimension()
{
	char* pShMemAddr;
	pShMemAddr = GetShmAddr();
	MouseInfo.nWidth = *((int*)(pShMemAddr + SHMEM_MOUSE_WIDTH_OFFSET));
	MouseInfo.nHeight = *((int*)(pShMemAddr + SHMEM_MOUSE_HEIGHT_OFFSET));
}

void inline 
SetMouseDimension()
{
	char* pShMemAddr;
	pShMemAddr = GetShmAddr();
	*((int*)(pShMemAddr + SHMEM_MOUSE_WIDTH_OFFSET)) = MouseInfo.nWidth;
	*((int*)(pShMemAddr + SHMEM_MOUSE_HEIGHT_OFFSET)) = MouseInfo.nHeight;
}




