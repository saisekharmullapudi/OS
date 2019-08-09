
#include "main.h"
#include "list.h"
IOHandler :: IOHandler()
{

}
IOHandler :: ~IOHandler()
{
	
}
void 
IOHandler :: CallBack()
{
	if(kernel->todo->NumInList()==0)
	{
		return;
	}
	ListIterator<IORequest*> *iter = new ListIterator<IORequest*>(kernel->todo);
	while( !iter->IsDone()) {
		IORequest* temp= iter->Item();
		iter->Next();
		if(temp->getRespondTime()<=kernel->stats->totalTicks)
		{
			if(temp->getType()==0)
			{
				std::cout<<"Doing IO Read Handling for thread "<<temp->getThread()->getName()<<"--- at :"<<kernel->stats->totalTicks<<endl;
				temp->Read();
			}
			else if(temp->getType()==1)
			{
				std::cout<<"Doing IO Write handling for thread"<<temp->getThread()->getName()<<"--- at :"<<kernel->stats->totalTicks<<endl;
				temp->Write();
			}
			kernel->todo->Remove(temp);
		}
		//std::cout<<"Todo Elements:  "<<kernel->todo->NumInList()<<endl;
	}
	
	delete iter;
	
}
bool IOHandler::operator==(IOHandler* other)
{
	return false;
}