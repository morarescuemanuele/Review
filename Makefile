main.exe: main.cpp src/database.cpp src/library.cpp src/sysman.cpp src/user.cpp src/exceptions.cpp
	g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude main.cpp src/database.cpp src/library.cpp src/sysman.cpp src/user.cpp src/exceptions.cpp -o main.exe

clean:
	rm -f main.exe