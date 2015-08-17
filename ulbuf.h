#include <stddef.h>

extern char *bufnew(size_t size);
extern char *bufext(char **base, char *tail, size_t n);
extern char *bufncat(char **base, char *tail, const char *s, size_t);
extern char *bufcat(char **base, char *tail, const char *s);
extern void bufdel(char *buf);
