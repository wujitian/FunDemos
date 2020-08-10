PROJECT (TEST)
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set(TARGET_NAME example)

#file(GLOB SRC_LIST example14.c)
#file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_1-1.cpp)
#file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_03-drawcommands.cpp)
#file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_03-primitiverestart.cpp)
#file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_03-instancing.cpp)    # not finish
#file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_04-gouraud.cpp)    # not finish
#file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_06-load-texture.cpp) 
#file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_06-multitexture.cpp) 
file(GLOB SRC_LIST src/*.c src/*.cpp red_book_example_06-cubemap.cpp) 

set(HELLO_BINARY_DIR "FabioKong test.")

MESSAGE(STATUS "This is HELLO_BINARY_DIR " ${HELLO_BINARY_DIR})
MESSAGE(STATUS "This is HELLO_SOURCE_DIR " ${HELLO_SOURCE_DIR})
MESSAGE(STATUS "This is PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "This is CMAKE_SOURCE_DIR " ${CMAKE_SOURCE_DIR})

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_DRELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11 )

add_definitions("-D_DEBUG")

ADD_EXECUTABLE(${TARGET_NAME} ${SRC_LIST})

include_directories(
    ./include
    ../glfw-3.3.2/include
)

#-lGL -lGLU -lglut -lm -lX11 -lXrandr -lXxf86vm -lXcursor -lXinerama -ldl
target_link_libraries(${TARGET_NAME}
    -lGL -lGLU -lglut -lm -ldl -lGLEW -lglfw
)


