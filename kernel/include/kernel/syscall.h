#ifndef SYSCALL_H
#define SYSCALL_H

#include <kernel/isr.h>
#include <stdint.h>

#define SYSCALL_NUM 256

typedef void(*sys_handler_t)(registers_t*);

void init_syscall();
void syscall_register_handler(uint32_t num, sys_handler_t handler);

#endif
