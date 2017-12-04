#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "restart.h"
#include "fileio.h"

#if 1
#define VERBOSE(p) (p)
#else
#define VERBOSE(p) (0)
#endif
//HelloWorld
int file_read(char *path, int offset, void *buffer, size_t bufbytes)
{
  int rFile;
  int fd = 0;
  int oSet;

  if(buffer == NULL|| bufbytes < 1 || path == NULL || offset < 0){
    return IOERR_INVALID_ARGS
  }
    fd = open(path, O_RDONLY, NULL);
    if(fd == -1){
      return IOERR_INVALID_PATH;
    }
    oSet = lseek(fd, offset, SEEK_CURR);
    if(oSet == -1){
      return IOERR_POSIX;
    }
    buffer = buffer + oSet;
    rFile = read(fd, buffer, bufbytes);
    if(rFile == -1){
      return IOERR_POSIX;
    }
    close(fd);
    return rFile;
}

int file_info(char *path, void *buffer, size_t bufbytes)
{
    if (!path || !buffer || bufbytes < 1)
	return IOERR_INVALID_ARGS;
    return IOERR_NOT_YET_IMPLEMENTED;
}

int file_write(char *path, int offset, void *buffer, size_t bufbytes)
{
    return IOERR_NOT_YET_IMPLEMENTED;
}

int file_create(char *path, char *pattern, int repeatcount)
{
    return IOERR_NOT_YET_IMPLEMENTED;
}

int file_remove(char *path)
{
    return IOERR_NOT_YET_IMPLEMENTED;
}

int dir_create(char *path)
{
    return IOERR_NOT_YET_IMPLEMENTED;
}

int dir_list(char *path, void *buffer, size_t bufbytes)
{
    return IOERR_NOT_YET_IMPLEMENTED;
}


int file_checksum(char *path)
{
    return IOERR_NOT_YET_IMPLEMENTED;
}

int dir_checksum(char *path)
{
    return IOERR_NOT_YET_IMPLEMENTED;
}
