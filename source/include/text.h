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

#ifndef _TEXT_H
#define _TEXT_H

#ifdef __cplusplus                     
extern "C" {
#endif




BOOL GUIAPI 
DrawText(
	HDC hDC,
	char* lpString,
	int nCount,
	LPRECT lpRect,
	UINT uFormat
);


BOOL 
winDrawText(
	HDC hDC,
	char* lpString,
	int nCount,
	LPRECT lpRect,
	UINT uFormat
);


BOOL GUIAPI 
DrawTextAngle(
	HDC hDC,
	char* lpString,
	int nCount,POINT* 
	lpPoint,double fDirection
);

BOOL 
winDrawTextAngle(
	HDC hDC,
	char* lpString,
	int nCount,
	POINT* lpPoint,
	double fDirection
);



#ifdef __cplusplus
}
#endif 


#endif 
