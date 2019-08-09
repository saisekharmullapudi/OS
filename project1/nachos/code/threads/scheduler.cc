// scheduler.cc 
//	Routines to choose the next thread to run, and to dispatch to
//	that thread.
//
// 	These routines assume that interrupts are already disabled.
//	If interrupts are disabled, we can assume mutual exclusion
//	(since we are on a uniprocessor).
//
// 	NOTE: We can't use Locks to provide mutual exclusion here, since
// 	if we needed to wait for a lock, and the lock was busy, we would 
//	end up calling FindNextToRun(), and that would put us in an 
//	infinite loop.
//
// 	Very simple implementation -- no priorities, straight FIFO.
//	Might need to be improved in later assignments.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "debug.h"
#include "scheduler.h"
#include "main.h"

//----------------------------------------------------------------------
// Scheduler::Scheduler
// 	Initialize the list of ready but not running threads.
//	Initially, no ready threads.
//----------------------------------------------------------------------

Scheduler::Scheduler()
{ 
    readyList = new List<Thread *>;
	readyList2 = new List<Thread *>;
	readyList3 = new List<Thread *>;
	readyList4 = new List<Thread *>;
    toBeDestroyed = NULL;
} 

//----------------------------------------------------------------------
// Scheduler::~Scheduler
// 	De-allocate the list of ready threads.
//----------------------------------------------------------------------

Scheduler::~Scheduler()
{ 
    delete readyList;
	delete readyList2;
	delete readyList3;
	delete readyList4;
}  


//----------------------------------------------------------------------
// Scheduler::ReadyToRun
// 	Mark a thread as ready, but not running.
//	Put it on the ready list, for later scheduling onto the CPU.
//
//	"thread" is the thread to be put on the ready list.
//----------------------------------------------------------------------

void
Scheduler::ReadyToRun (Thread *thread)
{
    ASSERT(kernel->interrupt->getLevel() == IntOff);
    DEBUG(dbgThread, "Putting thread on ready list: " << thread->getName());

    thread->setStatus(READY);
	int lev= thread->getLeve();
	if(lev==1)
	{
		readyList->Append(thread);
	}
	else if( lev==2)
	{
		readyList2->Append(thread);
	}
	else if(lev==3)
	{
		readyList3->Append(thread);
	}
	else if(lev==4)
	{
		readyList4->Append(thread);
	}
}

//----------------------------------------------------------------------
// Scheduler::FindNextToRun
// 	Return the next thread to be scheduled onto the CPU.
//	If there are no ready threads, return NULL.
// Side effect:
//	Thread is removed from the ready list.
//----------------------------------------------------------------------

Thread *
Scheduler::FindNextToRun ()
{
	check_aging();
    ASSERT(kernel->interrupt->getLevel() == IntOff);
	Thread *t;
    if (readyList->IsEmpty()) {
		if(readyList2->IsEmpty())
		{
			if(readyList3->IsEmpty())
			{
				if(readyList4->IsEmpty())
				{
					return NULL;
				}
				else
				{
					t= readyList4->RemoveFront();
				}
			}
			else
			{
				t= readyList3->RemoveFront();
			}
			
		}
		else{
			t= readyList2->RemoveFront();
		}
    } else {
    	t= readyList->RemoveFront();
    }
	t->decreasePriority();
	return t;
}

//----------------------------------------------------------------------
// Scheduler::Run
// 	Dispatch the CPU to nextThread.  Save the state of the old thread,
//	and load the state of the new thread, by calling the machine
//	dependent context switch routine, SWITCH.
//
//      Note: we assume the state of the previously running thread has
//	already been changed from running to blocked or ready (depending).
// Side effect:
//	The global variable kernel->currentThread becomes nextThread.
//
//	"nextThread" is the thread to be put into the CPU.
//	"finishing" is set if the current thread is to be deleted
//		once we're no longer running on its stack
//		(when the next thread starts running)
//----------------------------------------------------------------------

