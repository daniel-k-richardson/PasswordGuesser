pass: main.o linked_list.o password_generator.o
	gcc main.o linked_list.o password_generator.o -o pass

main.o: main.c
	gcc -c main.c

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c

password_generator.o: password_generator.c password_generator.h
	gcc -c password_generator.c

clean:
	rm *.o pass