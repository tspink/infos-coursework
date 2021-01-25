#!/bin/sh

TOP=`pwd`
INFOS_DIR=$TOP/infos
INFOS_USER_DIR=$TOP/infos-user
ROOTFS=$INFOS_USER_DIR/bin/rootfs.tar
KERNEL=$INFOS_DIR/out/infos-kernel
KERNEL_CMDLINE="boot-device=ata0 init=/usr/init pgalloc.debug=0 pgalloc.algorithm=simple objalloc.debug=0 sched.debug=0 sched.algorithm=cfs syslog=serial $*"
QEMU_DIR=/afs/inf.ed.ac.uk/group/teaching/cs3/os/qemu
QEMU_BIN=$QEMU_DIR/qemu-system-x86_64

LD_LIBRARY_PATH=$QEMU_DIR $QEMU_BIN -L $QEMU_DIR -kernel $KERNEL -m 6G -debugcon stdio -hda $ROOTFS -append "$KERNEL_CMDLINE"
