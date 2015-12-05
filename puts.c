#include <unistd.h>

int mylen(const char *s)
{
	int i = 0;
	while (*s++ != '\0') i++;
	return i;
}

int puts(const char *s)
{
	int i, len;
	const char *r = "Hi! ";

	i = 0;

	len = 0;
	while (len < mylen(r)) {
		len += write(1, r+len, mylen(r)-len);
	}
	i += len;

	len = 0;
	while (len < mylen(s)) {
		len += write(1, s+len, mylen(s)-len);
	}
	i += len;
	
	write(1, "\n", 1);
	++i;

	return i;
}
