try: main.o project.o 
	cc main.o project.o  -o try
main.o: main.c project.h
	cc -Wall -c main.c
project.o: project.c project.h
	cc -Wall -c project.c
/*g.o: g.c y.h
	cc -Wall -c g.c*/
