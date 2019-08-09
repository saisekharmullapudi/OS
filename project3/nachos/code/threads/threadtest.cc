#include "kernel.h"
#include "main.h"
#include "thread.h"

void CreateFile(char* name)
{
	char* fname = name;
	kernel->fileSystem->Create(fname, 0);
	OpenFile* f1 = kernel->fileSystem->Open(fname);
	char* buffer = new char[600];
	for (int i = 0; i < 600; i++)
	{
		buffer[i] = (char)1;
	}
	f1->Write(buffer, 600);
	char* buf = new char[f1->Length()];
	/*f1->Read(buf, f1->Length());

	for (int i = 0; i < f1->Length(); i++)
	{
		std::cout << buf[i];
	}*/

	char* f2 = "FileTwo";
	kernel->fileSystem->Create(f2, 0);
	OpenFile* f3 = kernel->fileSystem->Open(f2);
	f3->Write(buffer,600);

	delete f1;
	kernel->currentThread->Finish();
}
void createMutliple(int which)
{
	char* name1 = "multiple1";
	kernel->fileSystem->Create(name1, 0);
	char* name2 = "multiple2";
	kernel->fileSystem->Create(name2, 0);
	char* name3 = "multiple3";
	kernel->fileSystem->Create(name3, 0);
	char* name4 = "multiple4";
	kernel->fileSystem->Create(name4, 0);
	char* name5 = "multiple5";
	kernel->fileSystem->Create(name5, 0);
	char* name6 = "multiple6";
	kernel->fileSystem->Create(name6, 0);
	char* name7 = "multiple7";
	kernel->fileSystem->Create(name7, 0);
	char* name8 = "multiple8";
	kernel->fileSystem->Create(name8, 0);
	char* name9 = "multiple1";
	kernel->fileSystem->Create(name9, 0);
	char* name10 = "multiple1";
	kernel->fileSystem->Create(name10, 0);
	char* name11 = "multiple1";
	kernel->fileSystem->Create(name11, 0);
	for (int i = 0; i < 2000; i++)
	{
		kernel->currentThread->Yield();
	}
	



	
}
void ReadFile(char* name)
{

	OpenFile* f1 = kernel->fileSystem->Open(name);
	int fileLength = f1->Length();
	char* readBuffer = new char[fileLength];
	f1->Seek(0);
	f1->Read(readBuffer, fileLength);


	delete f1;
	kernel->currentThread->Finish();
}

void Write1(char* fileName)
{
	char* name = fileName;

	OpenFile* f1 = kernel->fileSystem->Open(name);
	int fileLength = f1->Length();
	char* writeBuffer = new char[fileLength];
	f1->Seek(f1->Length());

	for (int i = 0; i < fileLength; i++)
	{
		writeBuffer[i] = '1';
	}

	f1->Write(writeBuffer, fileLength);
	delete f1;
	kernel->currentThread->Finish();
}

void deletefile(int which)
{
	char* name = "FileOne";
	kernel->fileSystem->Remove(name);
	kernel->currentThread->Finish();

}
void FileExtention(int which)
{
	int number = 1;
	char* fileName = "extend";

	//Extension part yet to be integrated
	kernel->fileSystem->Create(fileName, 0);

	OpenFile* openFilePtr = kernel->fileSystem->Open(fileName);
	char* buffer = new char[6000];

	std::cout << "Before writing:" << openFilePtr->Length() << std::endl;
	for (int i = 0; i < 6000; i++)
	{
		buffer[i] = (char)1;
	}

	for (int p = 0; p < 14; p++)
	{
		openFilePtr->Seek(openFilePtr->Length());
		openFilePtr->Write(buffer, 6000);
	}

	std::cout << "After writing:" << openFilePtr->Length() << std::endl;
	char* readBuffer = new char[openFilePtr->Length()];


	delete openFilePtr;
	kernel->currentThread->Finish();
}

void
ThreadTest()
{
	char* fileName1 = "FileOne";
	char* fileName2 = "FileTwo";

	Thread* t = new Thread("CreateThread1");
	t->Fork((VoidFunctionPtr)CreateFile, (char*)fileName1);

	Thread* t1 = new Thread("CreateThread2");
	t1->Fork((VoidFunctionPtr)CreateFile, (char*)fileName2);


	Thread* write1 = new Thread("Writing-1");
	write1->Fork((VoidFunctionPtr)Write1, (char*)fileName1);
	Thread* write2 = new Thread("Writing-2");
	write2->Fork((VoidFunctionPtr)Write1, (char*)fileName1);


	Thread* read1 = new Thread("Reading-1");
	read1->Fork((VoidFunctionPtr)ReadFile, (char*)fileName1);
	Thread* read2 = new Thread("Reading-2");
	read2->Fork((VoidFunctionPtr)ReadFile, (char*)fileName1);
	Thread* read3 = new Thread("Reading-3");
	read3->Fork((VoidFunctionPtr)ReadFile, (char*)fileName1);

	Thread *delte3 = new Thread("delete");
	delte3->Fork((VoidFunctionPtr)deletefile, (void*) 1);


	Thread* write3 = new Thread("Writing-3");
	write3->Fork((VoidFunctionPtr)Write1, (char*)fileName2);

	Thread* read4 = new Thread("Reading-4");
	read4->Fork((VoidFunctionPtr)ReadFile, (char*)fileName2);



	Thread *tapp = new Thread("File Extension  ");
	tapp->Fork((VoidFunctionPtr)FileExtention, (void*)1);

	Thread* tdir = new Thread("File Extension  ");
	tdir->Fork((VoidFunctionPtr)createMutliple, (void*)1);
}
