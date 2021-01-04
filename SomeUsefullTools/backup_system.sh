#! /bin/sh
# Created Time: 2019-10-24 19:38:08
#
tar cvpzf backup.tgz --exclude=/proc --exclude=/lost+found --exclude=/backup.tgz --exclude=/mnt --exclude=/sys --exclude=/home /
