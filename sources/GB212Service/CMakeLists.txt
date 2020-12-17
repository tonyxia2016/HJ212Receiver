project(GB212Receiver)

cmake_minimum_required(VERSION 2.8)

set (VERSION 1.0.0)

add_definitions (-DCMAKE -DVERSION=\"${VERSION}\")

add_definitions("-DUSE_MOSQUITTO")
add_definitions("-DPUGIXML_HEADER_ONLY")

INCLUDE_DIRECTORIES(../include)

set(GB_SRC 
	./GB212DataMiddleware.cpp
	./Connection.cpp
	./DataMiddleware.cpp
	./MainApp.cpp
	./MainService.cpp
	./main.cpp)


if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(WIN32)
	set(BOOST_ROOT_DIR D:\\env\\local\\boost_1_69_0)
endif(WIN32)

# 在搜索Boost的package之前，可以通过设置一些变量来帮助boost库的查找
#set (BOOST_ROOT /usr/local/)
#set (BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
#set (BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

find_library(Boost REQUIRED COMPONENTS thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# ========================================
# Include projects
# ========================================

set(GB_LIBS
	pthread
	boost_thread
	boost_locale
	yaml-cpp)

add_executable(GB212Receiver ${GB_SRC})
target_link_libraries(GB212Receiver ${GB_LIBS})

install(TARGETS GB212Receiver RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

