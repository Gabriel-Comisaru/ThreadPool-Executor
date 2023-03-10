build:
	gcc -m32 -std=c99 main.c Stack.c Queue.c Functii.c Node.c -o tema2
run:
	./tema2
clean:
	rm -rf tema2