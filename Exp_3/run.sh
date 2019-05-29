#!/bin/bash
make
cd call_os4_module/
make 
cd ..
sudo insmod os4_module.ko 
sudo insmod call_os4_module/call_os4_module_add_time.ko
sudo rmmod call_os4_module_add_time
sudo insmod call_os4_module/call_os4_module_add_time.ko
sudo rmmod call_os4_module_add_time
sudo insmod call_os4_module/call_os4_module_add_time.ko
sudo rmmod call_os4_module_add_time
sudo rmmod os4_module
