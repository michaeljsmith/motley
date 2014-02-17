CXX=clang++
CXXFLAGS=-g --std=c++11 -stdlib=libc++ -Werror -Weverything -pedantic -Wno-c++98-compat -Wno-padded -Wno-float-equal -Wno-global-constructors -Wno-exit-time-destructors `sdl-config --cflags`
LDFLAGS=-g `sdl-config --libs` --std=c++11 -stdlib=libc++ -Werror -Weverything -framework OpenGL -framework Cocoa -lpthread

include build/buildtree/buildtree.mak
