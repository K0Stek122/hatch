#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minLen = 0;
int maxLen = 0;
char ch[512];
char out[1024];
char sp[64];
char ep[64];
FILE* outputFile;

int getEndIndex(char arr[])
{
	for (int i = 0; i < sizeof(arr); i++)
	{
		if (arr[i] == 0)
			return i;
	}
}

void printArray(char arr[])
{
	for (int i = 0; i < getEndIndex(arr); i++)
	{
		printf("%c", arr[i]);
	}
	printf("\n");
}


int compare(const void* a, const void* b)
{
	return (*(char*)a - *(char*)b);
}

void generateRecur(char* str, char* data, int last, int index)
{

	int i, len = strlen(str);
	for (i = 0; i < len; i++)
	{
		data[index] = str[i];
		if (index == last)
		{
			if (outputFile != NULL)
			{
				fprintf(outputFile, sp);
				fprintf(outputFile, data);
				fprintf(outputFile, ep);
				fprintf(outputFile, "\n");
			}
			else
			{
				printf("%s%s%s\n", sp, data, ep);
			}
		}
		else
			generateRecur(str, data, last, index + 1);
	}
}


void generatePermutations(char* str, int len)
{

	char* dataPtr = (char*)malloc(sizeof(char) * (len+1));
	dataPtr[len+1] = '\0';
//	void qsort (void* base, size_t num, size_t size,
//            int (*compar)(const void*,const void*));
	qsort(str, len, sizeof(char), compare);
	generateRecur(str, dataPtr, len - 1, 0);

	free(dataPtr);
}

int main(int argc, char* argv[])
{
	memset(ch, 0, sizeof(ch)); //Emptying the char arrays
	memset(sp, 0, sizeof(sp)); 
	memset(ep, 0, sizeof(ep));
	memset(out, 0, sizeof(out));


	if (argc < 2)
	{
		printf("Wrong amount of arguments\n");
		return -1;
	}
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
	{
		printf("usage: hatch [OPTIONS]\n");
		printf("	-mil <- minimum length of the permutations (REQUIRED)\n");
		printf("	-mal <- Maximum length of the password\n");
		printf("	-c <- characters to use in the permutations, if not specified then basic alphabet is used\n");
		printf("	-sp <- What the string starts with\n");
		printf("	-ep <- What the string ends with\n");
		printf("	-o <- Whether to output to a file\n");
		return -1;
	}



	for (short int i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i+1][0] == '-')
			{
				printf("Incorrect usage!\n");
				return -1;
			}

			if (strcmp(argv[i], "-mil") == 0)
			{
				char temp[16];
				strcpy(temp, argv[i+1]);
				minLen = atoi(temp);
			}
			else if (strcmp(argv[i], "-mal") == 0)
			{
				char temp[16];
				strcpy(temp, argv[i+1]);
				maxLen = atoi(temp);
			}
			else if (strcmp(argv[i], "-c") == 0)
			{
				strcpy(ch, argv[i+1]);
			}
			else if (strcmp(argv[i], "-sp") == 0)
			{
				strcpy(sp, argv[i+1]);
			}
			else if (strcmp(argv[i], "-ep") == 0)
			{
				strcpy(ep, argv[i+1]);
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				strcpy(out, argv[i+1]);
			}
		}
	}

	minLen -= getEndIndex(sp) + getEndIndex(ep);
	maxLen -= getEndIndex(sp) + getEndIndex(ep);

	if (minLen == 0 || maxLen == 0 || minLen > maxLen)
	{
		printf("Incorrect minLen or maxLen argument!\n");
	}

	//OPEN THE FILE
	if (out[0] != 0)
	{
		outputFile = fopen(out, "w");
		if (outputFile == NULL)
		{
			printf("Can't open the file!\n");
			exit(-1);
		}
	}

	for (int i = minLen; i <= maxLen; i++)
	{
		generatePermutations(ch, i);
	}

	if (outputFile != NULL)
	{
		fclose(outputFile);
	}
}
