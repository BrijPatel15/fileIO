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
    return IOERR_INVALID_ARGS;
  }
    fd = open(path, O_RDONLY, NULL);
    if(fd == -1){
      return IOERR_INVALID_PATH;
    }
    oSet = lseek(fd, offset, SEEK_CUR);
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
  struct stat info;
  if (path == NULL || buffer == NULL || bufbytes < 1) {
   return IOERR_INVALID_ARGS;
  }
  if(stat(path, &info) == -1){
    return IOERR_POSIX;
  }
  int size = info.st_size;
  long timeAccessed = info.st_atime;
  long timeModified = info.st_mtime;
  char type;
  switch(info.st_mode & S_IFMT){
    case S_IFREG: type = 'f'; break;
    case S_IFDIR: type = 'd'; break;
  }

  sprintf(buffer, "Size:%d Accessed:%ld Modified:%ld Type %c", size, timeAccessed, timeModified, type);

  return 0;
}

int file_write(char *path, int offset, void *buffer, size_t bufbytes)
{
  int file;
  if (path == NULL||!buffer||bufbytes<1||offset<0)
    return IOERR_INVALID_ARGS;
  int fd = open(path, O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);
  if (fd==-1){
    return IOERR_INVALID_PATH;
  }
  if (lseek(fd,offset,SEEK_CUR)==-1){
    return IOERR_POSIX;
  }
  file = r_write(fd,buffer,bufbytes);
  close(fd);
  return file;
}

int file_create(char *path, char *pattern, int repeatcount)
{
    int fd = 0;
    int file;
    int i = 0;
    char *t;
    if(path == NULL || repeatcount < 0){
      return IOERR_INVALID_PATH;
    }
    fd = open(path, O_RDWR|O_CREAT, S_IRWXU);
    if(fd == -1){
      return IOERR_INVALID_PATH;
    }

    for(; i <= repeatcount; i++){
      fprintf("I'm in the loop", "%s\n" );
      strcat(&t, pattern);
    }

    file = r_write(fd,t,sizeof(t));
    if(file < 0){
      return -1;
    }
    return 0;
}

int file_remove(char *path)
{
  if(path == NULL){
      return IOERR_INVALID_ARGS;
    }
    int rem = remove(path);
    if(rem == -1){
      return IOERR_INVALID_PATH;
    }
    return rem;
}

int dir_create(char *path)
{
      if(path == NULL){
      return IOERR_INVALID_ARGS;
    }
    int make = mkdir(path, S_IRUSR||S_IWUSR||S_IXUSR);
    if(make == -1){
      return IOERR_INVALID_PATH;
    }

    return 0;
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
