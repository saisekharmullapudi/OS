#include "IPT.h"
#include "stdio.h"
using namespace std;
 IPTEntry:: IPTEntry(int p,int q, int r)
 {
 	virtualPage=p; 
    physicalPage=q;  
    valid=false;        
    readOnly=false;  
    use=false;        
    dirty= false;
 	Thread_id=r;
 }
 IPTEntry:: ~IPTEntry()
 {
 }
 