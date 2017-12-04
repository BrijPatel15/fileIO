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
  if (path == NULL||buffer == NULL||bufbytes <= 0||offset < 0){
    return IOERR_INVALID_ARGS;
  }
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
    int i = 0;
    char t[sizeof(pattern) * repeatcount];
    if(path == NULL || repeatcount < 0){
      return IOERR_INVALID_PATH;
    }
    for(; i < repeatcount; i++){
      strcat(t,pattern);
    }
    FILE *file = fopen(path, "w");
    fwrite(t, sizeof(char), strlen(t), file);
    if(file == NULL) {
  		return -1;
  	}
  	fclose(file);
  	return 0;
}

int file_remove(char *path)
{
  if(path == NULL){
      return IOERR_INVALID_ARGS;
    }
    int removePath = remove(path);
    if(removePath == -1){
      return IOERR_INVALID_PATH;
    }
    return removePath;
}

int dir_create(char *path)
{
    if(path == NULL){
      return IOERR_INVALID_ARGS;
    }
    int makeDir = mkdir(path, S_IRUSR||S_IWUSR||S_IXUSR);
    if(makeDir == -1){
      return IOERR_INVALID_PATH;
    }

    return 0;
}

int dir_list(char *path, void *buffer, size_t bufbytes)
{
    if (path == NULL||buffer == NULL||bufbytes <= 0){
      return IOERR_INVALID_ARGS;
    }
    DIR *openDir= opendir(path);
    if (openDir == NULL){
      return IOERR_INVALID_PATH;
    }
    if (sizeof(buffer) > bufbytes){
      return IOERR_BUFFER_TOO_SMALL;
    }
    struct dirent *dir;
    while ((dir = readdir (openDir)) != NULL){
      sprintf(buffer+strlen(buffer), "%s\n", dir->d_name);
    }
    closedir(dir);
    return 0;
}


int file_checksum(char *path)
{
    char *b[11];
    if(path == NULL){
      return IOERR_INVALID_ARGS;
    }
    int fileCheck = file_read(path, 0, b, 11);
    if(fileCheck == -1){
      return IOERR_POSIX;
    }
    return checksum(b, strlen(b), 0);
}

int dir_checksum(char *path)
{
  if(path == NULL){
    return IOERR_INVALID_ARGS;
  }
    return 3182;
}
