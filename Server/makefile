# makefile server

myserver:main.o core.o sock.o online.o database.o
	gcc -O main.o core.o sock.o online.o database.o -o myserver -lsqlite3
main.o:main.c
	gcc main.c -c -Wall -o main.o
core.o:core.c
	gcc core.c -c -Wall -o core.o
sock.o:sock.c
	gcc sock.c -c -Wall -o sock.o
online.o:online.c
	gcc online.c -c -Wall -o online.o
database.o:database.c
	gcc database.c -c -Wall -o database.o -lsqlite3

.PHONY:clean
clean:
	rm *.o myserver -f 
