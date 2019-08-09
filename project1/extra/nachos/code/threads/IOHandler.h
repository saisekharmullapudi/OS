#include "callback.h"
class IOHandler :  public CallBackObj
{
	private:
	int type;
	
	public:
	IOHandler();
	~IOHandler();
	void CallBack();
	bool operator==(IOHandler* other);
};