SOURCES=$(wildcard *.c)
OBJS=$(subst .c,.o,${SOURCES})
TARGET=dcpu_emu

CC=gcc -std=gnu99
CFLAGS=

${TARGET}: ${OBJS}
	${CC} -o $@ $^ 

.PHONY: clean realclean depend
	
depend:
	makedepend ${SOURCES} -- ${CFLAGS}

realclean: clean
	-rm ${TARGET}

clean:
	-rm ${OBJS}
# DO NOT DELETE

dcpu.o: dcpu.h /usr/include/stdint.h /usr/include/features.h
dcpu.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
dcpu.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
dcpu.o: /usr/include/bits/wchar.h dcpu_types.h dcpu_ops.h
dcpu_ops.o: /usr/include/stdio.h /usr/include/features.h
dcpu_ops.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
dcpu_ops.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
dcpu_ops.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
dcpu_ops.o: /usr/include/libio.h /usr/include/_G_config.h
dcpu_ops.o: /usr/include/wchar.h /usr/include/bits/wchar.h
dcpu_ops.o: /usr/include/xlocale.h /usr/include/bits/stdio_lim.h
dcpu_ops.o: /usr/include/bits/sys_errlist.h dcpu.h /usr/include/stdint.h
dcpu_ops.o: dcpu_types.h dcpu_ops.h
main.o: dcpu.h /usr/include/stdint.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/include/bits/wchar.h
