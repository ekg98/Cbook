// Header to hold structure information for ex7-7

struct fileStructure
{
	FILE *filePointer;
	char *fileName;
	struct fileStructure *next;
};
