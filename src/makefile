../build/main.exe: main.cpp ./redBlackTree/node.h ./redBlackTree/redBlackTree.h
	g++ -o ../build/main.exe main.cpp ./redBlackTree/node.h ./redBlackTree/redBlackTree.h

test: ../build/main.exe
	../build/main.exe

clean:
	rm ../build/main.exe
	clear