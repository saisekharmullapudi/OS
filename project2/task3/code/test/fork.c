#include "syscall.h"

void func1()
{
	char* c; 
	Read(c, 7, 0);
	Write(c,7,0);
	Halt();
}
int main()
{
	ThreadFork(func1);
}