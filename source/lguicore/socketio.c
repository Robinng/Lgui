/*
	Copyright (C) 2004-2005 Li Yudong
	Some ideas come from MiniGUI
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
#include "../include/socketio.h"



int
serv_listen(
	const char *name
)
{
	int fd;
	int len;
	struct sockaddr_un unix_addr;
    
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("opening stream socket");
        return -1;
    }
    fcntl( fd, F_SETFD, FD_CLOEXEC );
    unlink (name);	
	memset (&unix_addr, 0, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;
    strcpy(unix_addr.sun_path, name);
   	len = sizeof (unix_addr.sun_family) + strlen (unix_addr.sun_path);
    if (bind (fd, (struct sockaddr *) &unix_addr, len) < 0){
		close(fd);
        perror("binding stream socket");
        return -1;
    }
	chmod (name, 0666);
    if(listen(fd, 5)<0){
		close(fd);
		return -1;
	}
	return fd;	
}


int 
serv_accept(
	int listenfd
)
{
    int                clifd;
    struct sockaddr_un unix_addr;
    clifd = accept(listenfd, 0, 0);
	if(clifd <0)
		return -1;
    return (clifd);
}



int 
cli_conn(
	const char *name
)
{
    int                fd, len;
    struct sockaddr_un unix_addr;

	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        return(-1);

    memset(&unix_addr, 0, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;
    sprintf(unix_addr.sun_path, "%s%05d", CLI_PATH, getpid());
    len = sizeof(unix_addr.sun_family) + strlen(unix_addr.sun_path); 
    unlink (unix_addr.sun_path); 
    if (bind(fd, (struct sockaddr *) &unix_addr, len) < 0){
		close(fd);
		return -1;
	}
	chmod(unix_addr.sun_path, 0606);
    memset(&unix_addr, 0, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;
    strcpy(unix_addr.sun_path, name);
    len = sizeof(unix_addr.sun_family) + strlen(unix_addr.sun_path);
    if (connect (fd, (struct sockaddr *) &unix_addr, len) < 0){
 		close(fd);
		return -1;
	}
    return (fd);

}


int 
sock_write(
	int fd, 
	const void* buff, 
	int count
)
{
    const void* pts = buff;
    int status = 0, n;

    if (count < 0) return SOCKERR_OK;

    while (status != count) {
        n = write (fd, pts + status, count - status);
        if (n < 0) {
            if (errno == EPIPE)
                return SOCKERR_CLOSED;
            else if (errno == EINTR)
                continue;
            else
                return SOCKERR_IO;
        }
        status += n;
    }
    return status;
}

int 
sock_read(
	int fd, 
	void* buff,
	int count
)
{
    void* pts = buff;
    int status = 0, n;

    if (count <= 0) return SOCKERR_OK;

    while (status != count) {
        n = read (fd, pts + status, count - status);

        if (n < 0) {
            if (errno == EINTR)
                continue;
            else
                return SOCKERR_IO;
        }

        if (n == 0)
            return SOCKERR_CLOSED;

        status += n;
    }

    return status;
}


