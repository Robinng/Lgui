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
#include "../include/xml.h"



#define DIRTAG			"<dir>"
#define APPTAG			"<app>"



static BOOL 
IsHead(
	 char* lpszTag
);

static BOOL 
IsPair(
	  char* lpszHead,
	  char* lpszTail
);


BOOL 
GetATag(
	FILE* fp,
	char* lpszRetTag
)
{
	char aByte;
	char lpszTag[MAX_TAG_SIZE];
	int iCount=0;
	BOOL bStart=false;
	memset(lpszTag,0,MAX_TAG_SIZE);
	while(!feof(fp)){
		fread(&aByte,1,1,fp);
		if(aByte=='<'){
			bStart=true;
			lpszTag[iCount]='<';
			iCount++;
		}
		else{
			if(bStart){
				lpszTag[iCount]=aByte;
				iCount++;
				if(aByte=='>'){
					strcpy(lpszRetTag,lpszTag);
					return true;
				}
			}
		}
	}
	return false;
}


static BOOL 
IsHead(
	 char* lpszTag
)
{
	if(*(lpszTag+1)=='/')
		return false;
	else
		return true;
}


BOOL 
IsDirHead(
	char* lpszTag
)
{
	if(!IsHead(lpszTag))
		return false;
	if(!strcmp(lpszTag,"<dir>"))
		return true;
	else
		return false;
}


BOOL 
IsDirTail(
	char* lpszTag
)
{
	if(IsHead(lpszTag))
		return false;
	if(!strcmp(lpszTag,"</dir>"))
		return true;
	else
		return false;
}


BOOL 
IsAppHead(
	char* lpszTag
)
{
	if(!IsHead(lpszTag))
		return false;
	if(!strcmp(lpszTag,"<app>"))
		return true;
	else
		return false;
}


BOOL 
IsAppTail(
	char* lpszTag
)
{
	if(IsHead(lpszTag))
		return false;
	if(!strcmp(lpszTag,"</app>"))
		return true;
	else
		return false;
}



BOOL 
GetHeadTag(
	FILE* fp, 
	char* lpszRetTag
)
{
	BOOL bRet;
	bRet=GetATag(fp,lpszRetTag);
	while(bRet){
		if(lpszRetTag[1]!='/')
			return true;
		bRet=GetATag(fp,lpszRetTag);
	}
	return false;
}


BOOL 
GetTailTag(
	FILE* fp, 
	char* lpszRetTag
)
{
	BOOL bRet;
	bRet=GetATag(fp,lpszRetTag);
	while(bRet){
		if(lpszRetTag[1]=='/')
			return true;
		bRet=GetATag(fp,lpszRetTag);
	}
	return false;
}


static BOOL 
IsPair(
	char* lpszHead, 
	char* lpszTail
)
{

	char strTmp[MAX_TAG_SIZE];
	strTmp[0]=lpszTail[0];
	strcpy(strTmp+1,lpszTail+2);
	if(!strcmp(lpszHead,strTmp))
		return true;
	else
		return false;
}


BOOL 
GetValue(
	FILE* fp, 
	char* lpszItem, 
	char* lpszValue
)
{
	char lpszHeadTag[MAX_TAG_SIZE];
	char lpszTailTag[MAX_TAG_SIZE];
	char lpszRetValue[MAX_VALUE_SIZE];
	int iCount=0;
	char aByte;
	
	memset(lpszHeadTag,0,MAX_TAG_SIZE);
	memset(lpszTailTag,0,MAX_TAG_SIZE);
	memset(lpszRetValue,0,MAX_VALUE_SIZE);
	if(!GetHeadTag(fp,lpszHeadTag))
		return false;
	while(!feof(fp)){
		fread(&aByte,1,1,fp);
		if(aByte!='<'){
			*(lpszRetValue + iCount)=aByte;
			iCount++;
		}
		else{
			fseek(fp,-1,SEEK_CUR);
			GetTailTag(fp,lpszTailTag);
			if(IsPair(lpszHeadTag,lpszTailTag)){
				strncpy(lpszItem,(lpszHeadTag+1),strlen(lpszHeadTag)-2);
				strcpy(lpszValue,lpszRetValue);
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

