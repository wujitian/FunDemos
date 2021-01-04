# OpenGL

./include --> 一些公共的头文件

./src --> 一些公共的source文件

./media --> 一些资源文件存放在这里，如图片等

./shaders --> 实现的一些可复用的shader代码

./examples --> 里面是一些自己用来学习OpenGL的例子，包括《OpenGL编程精粹》和《OpenGL编程指南》中的例子。

./glfw-3.3.2/ --> 里面是下载的glfw的全部源代码。

./check_version/ --> 一个example可以用来检测OpenGL的版本。

./GLTools/ --> 《OpenGL超级宝典》需要的代码，但目前没有调试成功。

./demos/ --> 一些有趣的demo
	--> MagicCube, 魔方程序，可以玩
	--> WanHuaTong, 打算做一个万花筒的程序，未完成


glfw的编译过程:
首先修改CMakeList.txt使之编译动态库
然后进入到编译好的libglfw.so所在目标
执行:
sudo ln -s libglfw.so.3.3 /usr/lib/libglfw.so.3
sudo ln -s /usr/lib/libglfw.so.3 /usr/lib/libglfw.so

如何编译带有debug信息的libglfw.so:
先建立build文件夹，然后进入build中执行cmake ..
然后修改src/CMakeFiles/glfw.dir/flags.make文件
在C_FLAGS中加入"-O0 -Wall -g2 -ggdb"
然后在make -j4
这样生成的就是带有debug信息的libglfw.so了

