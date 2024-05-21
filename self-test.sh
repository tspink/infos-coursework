#!/bin/sh

rm output.txt

./build.sh
./run-self-test.sh &

sleep(10)

cat output.txt | sed -n "/PAGE ALLOCATOR SELF TEST - BEGIN/,/PAGE ALLOCATOR SELF TEST - COMPLETE/p" > output.txt
diff output.txt expected.txt > result.txt
