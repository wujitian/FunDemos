#! /bin/sh
# Created Time: 2016-04-23 14:27:11
#

if [ "$#" != "0" ]; then
    ctags * -R $* --c++-kinds=+p --fields=+iaSl --extra=+q
else
    #ctags -R --c++-kinds=+p --fields=+iaS --extra=+q
    echo "ctag * -R xxxdir"
    ctags * -R \
            zxnn_test \
          --c++-kinds=+p --fields=+iaS --extra=+q
fi

