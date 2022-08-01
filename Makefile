# * Makefile created by Chapardev
# * It handles compilation and linking

EXECUTABLE_NAME = BinToDec
CHECKS = -Wall -pedantic-errors
LIBS = -lraylib -lgdi32 -lwinmm
NO_CONSOLE = -Wl,-subsystem,windows
RAYLIB_INCLUDE_PATH = C:/raylib/include
RAYLIB_LIB_PATH = C:/raylib/lib

default:
	g++ -std=c++23 -O3 -c ./*.cpp -I$(RAYLIB_INCLUDE_PATH) $(CHECKS)
	g++ -static ./*.o -o $(EXECUTABLE_NAME) -L$(RAYLIB_LIB_PATH) $(LIBS) $(NO_CONSOLE)
	del *.o