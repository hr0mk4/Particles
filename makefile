all: 
	g++ main.cpp particles.cpp system.cpp GUI.cpp `fltk-config --ldflags`

clean:
	rm a.out