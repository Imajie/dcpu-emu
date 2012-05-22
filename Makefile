DIRS=. hardware
SOURCES=$(foreach dir,${DIRS},$(wildcard ${dir}/*.c))
OBJS=$(subst .c,.o,${SOURCES})
TARGET=dcpu_emu

CC=gcc -std=gnu99 -ggdb
CFLAGS=$(shell pkg-config --cflags sdl)
SDL_LIBS=$(shell pkg-config --libs sdl)

LIBS=${SDL_LIBS}

.PHONY: all
all: ${TARGET}


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
./dcpu.o: /usr/include/bits/wchar.h dcpu_types.h dcpu_ops.h hardware_device.h
./dcpu.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
./dcpu.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
./dcpu.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
./dcpu.o: /usr/include/xlocale.h /usr/include/sys/types.h
./dcpu.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./dcpu.o: /usr/include/time.h /usr/include/sys/select.h
./dcpu.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./dcpu.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
./dcpu.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
./dcpu_ops.o: /usr/include/stdio.h /usr/include/features.h
./dcpu_ops.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
./dcpu_ops.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
./dcpu_ops.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
./dcpu_ops.o: /usr/include/libio.h /usr/include/_G_config.h
./dcpu_ops.o: /usr/include/wchar.h /usr/include/bits/wchar.h
./dcpu_ops.o: /usr/include/xlocale.h /usr/include/bits/stdio_lim.h
./dcpu_ops.o: /usr/include/bits/sys_errlist.h dcpu.h /usr/include/stdint.h
./dcpu_ops.o: dcpu_types.h dcpu_ops.h hardware_device.h
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
./main.o: /usr/include/alloca.h /usr/include/signal.h
./main.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
./main.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
./main.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
./main.o: /usr/include/bits/sigthread.h /usr/include/unistd.h
./main.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
./main.o: /usr/include/bits/confname.h /usr/include/getopt.h
./main.o: /usr/include/ctype.h /usr/include/poll.h /usr/include/sys/poll.h
./main.o: /usr/include/bits/poll.h dcpu.h /usr/include/stdint.h dcpu_types.h
./main.o: hardware/sdl.h /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
./main.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
./main.o: /usr/include/SDL/SDL_platform.h /usr/include/string.h
./main.o: /usr/include/inttypes.h /usr/include/iconv.h
./main.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
./main.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
./main.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
./main.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
./main.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
./main.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
./main.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
./main.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
./main.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
./main.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
./main.o: /usr/include/SDL/SDL_version.h hardware/generic_keyboard.h
./main.o: hardware_device.h hardware/LEM1802.h hardware/sdl.h
./main.o: hardware/generic_keyboard.h hardware/generic_clock.h dcpu.h
hardware/LEM1802.o: hardware_device.h /usr/include/stdint.h
hardware/LEM1802.o: /usr/include/features.h /usr/include/sys/cdefs.h
hardware/LEM1802.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
hardware/LEM1802.o: /usr/include/gnu/stubs-64.h /usr/include/bits/wchar.h
hardware/LEM1802.o: dcpu.h hardware/LEM1802.h hardware/sdl.h
hardware/LEM1802.o: hardware/LEM1802_builtin.h /usr/include/stdlib.h
hardware/LEM1802.o: /usr/include/bits/waitflags.h
hardware/LEM1802.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
hardware/LEM1802.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
hardware/LEM1802.o: /usr/include/xlocale.h /usr/include/sys/types.h
hardware/LEM1802.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
hardware/LEM1802.o: /usr/include/time.h /usr/include/sys/select.h
hardware/LEM1802.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
hardware/LEM1802.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
hardware/LEM1802.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
hardware/LEM1802.o: /usr/include/stdio.h /usr/include/libio.h
hardware/LEM1802.o: /usr/include/_G_config.h /usr/include/wchar.h
hardware/LEM1802.o: /usr/include/bits/stdio_lim.h
hardware/LEM1802.o: /usr/include/bits/sys_errlist.h
hardware/LEM1802_builtin.o: hardware/LEM1802_builtin.h hardware/LEM1802.h
hardware/LEM1802_builtin.o: hardware_device.h /usr/include/stdint.h
hardware/LEM1802_builtin.o: /usr/include/features.h /usr/include/sys/cdefs.h
hardware/LEM1802_builtin.o: /usr/include/bits/wordsize.h
hardware/LEM1802_builtin.o: /usr/include/gnu/stubs.h
hardware/LEM1802_builtin.o: /usr/include/gnu/stubs-64.h
hardware/LEM1802_builtin.o: /usr/include/bits/wchar.h dcpu.h hardware/sdl.h
hardware/generic_clock.o: /usr/include/stdlib.h /usr/include/features.h
hardware/generic_clock.o: /usr/include/sys/cdefs.h
hardware/generic_clock.o: /usr/include/bits/wordsize.h
hardware/generic_clock.o: /usr/include/gnu/stubs.h
hardware/generic_clock.o: /usr/include/gnu/stubs-64.h
hardware/generic_clock.o: /usr/include/bits/waitflags.h
hardware/generic_clock.o: /usr/include/bits/waitstatus.h
hardware/generic_clock.o: /usr/include/endian.h /usr/include/bits/endian.h
hardware/generic_clock.o: /usr/include/bits/byteswap.h /usr/include/xlocale.h
hardware/generic_clock.o: /usr/include/sys/types.h /usr/include/bits/types.h
hardware/generic_clock.o: /usr/include/bits/typesizes.h /usr/include/time.h
hardware/generic_clock.o: /usr/include/sys/select.h
hardware/generic_clock.o: /usr/include/bits/select.h
hardware/generic_clock.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
hardware/generic_clock.o: /usr/include/sys/sysmacros.h
hardware/generic_clock.o: /usr/include/bits/pthreadtypes.h
hardware/generic_clock.o: /usr/include/alloca.h /usr/include/stdio.h
hardware/generic_clock.o: /usr/include/libio.h /usr/include/_G_config.h
hardware/generic_clock.o: /usr/include/wchar.h /usr/include/bits/wchar.h
hardware/generic_clock.o: /usr/include/bits/stdio_lim.h
hardware/generic_clock.o: /usr/include/bits/sys_errlist.h
hardware/generic_clock.o: hardware/generic_clock.h dcpu.h hardware_device.h
hardware/generic_clock.o: /usr/include/stdint.h dcpu.h
hardware/generic_keyboard.o: /usr/include/stdlib.h /usr/include/features.h
hardware/generic_keyboard.o: /usr/include/sys/cdefs.h
hardware/generic_keyboard.o: /usr/include/bits/wordsize.h
hardware/generic_keyboard.o: /usr/include/gnu/stubs.h
hardware/generic_keyboard.o: /usr/include/gnu/stubs-64.h
hardware/generic_keyboard.o: /usr/include/bits/waitflags.h
hardware/generic_keyboard.o: /usr/include/bits/waitstatus.h
hardware/generic_keyboard.o: /usr/include/endian.h /usr/include/bits/endian.h
hardware/generic_keyboard.o: /usr/include/bits/byteswap.h
hardware/generic_keyboard.o: /usr/include/xlocale.h /usr/include/sys/types.h
hardware/generic_keyboard.o: /usr/include/bits/types.h
hardware/generic_keyboard.o: /usr/include/bits/typesizes.h
hardware/generic_keyboard.o: /usr/include/time.h /usr/include/sys/select.h
hardware/generic_keyboard.o: /usr/include/bits/select.h
hardware/generic_keyboard.o: /usr/include/bits/sigset.h
hardware/generic_keyboard.o: /usr/include/bits/time.h
hardware/generic_keyboard.o: /usr/include/sys/sysmacros.h
hardware/generic_keyboard.o: /usr/include/bits/pthreadtypes.h
hardware/generic_keyboard.o: /usr/include/alloca.h dcpu.h hardware_device.h
hardware/generic_keyboard.o: /usr/include/stdint.h /usr/include/bits/wchar.h
hardware/generic_keyboard.o: dcpu.h hardware/generic_keyboard.h
hardware/generic_keyboard.o: hardware/sdl.h
hardware/sdl.o: /usr/include/stdio.h /usr/include/features.h
hardware/sdl.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
hardware/sdl.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
hardware/sdl.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
hardware/sdl.o: /usr/include/libio.h /usr/include/_G_config.h
hardware/sdl.o: /usr/include/wchar.h /usr/include/bits/wchar.h
hardware/sdl.o: /usr/include/xlocale.h /usr/include/bits/stdio_lim.h
hardware/sdl.o: /usr/include/bits/sys_errlist.h /usr/include/SDL/SDL.h
hardware/sdl.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
hardware/sdl.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
hardware/sdl.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
hardware/sdl.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
hardware/sdl.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
hardware/sdl.o: /usr/include/sys/types.h /usr/include/time.h
hardware/sdl.o: /usr/include/sys/select.h /usr/include/bits/select.h
hardware/sdl.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
hardware/sdl.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
hardware/sdl.o: /usr/include/alloca.h /usr/include/string.h
hardware/sdl.o: /usr/include/inttypes.h /usr/include/stdint.h
hardware/sdl.o: /usr/include/ctype.h /usr/include/iconv.h
hardware/sdl.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
hardware/sdl.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
hardware/sdl.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
hardware/sdl.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
hardware/sdl.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
hardware/sdl.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
hardware/sdl.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
hardware/sdl.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
hardware/sdl.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
hardware/sdl.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
hardware/sdl.o: /usr/include/SDL/SDL_version.h hardware/sdl.h
