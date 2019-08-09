// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	is in machine.h.
//----------------------------------------------------------------------
void
Forked(int num)
{
    std::cout<<"___________________Forked Thread execution_____________________"<<endl;
    // ThreadExit(0);
}

void
ExceptionHandler(ExceptionType which)
{
    int type = kernel->machine->ReadRegister(2);

    DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

    switch (which) {
    case SyscallException:
      switch(type) {
      case SC_Halt:
	  //std::cout<<"inside halt sys call"<<endl;
	DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

	SysHalt();

	ASSERTNOTREACHED();
	break;

      case SC_Add:
	  //std::cout<<"inside add sys call"<<endl;
	DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
	
	/* Process SysAdd Systemcall*/
	int result;
	result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
			/* int op2 */(int)kernel->machine->ReadRegister(5));
	// std::cout<<"result from "<<kernel->currentThread->id<<" is "<<result<<endl;
	//kernel->scheduler->Print();
	DEBUG(dbgSys, "Add returning with " << result << "\n");
	/* Prepare Result */
	kernel->machine->WriteRegister(2, (int)result);
	{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}
	/* Modify return point */
	break;
	case SC_Read:
	{
		int reg4=(int)kernel->machine->ReadRegister(4);
		int reg5=(int)kernel->machine->ReadRegister(5);
		char* c=" reading";
		std::cout<<"                               Console Read from "<<kernel->currentThread->id<<endl;
		int i=0;
		while(i<reg5)
		{
			if(kernel->machine->WriteMem(reg4,1,(int)(*c)))
			{
				reg4=reg4+1;
			}
			i++;
			c++;
		}
		{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}
		break;
	}
	case SC_Exit:
	{
		std::cout<<"-----------------------------------------------------------------------------------"<<endl;
		std::cout<<"                               Exiting the current thread : "<< kernel->currentThread->id<<"   "<<kernel->machine->ReadRegister(4)<<endl;
		std::cout<<"-----------------------------------------------------------------------------------"<<endl;
		kernel->currentThread->Finish();
		// kernel->machine->track->Print();
		break;
	}
	case SC_ThreadFork:
	{
		// std::cout<<"inside ThreadFork"<<endl;
		int reg4=kernel->machine->ReadRegister(4);
		Thread* t = new Thread("Fork ");
		t->Fork((VoidFunctionPtr)Forked,0);
		kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
		kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
		kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
		//std::cout<<"\n"<<kernel->currentThread->getName()<<endl;
		// kernel->scheduler->Print();
		//kernel->currentThread->StackAllocate((VoidFunctionPtr)reg4,0);
		
		//kernel->scheduler->Print();
		break;
	}
	case SC_ThreadYield:
	{
		std::cout<<"                               Thread yeild:: "<< kernel->currentThread->id<<endl;
		
		kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
		kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
		kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
		kernel->currentThread->Yield();
	
		break;
	}
	case SC_ThreadExit:
	{
		std::cout<<"-----------------------------------------------------------------------------------"<<endl;
		std::cout<<"exiting the current thread : "<< kernel->currentThread->id<<endl;
		std::cout<<"-----------------------------------------------------------------------------------"<<endl;
		//kernel->scheduler->Print();
		kernel->currentThread->Finish();
		// kernel->machine->track->Print();

		break;
	}
	case SC_Write:
	{
	std::cout<<"                               Console Write System Call from "<<kernel->currentThread->id<<endl;
	int reg4=(int)kernel->machine->ReadRegister(4);
	int reg5=(int)kernel->machine->ReadRegister(5);
	int i=0;
	while(i<reg5)
	{
		int c;
		if(kernel->machine->ReadMem(reg4, 1, &c))
		{
			printf("%c",c);
		}
		i++;
		reg4=reg4+1;
	}
	std::cout<<endl;
	{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}
	break;
	}
	
	ASSERTNOTREACHED();

	break;

      default:
	cerr << "Unexpected system call " << type << "\n";
	std::cout<<"-----------------------------------------------------------------------------------"<<endl;
	std::cout<<"exiting the current thread : "<< kernel->currentThread->id<<endl;
	std::cout<<"-----------------------------------------------------------------------------------"<<endl;
	kernel->currentThread->Finish();
	// kernel->machine->track->Print();
	break;
      }
      break;
      case PageFaultException:
      {
      	std::cout<<"                               Page Fault Exception raised from  "<<kernel->currentThread->id<<endl;
      	int out=kernel->machine->track->FindAndSet();
      	if(out!=-1)
      	{
      		IPTEntry* p = kernel->machine->ipt.at(out);
      		int addr=kernel->machine->ReadRegister(BadVAddrReg);
        	unsigned int vpn1= (unsigned) addr / PageSize;
        	char* data1= new char[PageSize];
        	int nt=kernel->currentThread->id;
        	int nt_pos= kernel->loc[nt];
        	kernel->swapFile->ReadAt(&data1[0], PageSize,nt_pos+vpn1*PageSize);
        	int b=0;
        	for(int j=out*PageSize;j<((out*PageSize)+PageSize);j++)
        	{
        		kernel->machine->mainMemory[j]=data1[b];
        		b++;
        	}
        	p->virtualPage=vpn1;
        	p->physicalPage=out;
        	p->valid=true;
        	p->use=false;
        	p->dirty= false;
        	p->readOnly=false;
        	p->Thread_id=kernel->currentThread->id;
      	}
      	else
      	{
      		out= rand()%70+10;
      	kernel->machine->track->Clear(out);
      	IPTEntry* p = kernel->machine->ipt.at(out);
      	int t=p->Thread_id;
      	int file_pos= kernel->loc[t];
      	char* data= new char[PageSize];
      	int main_pos=out*PageSize;
      	int vpn=p->virtualPage;
      	for(int j=0;j<PageSize;j++)
        {
            // kernel->machine->mainMemory[j]=cod[b];
            data[j]=kernel->machine->mainMemory[main_pos];
            main_pos++;
        }
        kernel->swapFile->WriteAt(data, PageSize, file_pos+vpn*PageSize);
        delete data;
        // std::cout<<kernel->swapFile->Length()<<endl;
        int addr=kernel->machine->ReadRegister(BadVAddrReg);
        unsigned int vpn1= (unsigned) addr / PageSize;
        char* data1= new char[PageSize];
        int nt=kernel->currentThread->id;
        int nt_pos= kernel->loc[nt];
        kernel->swapFile->ReadAt(&data1[0], PageSize,nt_pos+vpn1*PageSize);
        int b=0;
        for(int j=out*PageSize;j<((out*PageSize)+PageSize);j++)
        {
        	kernel->machine->mainMemory[j]=data1[b];
        	b++;
        }
        p->virtualPage=vpn1;
        p->physicalPage=out;
        p->valid=true;
        p->use=false;
        p->dirty= false;
        p->readOnly=false;
        p->Thread_id=kernel->currentThread->id;
        kernel->machine->track->Mark(out);
    	}
        // kernel->machine->fifo->push(out);
    	
       	break;
      }
    default:
      cerr << "Unexpected user mode exception" << (int)which << "\n";
      exit(0);
      break;
    }
	
	return;
    ASSERTNOTREACHED();
}
