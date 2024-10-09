
TARGET = test.exe
LIBS_PATH = -O0
LIBS = -static
WARNINGS = -Wall -Wextra -Werror
INCLUDE = 
CC = g++
CPPSTD = -std=c++11
PREF_SRC = ./
SRC = $(wildcard $(PREF_SRC)*.cpp)
$(TARGET):
	$(CC) $(INCLUDE) $(LIBS_PATH) $(WARNINGS) $(CPPSTD) $(SRC) -o $(TARGET) $(LIBS)
clean:
	rm $(TARGET)
clear:
	rm $(TARGET)
run:
	./$(TARGET)
e: clear $(TARGET) run
	
