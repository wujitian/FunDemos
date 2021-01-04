#! /bin/sh
# Created Time: 2019-12-11 09:45:21
#

#################################################
## new system lib
sudo apt-get upgrade
sudo apt-get install -y vim
sudo apt-get install -y ssh
sudo apt-get install -y git
sudo apt-get install -y ctags
sudo apt-get install -y console
sudo apt-get install -y fcitx
sudo apt-get install -y fcitx-sunpinyin
sudo apt-get install -y docker.io
sudo apt-get install -y u-boot-tools
sudo apt-get install -y konsole

#################################################
## install tvm neccessary lib
sudo apt-get update
sudo apt-get install -y python3 python3-dev python3-setuptools gcc libtinfo-dev zlib1g-dev build-essential cmake libedit-dev libxml2-dev libatlas-base-dev

pip3 install --user numpy decorator attrs
pip3 install --user tornado
pip3 install --user psutil xgboost

#################################################
## fix initramfs-tools
#sudo rm -f /var/lib/dpkg/info/initramfs-tools.post*
#sudo rm -f /var/lib/dpkg/info/initramfs-tools.pre*
#
#sudo rm -f /var/lib/dpkg/info/bcmwl-kernel-source.post*
#sudo rm -f /var/lib/dpkg/info/bcmwl-kernel-source.pre*
#
#sudo dpkg --configure -a


#################################################
## add neccessary lib
sudo apt-get install -y libopenblas-dev liblapack-dev libopencv-dev libboost-all-dev

