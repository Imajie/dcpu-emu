DIRS=. hardware
SOURCES=$(foreach dir,${DIRS},$(wildcard ${dir}/*.c))
OBJS=$(subst .c,.o,${SOURCES})
TARGET=dcpu_emu

CC=gcc -std=gnu99
CFLAGS=$(shell pkg-config --cflags sdl)
SDL_LIBS=$(shell pkg-config --libs sdl)

LIBS=${SDL_LIBS}

${TARGET}: ${OBJS}
	${CC} -o $@ $^ ${LIBS}

.PHONY: clean realclean depend
	
depend:
	makedepend ${SOURCES} -- ${CFLAGS}

realclean: clean
	-rm ${TARGET}

clean:
	-rm ${OBJS}
# DO NOT DELETE

./dcpu.o: dcpu.h /usr/include/stdint.h /usr/include/features.h
./dcpu.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./dcpu.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
./dcpu.o: /usr/include/bits/wchar.h dcpu_types.h dcpu_ops.h
./dcpu_ops.o: /usr/include/stdio.h /usr/include/features.h
./dcpu_ops.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./dcpu_ops.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
./dcpu_ops.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./dcpu_ops.o: /usr/include/libio.h /usr/include/_G_config.h
./dcpu_ops.o: /usr/include/wchar.h /usr/include/bits/wchar.h
./dcpu_ops.o: /usr/include/xlocale.h /usr/include/bits/stdio_lim.h
./dcpu_ops.o: /usr/include/bits/sys_errlist.h dcpu.h /usr/include/stdint.h
./dcpu_ops.o: dcpu_types.h dcpu_ops.h
./main.o: /usr/include/stdio.h /usr/include/features.h
./main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
./main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
./main.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
./main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./main.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
./main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
./main.o: /usr/include/sys/types.h /usr/include/time.h
./main.o: /usr/include/sys/select.h /usr/include/bits/select.h
./main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
./main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
./main.o: /usr/include/alloca.h dcpu.h /usr/include/stdint.h dcpu_types.h
hardware/LEM1802_builtin.o: hardware/LEM1802_builtin.h hardware/LEM1802.h
hardware/LEM1802_builtin.o: hardware_device.h /usr/include/stdint.h
hardware/LEM1802_builtin.o: /usr/include/features.h /usr/include/sys/cdefs.h
hardware/LEM1802_builtin.o: /usr/include/bits/wordsize.h
hardware/LEM1802_builtin.o: /usr/include/gnu/stubs.h
hardware/LEM1802_builtin.o: /usr/include/gnu/stubs-64.h
hardware/LEM1802_builtin.o: /usr/include/bits/wchar.h dcpu.h
hardware/LEM1802.o: hardware_device.h /usr/include/stdint.h
hardware/LEM1802.o: /usr/include/features.h /usr/include/sys/cdefs.h
hardware/LEM1802.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
hardware/LEM1802.o: /usr/include/gnu/stubs-64.h /usr/include/bits/wchar.h
hardware/LEM1802.o: dcpu.h hardware/LEM1802.h hardware/LEM1802_builtin.h
hardware/LEM1802.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
hardware/LEM1802.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
hardware/LEM1802.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
hardware/LEM1802.o: /usr/include/sys/types.h /usr/include/bits/types.h
hardware/LEM1802.o: /usr/include/bits/typesizes.h /usr/include/time.h
hardware/LEM1802.o: /usr/include/sys/select.h /usr/include/bits/select.h
hardware/LEM1802.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
hardware/LEM1802.o: /usr/include/sys/sysmacros.h
hardware/LEM1802.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
hardware/LEM1802.o: /usr/include/stdio.h /usr/include/libio.h
hardware/LEM1802.o: /usr/include/_G_config.h /usr/include/wchar.h
hardware/LEM1802.o: /usr/include/xlocale.h /usr/include/bits/stdio_lim.h
hardware/LEM1802.o: /usr/include/bits/sys_errlist.h
