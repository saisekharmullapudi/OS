#include "main.h"
#include "kernel.h"
#include<string> 
IORequest::IORequest(string* s, Thread* i, int time, int ty)
{
	IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
	type=ty;
	id=i;
	str=s;
	delay_time=time;
	raise_request_time=(kernel->stats->totalTicks)+delay_time;
	
	handler = new IOHandler();
	if(ty==0)
	{
		kernel->interrupt->Schedule(handler,time,IORead);
	}
	else if(ty==1)
	{
		kernel->interrupt->Schedule(handler,time,IOWrite);
	}
	kernel->todo->Insert(this);
	id->setLastExecuted__time(kernel->stats->totalTicks);
	id->Sleep(false);
	(void) kernel->interrupt->SetLevel(oldLevel);
}
IORequest::~IORequest()
{
	delete handler;
	
}
void  
IORequest:: Read()
{
	*str=read_from;
	IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
	id->increasePriority();
	id->increasePriority();
	kernel->scheduler->ReadyToRun(id);
	(void) kernel->interrupt->SetLevel(oldLevel);
}
int
IORequest :: getType()
{
	return type;
}
void
IORequest:: Write()
{
	write_to=*str;
	std::cout<<"----------------------------------------------------------------"<<endl;
	std::cout<<"Displaying string: "<<write_to<<"from "<<id->getName()<<endl;
	std::cout<<"----------------------------------------------------------------"<<endl;
	IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
	id->increasePriority();
	id->increasePriority();
	kernel->scheduler->ReadyToRun(id);
	(void) kernel->interrupt->SetLevel(oldLevel);
}
int IORequest::getRespondTime()
{
	return raise_request_time;
}
Thread*
IORequest:: getThread()
{
	return id;
}