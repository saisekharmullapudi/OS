
#include "syscall.h"
int main()
{
	
	OpenFileId input = ConsoleInput;
	OpenFileId output = ConsoleOutput;
	char* str;
	Read(str, 8,input);
	Write(str, 8, output);
	ThreadFork(0);
	ThreadYield();
	ThreadExit(0);
}
