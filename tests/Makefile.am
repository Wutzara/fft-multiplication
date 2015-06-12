TESTS = check_fft
check_PROGRAMS = check_fft
check_fft_SOURCES = check_fft.c $(top_builddir)/src/fft.h
check_fft_CFLAGS = @CHECK_CFLAGS@
check_fft_LDADD = -lm $(top_builddir)/src/libfft.la @CHECK_LIBS@