void
Scheduler::Run (Thread *nextThread, bool finishing)
{
    Thread *oldThread = kernel->currentThread;
    //std::cout<<"Thread :  "<<oldThread->getName()<<"  gettin context switch  at "<<kernel->stats->totalTicks<<endl;
    ASSERT(kernel->interrupt->getLevel() == IntOff);

    if (finishing) {	// mark that we need to delete current thread
         ASSERT(toBeDestroyed == NULL);
	 toBeDestroyed = oldThread;
    }
    
    if (oldThread->space != NULL) {	// if this thread is a user program,
        oldThread->SaveUserState(); 	// save the user's CPU registers
	oldThread->space->SaveState();
    }
    
    oldThread->CheckOverflow();		    // check if the old thread
					    // had an undetected stack overflow

    kernel->currentThread = nextThread;  // switch to the next thread
	int level=-1;
	level=kernel->currentThread->getOld();
	int t=0;
	if(level==1)
	{
		t=kernel->quantum1;
	}
	else if(level==2)
	{
		t=kernel->quantum2;
	}
	else if(level==3)
	{
		t=kernel->quantum3;
	}
	else if(level==4)
	{
		t=kernel->quantum4;
	}
	else{
		t=0;
	}
	kernel->interrupt->changeInterrupt(t);
    nextThread->setStatus(RUNNING);      // nextThread is now running
	int time= kernel->currentThread->getOld();
    //kernel->interrupt->Schedule(this,time,Schdeuler);
	std::cout<<"Thread : "<<kernel->currentThread->getName()<<"   having priority "<<kernel->currentThread->getOld()<< " running at "<<kernel->stats->totalTicks<<endl;
    DEBUG(dbgThread, "Switching from: " << oldThread->getName() << " to: " << nextThread->getName());
    
    // This is a machine-dependent assembly language routine defined 
    // in switch.s.  You may have to think
    // a bit to figure out what happens after this, both from the point
    // of view of the thread and from the perspective of the "outside world".

    SWITCH(oldThread, nextThread);

    // we're back, running oldThread
      
    // interrupts are off when we return from switch!
    ASSERT(kernel->interrupt->getLevel() == IntOff);

    DEBUG(dbgThread, "Now in thread: " << oldThread->getName());

    CheckToBeDestroyed();		// check if thread we were running
					// before this one has finished
					// and needs to be cleaned up
    
    if (oldThread->space != NULL) {	    // if there is an address space
        oldThread->RestoreUserState();     // to restore, do it.
	oldThread->space->RestoreState();
    }
}

//----------------------------------------------------------------------
// Scheduler::CheckToBeDestroyed
// 	If the old thread gave up the processor because it was finishing,
// 	we need to delete its carcass.  Note we cannot delete the thread
// 	before now (for example, in Thread::Finish()), because up to this
// 	point, we were still running on the old thread's stack!
//----------------------------------------------------------------------

void
Scheduler::CheckToBeDestroyed()
{
    if (toBeDestroyed != NULL) {
        delete toBeDestroyed;
	toBeDestroyed = NULL;
    }
}
 
//----------------------------------------------------------------------
// Scheduler::Print
// 	Print the scheduler state -- in other words, the contents of
//	the ready list.  For debugging.
//----------------------------------------------------------------------
void
Scheduler::Print()
{
    cout << "*******Ready list contents:********\n";
    readyList->Apply(ThreadPrint);
	cout<<endl;
	cout << "====Ready list 2 contents:=====\n";
	readyList2->Apply(ThreadPrint);
	cout<<endl;
	cout << "++++++Ready list 3contents:+++++\n";
	readyList3->Apply(ThreadPrint);
	cout<<endl;
	cout << "#####Ready list 4 contents:#####\n";
	readyList4->Apply(ThreadPrint);
	cout<<endl;
}
List<Thread *> 
Scheduler::getlevelOne()
{
	return *readyList;
}
List<Thread *> 
Scheduler::getlevelTwo()
{
	return *readyList2;
}
List<Thread *> 
Scheduler::getlevelThree()
{
	return *readyList3;
}
List<Thread *> 
Scheduler::getlevelFour()
{
	return *readyList4;
}

//void 
//Scheduler::CallBack()
//{
//	kernel->currentThread->Yield();
//}
void 
Scheduler::check_aging()
{
	ListIterator<Thread *> *iter = new ListIterator<Thread *>(readyList3);
	while( !iter->IsDone()) {
		Thread* temp= iter->Item();
		iter->Next();
		if((kernel->stats->totalTicks)-(temp->getLastExecuted__time())>= kernel->aging_time)
		{
			readyList3->Remove(temp);
			temp->increasePriority();
			temp->increasePriority();
			kernel->scheduler->ReadyToRun(temp);
			std::cout<<"**************************************************************************"<<endl;
			std::cout<<"**************************************************************************"<<endl;
			std::cout<<"Thread :  "<< temp->getName()<< "is getting aged to increased its priority "<<endl;
			std::cout<<"**************************************************************************"<<endl;
		}
	}
	ListIterator<Thread *> *iter1 = new ListIterator<Thread *>(readyList4);
	while( !iter1->IsDone()) {
		Thread* temp= iter1->Item();
		iter1->Next();
		if((kernel->stats->totalTicks)-(temp->getLastExecuted__time())>= kernel->aging_time)
		{
			readyList4->Remove(temp);
			temp->increasePriority();
			temp->increasePriority();
			kernel->scheduler->ReadyToRun(temp);
			std::cout<<"**************************************************************************"<<endl;
			std::cout<<"**************************************************************************"<<endl;
			std::cout<<"Thread :  "<< temp->getName()<< "is getting aged to increased its priority "<<endl;
			std::cout<<"**************************************************************************"<<endl;
		}
	}
	delete iter;
	delete iter1;
}