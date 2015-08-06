#include "ulbuf.h"
#include <cstring>
#include <cstdio>
#include <ctime>
#include <string>

using namespace std;

const char *token = "hello";
const string token2 = "hello";
const int N = 5000000;

void test(const char *title, void f(void))
{
	clock_t clk = clock();
	f();
	printf("%s:\t%.3f\n", title, 1000.0 * (clock() - clk) / (CLOCKS_PER_SEC));
}

void staticbuf(void)
{
	static char buf[5 * N + 1];
	char *p = buf;

	for (int i = 0; i < N; i++) {
		memcpy(p, token, 5);
		p += 5;
	}
	*p++ = '\0';
}

void ulbuf(void)
{
	char *buf, *p;

	p = buf = bufnew(100);
	for (int i = 0; i < N; i++) {
		p = bufcat(&buf, p, token);
	}
	bufdel(buf);
}

void ulbuf2(void)
{
	char *buf, *p;

	p = buf = bufnew(100);
	for (int i = 0; i < N; i++) {
		p = bufadd(&buf, p, token, 5);
	}
	bufdel(buf);
}

void stlstring(void)
{
	string s;

	for (int i = 0; i < N; i++) {
		s += token;
	}
}

void stlstring2(void)
{
	string s;

	for (int i = 0; i < N; i++) {
		s += token2;
	}
}

int main()
{
	test("staticbuf", staticbuf);
	test("ulbuf", ulbuf);
	test("ulbuf2", ulbuf2);
	test("stlstring", stlstring);
	test("stlstring2", stlstring2);
	return 0;
}
