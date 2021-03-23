# -*- Makefile -*-

obj:
	g++ -c gplot-cpp.cpp -I gplot-cpp.h -o gplot-cpp.o				# MacOS or Linux 


lib:
	ar -rcs libgnuplot-cpp.a gplot-cpp.o						# MacOS or Linux


static: obj lib


dynamic:
	g++ -dynamiclib gplot-cpp.cpp -I gplot-cpp.h -o libgplot-cpp.dylib		# MacOS
	#g++ -shared -fPIC gplot-cpp.cpp -I gplot-cpp.h -o libgplot-cpp.so		# Linux	


static_move_to_path:
	sudo mv libgplot-cpp.a /usr/loca/lib/libgplot-cpp.a


dynamic_move_to_path:
	sudo mv libgplot-cpp.dylib /usr/local/lib/libgplot-cpp.dylib


include_move_to_path:
	sudo mv gplot-cpp.h /usr/loca/include/gplot-cpp.h
