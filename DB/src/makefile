CC= gcc -c  -ggdb
LINK= gcc  -ggdb -lrt
CFLAGS= -Werror -Wall  -ggdb -lm
INCLUDE= -I ./Include/ \

app_DB: objs/CaseDiaryCurrent.o \
	objs/avlFinal.o
	$(LINK) objs/CaseDiaryCurrent.o \
		objs/avlFinal.o \
	-lpthread -o app_DB

objs/CaseDiaryCurrent.o: src/CaseDiaryCurrent.c
	$(CC) $(CFLAGS) $(INCLUDE) src/CaseDiaryCurrent.c -o objs/CaseDiaryCurrent.o

objs/avlFinal.o: src/avlFinal.c
	$(CC) $(CFLAGS) $(INCLUDE) src/avlFinal.c -o objs/avlFinal.o
