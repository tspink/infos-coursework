#!/bin/sh

PORT=`whoami | md5sum | cut -b 1-3 | awk '{print strtonum("0x"$1)+5900}'`
vncviewer localhost:$PORT
