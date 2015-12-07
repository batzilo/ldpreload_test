all : main mylib.so

main : main.c
	$(CC) -o main main.c

mylib.so : mylib.c
	$(CC) -shared -fpic mylib.c -o mylib.so

.PHONY : clean

clean :
	$(RM) main mylib.so
