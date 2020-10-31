.PHONY: build clean

EXECUTABLE = bin/${TARGET}/${TARGET}

SOURCES = $(wildcard ${TARGET}/*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, ${SOURCES})
GFLAGS  = -O3 -Wall

build: makedirs $(OBJECTS)
	g++ $(GFLAGS) bin/${TARGET}/*.o -o $(EXECUTABLE)

%.o: %.cpp
	g++ $(GFLAGS) -g -I common -c $< -o bin/$@

clean:
	rm -rf bin/

makedirs:
	mkdir -p bin/${TARGET}

test: build
	sh scripts/test.sh ${TARGET}
