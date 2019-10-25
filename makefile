all: main.exe

main.exe: main.o
	gcc main.o -o main.exe -L./GL -L./GL/GLEW -L./GL/GLFW -lopengl32 -lglew32 -lglfw3 -lgdi32

main.o: main.c
	gcc -c main.c -I./GL -I./GL -o main.o

clean: 
	rm -rf *.o *.exe
