TARGET=schedule.exe

#
# Specifiy the target
all:	$(TARGET)

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
$(TARGET):	main.o
	g++  main.o RequirementsLL.o -o $(TARGET) 

# Specify how the object files should be created from source files
main.o:	main.cpp
	g++ -c main.cpp
	g++ -c RequirementsLL.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o $(TARGET)

run:	$(TARGET)
	./$(TARGET)
