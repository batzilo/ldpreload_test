/*
 * This file "overwrites" some C standard library functions
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
 * A custom printf() function that adds a "Hi! " prefix.
 * Since printf() is variadic, we cannot write a variadic wrapper of it.
 * Instead of a variable number of arguments, we have to use functions
 * that take a single va_list pointer.
 * See : http://c-faq.com/varargs/handoff.html
 */
int printf(const char *format, ...)
{
	va_list arg;
	int done = 0;

	va_start(arg, format);
	done += fprintf(stdout, "%s ", "Hi!");
	done += vfprintf(stdout, format, arg);
	va_end(arg);

	return done;
}

ssize_t insist_write(int fd, const void *buf, size_t count)
{
	ssize_t len = 0;
	while (len < strlen(buf)) {
		len += write(1, buf+len, strlen(buf)-len);
	}
	return len;
}

/*
 * A custom puts() function that adds a "Hi! " prefix.
 * Uses insist_write(), which in turn uses write().
 *
 * FIXME:
 * Actually, this is not compliant with libc puts().
 * Original puts() will do a buffered write.
 * This puts() will do "direct"/"unbuffered" write.
 */
int puts(const char *s)
{
	int i = 0;
	const char *r = "Hi! ";

	i += insist_write(1, r, strlen(r));
	i += insist_write(1, s, strlen(s));
	i += insist_write(1, "\n", 1);

	return i;
}
