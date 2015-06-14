TESTS = check_fft
check_PROGRAMS = check_fft
check_fft_SOURCES = check_fft.c $(top_builddir)/fft/fft.h
check_fft_CFLAGS = @CHECK_CFLAGS@ -I$(top_srcdir)
check_fft_LDADD = -lm $(top_builddir)/fft/libfft.la @CHECK_LIBS@
