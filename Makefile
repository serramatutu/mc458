.PHONY: build clean

EXECUTABLE = bin/${TARGET}/${TARGET}.out

SOURCES = $(wildcard ${TARGET}/*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, ${SOURCES})
GFLAGS  = -O3 -Wall -std=c++98

build: makedirs $(OBJECTS)
	g++ $(GFLAGS) bin/${TARGET}/*.o -o $(EXECUTABLE)

%.o: %.cpp
	g++ $(GFLAGS) -g -c $< -o bin/$@

clean:
	rm -rf bin/

makedirs:
	mkdir -p bin/${TARGET}

test: build
	sh scripts/test.sh ${TARGET}
