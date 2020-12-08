#ifndef _KERNEL_

#include <sys/stat.h>
#include <unistd.h>

#include <kernel/uapi/uapi_syscall.h>
#include <kernel/uapi/uapi_fs.h>

extern int32_t syscall1(uint32_t eax, uint32_t ebx);
extern int32_t syscall2(uint32_t eax, uint32_t ebx, uint32_t ecx);

int mkdir(const char* pathname, mode_t mode) {
    uint32_t inode = syscall2(SYS_MKDIR, (uintptr_t) pathname, mode);

    if (inode == FS_INVALID_INODE) {
        return -1;
    }

    return 0;
}

int chdir(const char* path) {
    return syscall1(SYS_CHDIR, (uintptr_t) path);
}

char* getcwd(char* buf, size_t size) {
    return (char*) syscall2(SYS_GETCWD, (uintptr_t) buf, (uintptr_t) size);
}

int unlink(const char* path) {
    return syscall1(SYS_UNLINK, (uintptr_t) path);
}

int stat(const char* path, struct stat* buf) {
    stat_t statbuf;
    int ret = syscall2(SYS_STAT, (uintptr_t) path, (uintptr_t) &statbuf);

    if (ret) {
        return ret;
    }

    buf->st_dev = statbuf.st_dev;
    buf->st_ino = statbuf.st_ino;
    buf->st_mode = statbuf.st_mode;
    buf->st_nlink = statbuf.st_nlink;
    buf->st_size = statbuf.st_size;

    return 0;
}

#endif