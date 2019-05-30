#!/bin/bash
make > /dev/null
sudo insmod charMsgModule.ko
dmesg | tail -n 10
ls -al /dev/ | grep char*
gcc userApp/tst_charMsgDriver.c -o a.out > /dev/null
sudo ./a.out
sudo rmmod charMsgModule