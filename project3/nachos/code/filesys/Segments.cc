#include "Segments.h"
#include "main.h"
#include "synchdisk.h"
#include "directory.h"
#include "filesys.h"

void Workingbcopy(char* from, char* to, int size) {
	for (int i = 0, j = 0; i < size; i++, j++) {
		to[i] = from[j];
	}
}

Segments::Segments() {

	data = new char[NumSectors * SectorSize];
	for (int i = 0; i < NumSectors * SectorSize; i++) {
		data[i] = '.';
	}
	counter = 7;
}

void Segments::MapDirectory() {
	FileHeader* directoryFileHeader = new FileHeader();
	DoublyIndirectBlock* dblock = new DoublyIndirectBlock();
	IndirectBlock* iblock = new IndirectBlock();
	iblock->dataSectors[0] = 3;
	iblock->dataSectors[1] = 4;
	iblock->dataSectors[1] = 5;
	Workingbcopy((char*) iblock, &data[2 * SectorSize], SectorSize);
	dblock->dataSectors[0] = 2;
	Workingbcopy((char*) dblock, data + (1 * SectorSize), SectorSize);
	directoryFileHeader->dataSectors[0] = 1;
	directoryFileHeader->numBytes = 2 * SectorSize;
	Workingbcopy((char*) directoryFileHeader, &data[0], SectorSize);
}
void Segments::WriteToDisk() {
	char* c = (char*) &counter;
	Workingbcopy(c, &data[6 * SectorSize], sizeof(int));

	int i = 0;
	for (i = 0; i < NumSectors; i++) {
		kernel->synchDisk->WriteSector(i, (char*) (data + i * SectorSize));
	}
	std::cout << "Writing to Disk from Segments " << endl;
	delete kernel;
}

void Segments::ReadFromDisk() {

	for (int i = 0; i < NumSectors; i++) {
		kernel->synchDisk->ReadSector(i, (char*) (data + i * SectorSize));
	}
	char* a = new char();
	Workingbcopy(&data[6 * SectorSize], a, sizeof(int));
	counter = *((int*)a);
	std::cout << "Reading from Disk to Segments ::" << endl;
}

void Segments::WriteSector(char * buff) {
	if (counter >= NumSectors) {
		WriteToDisk();
		std::cout << "Segments has been fileed OS." << endl;

	}
	Workingbcopy(buff, &data[counter * SectorSize], SectorSize);
	counter++;
}

void Segments::WriteSector(int sector, char * buff) {
	if (sector > NumSectors) {
		WriteToDisk();
		std::cout << "Wrting change cannot happen." << endl;
	}
	Workingbcopy(buff, &data[sector * SectorSize], SectorSize);
}

void Segments::ReadSector(int sector, char* into) {
	Workingbcopy(&data[sector * SectorSize], into, SectorSize);
}

int Segments::getCounter() {
	if (counter >= NumSectors) {
		cout << "Segment has been filled. Write to Disk is being called." << endl;
		WriteToDisk();

	}
	return counter++;
}
Segments::~Segments() {
	// TODO Auto-generated destructor stub
}
