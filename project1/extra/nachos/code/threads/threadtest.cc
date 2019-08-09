#include "kernel.h"
#include "main.h"
#include "thread.h"


void
fnRead1(int which)
{
	
	string str;
	int delay=rand()%50+200;
	std::cout<<"Thread :"<<kernel->currentThread->getName()<<"  Read Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
	IORequest *read= new IORequest(&str,kernel->currentThread,delay,0);
	delete read;
	std::cout<<"----------------------------------------------------------------"<<endl;
	std::cout<<"Thread id:  "<<kernel->currentThread->getName()<<"---Return read string :"<<str<<"at :"<<kernel->stats->totalTicks<<endl;
	std::cout<<"----------------------------------------------------------------"<<endl;
	
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;
}
void 
fnWrite1(int which)
{
	string str=" ((Writing to screen))  ";
	int delay = rand()%30+100;
	std::cout<<"Thread :  "<<kernel->currentThread->getName()<<" will execute at :"<<delay+kernel->stats->totalTicks<<endl;
	IORequest *write= new IORequest(&str,kernel->currentThread,delay,1);
	delete write;
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;
}
void 
fnCPU1(int which)
{
	for(int m=0;m<1000;m++)
	{
		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		(void) kernel->interrupt->SetLevel(oldLevel);
		//std::cout<<"Thread "<<which<<"at ready Queue "<<kernel->currentThread->getOld()<< "running at "<<kernel->stats->totalTicks<<endl;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;
}
void 
fnReadIntensive(int which)
{
	for(int i=0;i<10;i++)
	{
		string str;
		int delay=rand()%50+200;
		std::cout<<"Thread :"<<kernel->currentThread->getName()<<"  Read Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *read= new IORequest(&str,kernel->currentThread,delay,0);
		std::cout<<"----------------------------------------------------------------"<<endl;
		std::cout<<"Thread id:  "<<kernel->currentThread->getName()<<"---Return read string :"<<str<<"at :"<<kernel->stats->totalTicks<<endl;
		std::cout<<"----------------------------------------------------------------"<<endl;
		delete read;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;
}
void
fnWriteIntensive(int which)
{
	for(int i=0;i<10;i++)
	{
		string str=" ((Writing to screen))  ";
		int delay = rand()%30+100;
		std::cout<<"Thread :  "<<kernel->currentThread->getName()<<"  Write Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *write= new IORequest(&str,kernel->currentThread,delay,1);
		delete write;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;
	
}
void 
fnIOIntensive(int which)
{
	for(int i=0;i<10;i++)
	{
		string str;
		int delay=rand()%50+200;
		std::cout<<"Thread :"<<kernel->currentThread->getName()<<"  Read Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *read= new IORequest(&str,kernel->currentThread,delay,0);
		std::cout<<"----------------------------------------------------------------"<<endl;
		std::cout<<"Thread id:  "<<kernel->currentThread->getName()<<"----Return read string :"<<str<<"at :"<<kernel->stats->totalTicks<<endl;
		std::cout<<"----------------------------------------------------------------"<<endl;
		delete read;
	}
	for(int i=0;i<10;i++)
	{
		string str=" ((Writing to screen))  ";
		int delay =rand()%30+100;
		std::cout<<"Thread :  "<<kernel->currentThread->getName()<<"  Write Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *write= new IORequest(&str,kernel->currentThread,delay,1);
		delete write;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :   "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;
}
void 
fnCPUReadIntensive( int which)
{
	for(int m=0;m<500;m++)
	{
		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		(void) kernel->interrupt->SetLevel(oldLevel);
		//std::cout<<"Thread "<<which<<"at ready Queue "<<kernel->currentThread->getOld()<< "running at "<<kernel->stats->totalTicks<<endl;
	}
	for(int i=0;i<10;i++)
	{
		string str;
		int delay=rand()%50+200;
		std::cout<<"Thread :"<<kernel->currentThread->getName()<<"  Read Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *read= new IORequest(&str,kernel->currentThread,delay,0);
		std::cout<<"----------------------------------------------------------------"<<endl;
		std::cout<<"Thread id:  "<<kernel->currentThread->getName()<<"---Return read string :"<<str<<"at :"<<kernel->stats->totalTicks<<endl;
		std::cout<<"----------------------------------------------------------------"<<endl;
		delete read;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;	
}
void 
fnCPUWriteIntensive(int which)
{
	for(int m=0;m<500;m++)
	{
		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		(void) kernel->interrupt->SetLevel(oldLevel);
		//std::cout<<"Thread "<<which<<"at ready Queue "<<kernel->currentThread->getOld()<< "running at "<<kernel->stats->totalTicks<<endl;
	}
	for(int i=0;i<10;i++)
	{
		string str=" ((Writing to screen))  ";
		int delay = rand()%30+100;
		std::cout<<"Thread :  "<<kernel->currentThread->getName()<<"   Write Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *write= new IORequest(&str,kernel->currentThread,delay,1);
		delete write;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;	
}
void 
fnIOCPUIntensive(int which)
{
	for(int i=0;i<5;i++)
	{
		string str;
		int delay=rand()%50+200;
		std::cout<<"Thread :"<<kernel->currentThread->getName()<<"  Read Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *read= new IORequest(&str,kernel->currentThread,delay,0);
		std::cout<<"----------------------------------------------------------------"<<endl;
		std::cout<<"Thread id:  "<<kernel->currentThread->getName()<<"----Return read string :"<<str<<"at :"<<kernel->stats->totalTicks<<endl;
		std::cout<<"----------------------------------------------------------------"<<endl;
		delete read;
	}
	for(int i=0;i<5;i++)
	{
		string str=" ((Writing to screen))  ";
		int delay = rand()%30+100;
		std::cout<<"Thread :  "<<kernel->currentThread->getName()<<" Write Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *write= new IORequest(&str,kernel->currentThread,delay,1);
		delete write;
	}
	for(int m=0;m<800;m++)
	{
		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		(void) kernel->interrupt->SetLevel(oldLevel);
		//std::cout<<"Thread "<<which<<"at ready Queue "<<kernel->currentThread->getOld()<< "running at "<<kernel->stats->totalTicks<<endl;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;	
}
void 
fnIOCPUIntensive2(int which)
{
	for(int i=0;i<10;i++)
	{
		string str;
		int delay=rand()%50+200;
		std::cout<<"Thread :"<<kernel->currentThread->getName()<<" Read Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *read= new IORequest(&str,kernel->currentThread,delay,0);
		std::cout<<"----------------------------------------------------------------"<<endl;
		std::cout<<"Thread id:  "<<kernel->currentThread->getName()<<"----Return read string :"<<str<<"at :"<<kernel->stats->totalTicks<<endl;
		std::cout<<"----------------------------------------------------------------"<<endl;
		delete read;
	}
	for(int m=0;m<300;m++)
	{
		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		(void) kernel->interrupt->SetLevel(oldLevel);
		//std::cout<<"Thread "<<which<<"at ready Queue "<<kernel->currentThread->getOld()<< "running at "<<kernel->stats->totalTicks<<endl;
	}
	for(int i=0;i<10;i++)
	{
		string str=" ((Writing to screen))  ";
		int delay = rand()%30+100;
		std::cout<<"Thread :  "<<kernel->currentThread->getName()<<"   Write Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *write= new IORequest(&str,kernel->currentThread,delay,1);
		delete write;
	}
	
	
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;	
}
void 
fnWriteReadCPUIntensive(int which )
{
	for(int i=0;i<10;i++)
	{
		string str=" ((Writing to screen))  ";
		int delay = rand()%30+100;
		std::cout<<"Thread :  "<<kernel->currentThread->getName()<<"   Write Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *write= new IORequest(&str,kernel->currentThread,delay,1);
		delete write;
	}
	for(int i=0;i<10;i++)
	{
		string str;
		int delay=rand()%50+200;
		std::cout<<"Thread :"<<kernel->currentThread->getName()<<" Read Interrupt will execute at :"<<delay+kernel->stats->totalTicks<<endl;
		IORequest *read= new IORequest(&str,kernel->currentThread,delay,0);
		std::cout<<"----------------------------------------------------------------"<<endl;
		std::cout<<"Thread id:  "<<kernel->currentThread->getName()<<"----Return read string :"<<str<<"at :"<<kernel->stats->totalTicks<<endl;
		std::cout<<"----------------------------------------------------------------"<<endl;
		delete read;
	}
	for(int m=0;m<300;m++)
	{
		IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
		(void) kernel->interrupt->SetLevel(oldLevel);
		//std::cout<<"Thread "<<which<<"at ready Queue "<<kernel->currentThread->getOld()<< "running at "<<kernel->stats->totalTicks<<endl;
	}
	std::cout<<"==========================================================================================="<<endl;
	std::cout<<"Exiting Thread :  "<<kernel->currentThread->getName()<<"at "<< kernel->stats->totalTicks<<endl;
	std::cout<<"==========================================================================================="<<endl;	
	
}

void
ThreadTest()
{
	std::cout<<"******************************************************************************************"<<endl;
	std::cout<<"Quantum for Ready Queue with Priority 1:  "<<kernel->quantum1<<endl;
	std::cout<<"Quantum for Ready Queue with Priority 2:  "<<kernel->quantum2<<endl;
	std::cout<<"Quantum for Ready Queue with Priority 3:  "<<kernel->quantum3<<endl;
	std::cout<<"Quantum for Ready Queue with Priority 4:  "<<kernel->quantum4<<endl;
	std::cout<<"******************************************************************************************"<<endl;
	Thread *t3 = new Thread("CPU bound");
    t3->Fork((VoidFunctionPtr) fnCPU1, (void *) 3);
	Thread *t = new Thread("Read Thread");
    t->Fork((VoidFunctionPtr) fnRead1, (void *) 1);
	Thread *t1 = new Thread("Write Thread");
    t1->Fork((VoidFunctionPtr) fnWrite1, (void *) 2);
	Thread *t9 = new Thread("IO-CPU-Intensive");
    t9->Fork((VoidFunctionPtr) fnIOCPUIntensive, (void *) 9);
	Thread *t11 = new Thread("Write-Read-CPU");
    t11->Fork((VoidFunctionPtr) fnWriteReadCPUIntensive, (void *) 11);
	Thread *t4 = new Thread("Read Intensive");
    t4->Fork((VoidFunctionPtr)fnReadIntensive, (void *) 4);
	Thread *t5 = new Thread("Write Intensive");
    t5->Fork((VoidFunctionPtr) fnWriteIntensive, (void *) 5);
	Thread *t6 = new Thread("IO Intensive");
    t6->Fork((VoidFunctionPtr) fnIOIntensive, (void *) 6);
	Thread *t10 = new Thread("CPU-IO-Intensive");
    t10->Fork((VoidFunctionPtr) fnIOCPUIntensive2, (void *) 10);
	Thread *t7 = new Thread("CPU-Read-Intensive");
    t7->Fork((VoidFunctionPtr) fnCPUReadIntensive, (void *) 7);
	Thread *t8 = new Thread("CPU-Write-Intensive");
    t8->Fork((VoidFunctionPtr) fnCPUWriteIntensive, (void *) 8);
	
}
