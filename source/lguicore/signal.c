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
#include "../include/rect.h"
#include "../include/message.h"
#include "../include/blockheap.h"
#include "../include/invalidregion.h"
#include "../include/clipregion.h"
#include "../include/hdc.h"
#include "../include/caret.h"
#include "../include/winnc.h"
#include "../include/winbase.h"
#include "../include/window.h"
#include "../include/scrollbar.h"

extern PWindowsTree  _lGUI_pWindowsTree;
//define a global variable
//client process exit passive or active
BOOL _lGUI_bByServer	= false;

//signal callback function
void 
SigTermRoutine()
{
	_lGUI_bByServer=true;
	DestroyWindow(_lGUI_pWindowsTree);	
}

//register signal callback function
void 
RegSignalCallBack()
{
	signal(SIGTERM,SigTermRoutine);
}

//send signal to a client process 
//this function will called by server process
//to send a terminate signal
void SendSigTerm(pid_t pid)
{
	kill(pid,SIGTERM);
}
