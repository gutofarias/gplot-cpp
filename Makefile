# -*- Makefile -*-

obj:
	g++ -c gplot-cpp.cpp -I gplot-cpp.h -o gplot-cpp.o


lib:
	ar -rcs libgnuplot-cpp.a gplot-cpp.o


static: obj lib


dynamic:
	g++ -dynamiclib gplot-cpp.cpp -I gplot-cpp.h -o libgplot-cpp.dylib


static_move_to_path:
	sudo mv libgplot-cpp.a /usr/loca/lib/libgplot-cpp.a


dynamic_move_to_path:
	sudo mv libgplot-cpp.dylib /usr/local/lib/libgplot-cpp.dylib
