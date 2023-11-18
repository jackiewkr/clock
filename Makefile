CFLAGS := -Wall
LDFLAGS := -lncurses
INCLUDES := clock.c

build:
	${CC} -o clock ${INCLUDES} ${CFLAGS} ${LDFLAGS}

clean:
	rm -f clock
