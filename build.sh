#!/bin/sh

ln -Tsf `pwd`/coursework infos/oot

make -C infos || exit 1
make -C infos-user fs || exit 1
