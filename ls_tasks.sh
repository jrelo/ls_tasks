make
insmod ls_tasks.ko
lsmod|grep ls_tasks
dmesg|grep ls_tasks:
rmmod ls_tasks

