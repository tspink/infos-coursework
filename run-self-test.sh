#!/bin/sh

./build.sh
rm output.txt

TOP=`pwd`
INFOS_DIR=$TOP/infos
INFOS_USER_DIR=$TOP/infos-user
ROOTFS=$INFOS_USER_DIR/bin/rootfs.tar
KERNEL=$INFOS_DIR/out/infos-kernel
KERNEL_CMDLINE="boot-device=ata0 init=/usr/init pgalloc.debug=0 pgalloc.algorithm=buddy pgalloc.self-test=1 objalloc.debug=0 sched.debug=0 sched.algorithm=cfs syslog=serial $*"
QEMU=qemu-system-x86_64

$QEMU -kernel $KERNEL -m 6G -debugcon file:output.txt -hda $ROOTFS -append "$KERNEL_CMDLINE"

cat output.txt | sed -n "/PAGE ALLOCATOR SELF TEST - BEGIN/,/PAGE ALLOCATOR SELF TEST - COMPLETE/p" > output.txt
