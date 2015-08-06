#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct buffer {
	size_t size;
	char bytes[1];
};

#define BUFFER(buf) ((struct buffer *)((buf) - offsetof(struct buffer, bytes)))

char *bufnew(size_t size)
{
	struct buffer *buf;

	buf = (struct buffer *) malloc(sizeof (struct buffer) + size);
	if (buf) {
		buf->size = size;
		buf->bytes[0] = 0;
		return buf->bytes;
	}
	return 0;
}

char *bufext(char **base, char *tail, size_t n)
{
	size_t len, len1, size;

	if (!tail) return 0;
	len = (size_t) (tail - *base);
	len1 = len + n;
	if ((size = BUFFER(*base)->size) < len1) {
		struct buffer *buffer;

		do
			size *= 2;
		while (size < len1);
		buffer = (struct buffer *)
			realloc(BUFFER(*base), sizeof (struct buffer) + size);
		if (!buffer) return 0;	/* OOM */
		buffer->size = size;
		*base = buffer->bytes;
	}
	/* defensive programming: put a sentinel zero right after the desired
	 * length, so that the buffer is always a legal C string and the user
	 * is free to use use string routines in the standard library. */
	(*base)[len1] = 0;
	return tail = *base + len;
}

char *bufadd(char **base, char *tail, const char *s, size_t n)
{
	if ((tail = bufext(base, tail, n))) {
		memcpy(tail, s, n);
		tail += n;
	}
	return tail;
}

char *bufcat(char **base, char *tail, const char *s)
{
	return (tail) ? bufadd(base, tail, s, strlen(s)) : 0;
}

void bufdel(char *buf)
{
	if (buf)
		free(BUFFER(buf));
}
