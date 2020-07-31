# OpenGL

./examples --> 里面是一些自己用来学习OpenGL的例子，包括《OpenGL编程精粹》和《OpenGL编程指南》中的例子。

./glfw-3.3.2/ --> 里面是下载的glfw的全部源代码。

./check_version/ --> 一个example可以用来检测OpenGL的版本。

./GLTools/ --> 《OpenGL超级宝典》需要的代码，但目前没有调试成功。


glfw的编译过程:
首先修改CMakeList.txt使之编译动态库
然后进入到编译好的libglfw.so所在目标
执行:
sudo ln -s libglfw.so.3.3 /usr/lib/libglfw.so.3
sudo ln -s /usr/lib/libglfw.so /usr/lib/libglfw.so.3

