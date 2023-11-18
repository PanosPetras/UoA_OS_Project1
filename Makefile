rootDirectory 		:= $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
commonHeader  		:= $(rootDirectory)/Common/Header
commonSource  		:= $(rootDirectory)/Common/Source
commonBin     		:= bin/common
processDependencies := bin/common/Semaphore.o bin/common/SharedMemory.o bin/common/Buffer.o bin/common/ReadOnlyBuffer.o bin/common/WriteOnlyBuffer.o bin/common/Thread.o

a:
	@echo "Building process A.\n";
	g++ -c -I$(commonHeader) processes/A/processA.cpp -o bin/processes/processA.o
	g++ $(processDependencies) bin/processes/processA.o -o build/processes/processA

b:
	@echo "Building process B.\n";
	g++ -c -I$(commonHeader) processes/B/processB.cpp -o bin/processes/processB.o
	g++ $(processDependencies) bin/processes/processB.o -o build/processes/processB

proj:
	@echo "Building project.\n";
	make clean
	make common
	make a
	make b
	make tests

common:
	@echo "Compiling common objects for the project.\n";

	g++ -c -I$(commonHeader) $(commonSource)/Semaphore.cpp -o $(commonBin)/Semaphore.o
	g++ -c -I$(commonHeader) $(commonSource)/Thread.cpp -o $(commonBin)/Thread.o
	g++ -c -I$(commonHeader) $(commonSource)/SharedMemory.cpp -o $(commonBin)/SharedMemory.o
	g++ -c -I$(commonHeader) $(commonSource)/Buffer.cpp -o $(commonBin)/Buffer.o
	g++ -c -I$(commonHeader) $(commonSource)/ReadOnlyBuffer.cpp -o $(commonBin)/ReadOnlyBuffer.o
	g++ -c -I$(commonHeader) $(commonSource)/WriteOnlyBuffer.cpp -o $(commonBin)/WriteOnlyBuffer.o

run:
	@echo "Building and running project.\n";

clean:
	@echo "Cleaning project files.\n";

	rm -rf bin/common/*
	rm -rf bin/tests/*
	rm -rf build/tests/*
	rm -rf build/A/*
	rm -rf build/B/*

tests:
	@echo "Building tests\n";
	g++ -c -I$(commonHeader) Tests/SemaphoreTest.cpp -o bin/tests/SemaphoreTest.o
	g++ -c -I$(commonHeader) Tests/SharedMemoryTest.cpp -o bin/tests/SharedMemoryTest.o
	g++ -c -I$(commonHeader) Tests/BufferTest.cpp -o bin/tests/BufferTest.o
	g++ bin/common/Semaphore.o bin/tests/SemaphoreTest.o -o build/tests/SemaphoreTest
	g++ bin/common/SharedMemory.o bin/tests/SharedMemoryTest.o -o build/tests/SharedMemoryTest
	g++ bin/common/SharedMemory.o bin/common/Semaphore.o bin/common/Buffer.o bin/common/ReadOnlyBuffer.o bin/common/WriteOnlyBuffer.o bin/tests/BufferTest.o -o build/tests/BufferTest

	@echo "---------------";
	@echo "Running tests\n";
	./build/tests/SemaphoreTest
	./build/tests/SharedMemoryTest
	./build/tests/BufferTest