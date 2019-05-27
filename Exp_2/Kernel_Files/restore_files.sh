#!/bin/bash
cp unistd_64.h $1/arch/sh/include/uapi/asm/unistd_64.h
cp syscall_64.tbl $1/arch/x86/entry/syscalls/syscall_64.tbl
cp syscalls.h $1/include/linux/syscalls.h
cp sys.c $1/kernel/sys.c