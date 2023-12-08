assembler: main.o preproccesor.o file.o assembler.o string.o variables.o
	gcc -o assembler main.o preproccesor.o file.o assembler.o string.o variables.o

main.o: main.c assembler.h file.h preproccesor.h string.h variables.h
	gcc -c main.c

preproccesor.o: preproccesor.c preproccesor.h
	gcc -c preproccesor.c

file.o: file.c file.h
	gcc -c file.c

assembler.o: assembler.c assembler.h
	gcc -c assembler.c

string.o: string.c string.h
	gcc -c string.c

variables.o: variables.c variables.h
	gcc -c variables.c

clean:
	rm *.o assembler