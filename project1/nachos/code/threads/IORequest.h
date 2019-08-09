#include "list.h"
#include "thread.h"
#include<string> 
#include "IOHandler.h"

class IORequest
{
	private:
	int type;
	Thread* id;
	string* str;
	int delay_time;
	int raise_request_time;
	int status;
	string read_from="   ((Reading from file))  ";
	string write_to;
	IOHandler *handler;
	
	public:
	IORequest(string* s, Thread* id, int time, int ty);
	~IORequest();
	int getType();
	Thread* getThread();
	void Read();
	void Write();
	int getRespondTime();
};