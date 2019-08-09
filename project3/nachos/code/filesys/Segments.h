#ifndef NACHOS_CODE_FILESYS_SEGMENTS_H_
#define NACHOS_CODE_FILESYS_SEGMENTS_H_
#include "filehdr.h"
#include "fileBlock.h"
class Segments {
public:
	Segments();
	~Segments();
	int counter = 0;
	char* data;
	void WriteToDisk();
	void ReadFromDisk();
	void WriteSector(char * buff);
	void WriteSector(int sector, char * buff);
	void ReadSector(int sector, char* into);
	int getCounter();
	void MapDirectory();
};

#endif /* NACHOS_CODE_FILESYS_SEGMENTS_H_ */
