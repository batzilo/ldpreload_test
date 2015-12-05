all : main puts.so

main : main.c
	$(CC) -o main main.c

puts.so : puts.c
	$(CC) -shared -fpic puts.c -o puts.so

.PHONY : clean

clean :
	$(RM) main puts.so
