cc = g++
porm = server
source = main.cpp src/*

$(porm) : $(source)
	$(cc) -o $(porm) $(source) -ljsoncpp
