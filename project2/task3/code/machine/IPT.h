
class IPTEntry {
  public:
    int virtualPage; 
    int physicalPage;  
    bool valid;        
    bool readOnly;  
    bool use;        
    bool dirty;
    int Thread_id;

    
     IPTEntry(int p,int q, int r);
     ~IPTEntry();
     // void Pri();
     
};
