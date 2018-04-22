#include <stdint.h>
const int maxRecordStringLength = 25;
class BinaryHeader
{
	public:
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint64_t numRecords;
};
class BinaryFileRecord
{
	public:
	uint8_t strLength;
	char stringBuffer[maxRecordStringLength];
};
