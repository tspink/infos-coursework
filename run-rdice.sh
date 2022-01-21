#!/bin/sh

TOP=`pwd`
INFOS_DIR=$TOP/infos
INFOS_USER_DIR=$TOP/infos-user
ROOTFS=$INFOS_USER_DIR/bin/rootfs.tar
KERNEL=$INFOS_DIR/out/infos-kernel
KERNEL_CMDLINE="boot-device=ata0 init=/usr/init pgalloc.debug=0 pgalloc.algorithm=simple objalloc.debug=0 sched.debug=0 sched.algorithm=cfs syslog=serial $*"
QEMU=qemu-system-x86_64
PORT=`whoami | md5sum | cut -b 1-3 | awk '{print strtonum("0x"$1)}'`

$QEMU -display vnc=localhost:$PORT -kernel $KERNEL -m 6G -debugcon stdio -hda $ROOTFS -append "$KERNEL_CMDLINE"
