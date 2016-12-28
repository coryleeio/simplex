A simple cross-platform compatible object oriented wrapper for OpenGL. Used to complete various exercises and tutorials(see tests/)


### Prerequisites

	[Install CMake](https://cmake.org/)

### Windows
	
You'll need visual studio community 2015 installed then:

	git clone --recursive project.git
	cd project
	cd build/
	cmake ..
	select one of the demo projects as 'Startup project'
	start debugger

If you wanted, you could run entirely from commandline with VS by:

	cmake --build .
	./Debug/demo1.exe

### Run on OSX

	git clone --recursive project.git
	cd project
	cd build/
	cmake ..
	make
	./demo1.exe
