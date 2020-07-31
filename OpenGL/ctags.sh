#! /bin/sh
# Created Time: 2016-04-23 14:27:11
#

EXTRA_CMD=extra # 5.9

for eachline in `ctags --version`; do

    TAGS=`echo ${eachline} | awk -F " " '{print $1}'`

    if [ "${TAGS}" = "5.8," ]; then

        #
        # git clone ctags 最新的下来进行编译安装后就可以得到 5.8 的
        #
        echo "TAGS = ${TAGS}"
        echo "ctags version is 5.8"
        EXTRA_CMD=extras # 5.8
    fi
done

if [ "$#" != "0" ]; then
    ctags * -R $* --c++-kinds=+p --fields=+iaSl --${EXTRA_CMD}=+q
else
    #ctags -R --c++-kinds=+p --fields=+iaS --${EXTRA_CMD}=+q
    echo "ctag * -R xxxdir"
    ctags * -R \
              ./examples/ \
              ./glfw-3.3.2/src/ \
              ./glfw-3.3.2/include/ \
              --c++-kinds=+p --fields=+iaS --${EXTRA_CMD}=+q
fi

