# The first rule is executed when the
# command make is typed in the local folder:
all: run

# executable deps and command to build it:
run: run.o generator.o renderer.o tile.o
	g++ run.o generator.o renderer.o tile.o -o run -l SDL2-2.0.0

#run.o deps and command to build it:
run.o: run.cpp generator.h renderer.h
	g++ -c run.cpp -o run.o

renderer.o: renderer.cpp renderer.h generator.h
	g++ -c renderer.cpp -o renderer.o

generator.o: generator.cpp generator.h tile.h
	g++ -c generator.cpp -o generator.o

tile.o: tile.cpp tile.h
	g++ -c tile.cpp -o tile.o

# Special rule to remove all build files
clean:
	rm -rf *.o run
