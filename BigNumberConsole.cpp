#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))

void usage(char **argv);

// two numbers add
// res is the result of two numbers sum
void AddNumber(char **argv, char *res);

// add two positive number
// res is the result of two numbers sum
void AddTwoPositiveNumber(char **argv, char *tempRes);

// add two negative numbers
// res is the result of two numbers sum
void AddTwoNegativeNumbers(char **argv, char *tempRes);

// add a Negative and a positive number
// res is the result of two numbers sum
void AddNegAndPosNumber(char **argv, char *tempRes);

// if add, check the number
void CheckNumber(char **argv);

//multiplication
void multiplication(char **argv, char *res);

void EveryAdd(char *AddTemp, char *res, int RoundCount);


int main(int argc, char **argv)
{
	if (argc == 2 && _stricmp(argv[1], "-h") == 0)
	{
		usage(argv);
	}
	else if (argc != 4)
	{
		printf("Error!\n");
		usage(argv);
	}
	else if (_stricmp(argv[1], "-h") == 0)
	{
		usage(argv);
	}

	else if (_stricmp(argv[1], "-a") == 0)
	{
		//add
		CheckNumber(argv);
		char res[2056];
		AddNumber(argv, res);

		//filter the res
		int i = 0; 
		for (i = 0; i < strlen(res); i++)
		{
			if (res[i] =='0' || res[i] == '-')
			{
				continue;
			}
			else break;
		}
		char RealRes[2056];
		ZeroMemory(RealRes, 2056);
		if (res[0] == '-')
		{
			RealRes[0] = '-';
			memcpy(RealRes+1, res+i, 2056-i);
		}
		else
		{
			memcpy(RealRes, res + i, 2056-i);
		}
		printf("\n\n%s + %s = %s\n", argv[2], argv[3], RealRes);
	}
	else if (_stricmp(argv[1], "-m") == 0)
	{
		//mutli
		// I don't know how to multi numbers....
		char res[4096];
		ZeroMemory(res, 4096);
		CheckNumber(argv);

#ifdef _DEBUG
		clock_t a,b;
#endif
#ifdef _DEBUG
		a = clock();
#endif // _DEBUG

		multiplication(argv, res);

#ifdef _DEBUG
		b = clock();
#endif // _DEBUG

		printf("\n\n%s * %s = %s\n", argv[2], argv[3], res);

#ifdef _DEBUG
		printf("Usage %d ms", b-a);
#endif // _DEBUG
	}

	return 0;
}


void usage(char **argv)
{
	printf("Usage:\n");
	printf("\tuse: %s -a number1 number2 to calc addition\n.", argv[0]);
	printf("\tuse: %s -m number1 number2 to calc multiplication.\n", argv[0]);
	printf("\tuse: %s -h to show the help.\n", argv[0]);
}

void CheckNumber(char **argv)
{
	strlen(argv[2]) >= 2048 ? (printf("Too long!\n"),exit(0)) : 1;
	strlen(argv[3]) >= 2048 ? (printf("Too long!\n"),exit(0)) : 1;

#ifdef _DEBUG
	printf("[Debug]strlen argv[2]:%d strlen argv[3]:%d", strlen(argv[2]),strlen(argv[3]));
#endif

	char number1[2048];
	char number2[2048];

	ZeroMemory(number1, 2048);
	ZeroMemory(number2, 2048);

	//memcpy(number1, argv[2], 2048);
	memcpy(number2, argv[3], strlen(argv[3]));
	memcpy(number1, argv[2], strlen(argv[3]));

	if (number1[0] != '-' && !(number1[0] >= '0' && number1[0] <= '9') )
	{
		printf("Input error!\n");
		exit(0);
	}
	if (number2[0] != '-' && !(number2[0] >= '0' && number2[0] <= '9') )
	{
		printf("Input error!\n");
		exit(0);
	}

	int cnt = 0;
 	if (number1[0] == '-')
	{
		for (cnt = 1; cnt < strlen(number1); cnt++)
		{
			if ( !(number1[cnt] >= '0' && number1[cnt] <= '9') )
			{
				printf("Input error!\n");
				exit(0);
			}
		}
	}
	else if (number1[0] != '-')
	{
		cnt = 0;
		for (cnt = 0; cnt < strlen(number1); cnt++)
		{
			if ( !(number1[cnt] >= '0' && number1[cnt] <= '9') )
			{
				printf("Input error!\n");
				exit(0);
			}
		}
	}

	cnt = 0;
	if (number2[0] == '-')
	{
		for (cnt = 1; cnt < strlen(number2); cnt++)
		{
			if ( !(number2[cnt] >= '0' && number2[cnt] <= '9') )
			{
				printf("Input error!\n");
				exit(0);
			}
		}
	}
	else if (number2[0] != '-')
	{
		cnt = 0;
		for (cnt = 0; cnt < strlen(number2); cnt++)
		{
			if ( !(number2[cnt] >= '0' && number2[cnt] <= '9') )
			{
				printf("Input error!\n");
				exit(0);
			}
		}
	}
}

void AddNumber(char **argv, char *tempRes)
{
	strlen(argv[2]) >= 2048 ? (printf("Number1 is too long!\n"),exit(0)):1;
	strlen(argv[3]) >= 2048 ? (printf("Number2 is too long!\n"),exit(0)):1;
	char number1[2048], number2[2048];
	char temp1[2048], temp2[2048];
	
	ZeroMemory(number1, 2048);
	ZeroMemory(number2, 2048);
	ZeroMemory(temp1, 2048);
	ZeroMemory(temp2, 2048);

	memcpy(number1, argv[2], strlen(argv[2]));
	memcpy(number2, argv[3], strlen(argv[3]));

	if (number1[0] != '-' && number2[0] != '-')
	{
		//add two positive numbers
		AddTwoPositiveNumber(argv, tempRes);
	}
	else if (number1[0] == '-' && number2[0] == '-')
	{
		//add two negative numbers
		AddTwoNegativeNumbers(argv, tempRes);
	}
	else if ((number1[0] == '-' && number2[0] != '-') || 
		(number1[0] != '-' && number2[0] == '-'))
	{
		//add a negative and a positive number
		AddNegAndPosNumber(argv, tempRes);
	}
	else
	{
		printf("Wrong input!\n");
		exit(0);
	}
}

void AddTwoPositiveNumber(char **argv, char *tempRes)
{
	char number1[2048];
	char number2[2048];
	char res[2056];

	ZeroMemory(number1, 2048);
	ZeroMemory(number2, 2048);
	ZeroMemory(res, 2056);
	memcpy(number1, argv[2], strlen(argv[2]));
	memcpy(number2, argv[3], strlen(argv[3]));

	int c = 0;
	int i = 0;
	int numlen1 = strlen(number1) - 1;
	int numlen2 = strlen(number2) - 1;
	for (i = 0; numlen1 >= 0 || numlen2 >= 0; i++, numlen1--, numlen2--)
	{
		if (numlen1 >= 0 && numlen2 >= 0)
		{
			res[i] = number1[numlen1] + number2[numlen2] + c - '0';
		}
		if (numlen1 >= 0 && numlen2 < 0)
		{
			res[i] = number1[numlen1] + c;
		}
		if (numlen1 < 0 && numlen2 >= 0)
		{
			res[i] = number2[numlen2] + c;
		}
		c = 0;
		if (res[i] > '9')
		{
			c = 1;
			res[i] = res[i] - 10;
		}
	}
	//the reverse sum result in array res.
	//printf("%s + %s = %s", number1, number2, res);
	if (c == 1)
	{
		res[strlen(res)] = '1';
	}
	int tempLen = strlen(res);
	//char tempRes[2056];
	ZeroMemory(tempRes, 2056);
	//reverse the array res, and put it into the tempRes
	int j = 0;
	for (int k = tempLen-1; k >= 0; k--,j++)
	{
		tempRes[j] = res[k];
	}
	//printf("%s + %s = ", number1, number2);
	//printf("%s", tempRes);
}

void AddTwoNegativeNumbers(char **argv, char *tempRes)
{
	char number1[2048];
	char number2[2048];
	char res[2056];

	ZeroMemory(number1, 2048);
	ZeroMemory(number2, 2048);
	ZeroMemory(res, 2056);
	memcpy(number1, argv[2]+1, strlen(argv[2]) - 1);
	memcpy(number2, argv[3]+1, strlen(argv[3]) - 1);

	int c = 0;
	int i = 0;
	int numlen1 = strlen(number1) - 1;
	int numlen2 = strlen(number2) - 1;
	for (i = 0; numlen1 >= 0 || numlen2 >= 0; i++, numlen1--, numlen2--)
	{
		if (numlen1 >= 0 && numlen2 >= 0)
		{
			res[i] = number1[numlen1] + number2[numlen2] + c - '0';
		}
		if (numlen1 >= 0 && numlen2 < 0)
		{
			res[i] = number1[numlen1] + c;
		}
		if (numlen1 < 0 && numlen2 >= 0)
		{
			res[i] = number2[numlen2] + c;
		}
		c = 0;
		if (res[i] > '9')
		{
			c = 1;
			res[i] = res[i] - 10;
		}
	}
	//the reverse sum result in array res.
	//printf("%s + %s = %s", number1, number2, res);
	if (c == 1)
	{
		if (strlen(res) >= 2056)
		{
			printf("Buffer overflow! Maybe the number was too long!\n");
			exit(0);
		}
		else res[strlen(res)] = '1';
	}
	if (strlen(res) >= 2056)
	{
		printf("Buffer overflow! Maybe the number was too long!\n");
		exit(0);
	}
	else res[strlen(res)] = '-';
	int tempLen = strlen(res);
	//char tempRes[2056];
	ZeroMemory(tempRes, 2056);
	//reverse the array res, and put it into the tempRes
	int j = 0;
	for (int k = tempLen-1; k >= 0; k--,j++)
	{
		tempRes[j] = res[k];
	}
}

void AddNegAndPosNumber(char **argv, char *tempRes)
{
	char number1[2048];
	char number2[2048];
	char res[2056];

	ZeroMemory(number1, 2048);
	ZeroMemory(number2, 2048);
	ZeroMemory(res, 2056);

	if (argv[2][0] == '-' && argv[3][0] != '-')
	{
		memcpy(number1, argv[2]+1, strlen(argv[2]) - 1);
		memcpy(number2, argv[3], strlen(argv[3]) );
	}
	else if (argv[2][0] != '-' && argv[3][0] == '-')
	{
		memcpy(number1, argv[2], strlen(argv[2]) );
		memcpy(number2, argv[3]+1, strlen(argv[3]) - 1);
	}

	
	// iFlag is the result singed.
	// 0:+ 1:-
	int iFlag = 0;

	// Find the biggest number 
	int BigNumber = 1;
	if (strlen(number1) > strlen(number2) )
	{
		BigNumber = 1;
	}
	else if (strlen(number1) < strlen(number2) )
	{
		BigNumber = 2;
	}
	else BigNumber = 0;	//two number is eq

	if (BigNumber == 0)
	{
		for (int t = 0; t < strlen(number1); t++)
		{
			if (number1[t] == number2[t])
			{
				continue;
			}
			else if (number1[t] > number2[t])
			{
				BigNumber = 1;
				break;
			}
			else if (number1[t] < number2[t])
			{
				BigNumber = 2;
				break;
			}
		}
	}
	//printf("Big NUmber %d", BigNumber);
	// put the big number to the number1
	// and put the little number to the number2
	if (BigNumber == 1)
	{
		// Do nothing. Because the big number is in
		// the number1
	}
	else if (BigNumber == 2)
	{
		char temp[2048];
		ZeroMemory(temp, 2048);
		memcpy(temp, number1, 2048);
		memcpy(number1, number2, 2048);
		memcpy(number2, temp, 2048);
	}
	else if (BigNumber == 0)
	{
		// the two numbers eq
		// return 0
		ZeroMemory(tempRes, 2056);
		tempRes[0] = '0';
		return;
	}

	
	int c = 0;
	int i = 0;
	int numlen1 = strlen(number1) - 1;
	int numlen2 = strlen(number2) - 1;
	for (i = 0; numlen1 >= 0 || numlen2 >= 0; i++, numlen1--, numlen2--)
	{
		if (numlen1 >= 0 && numlen2 >= 0)
		{
			res[i] = number1[numlen1] - number2[numlen2] - c + '0';
		}
		if (numlen1 >= 0 && numlen2 < 0)
		{
			res[i] = number1[numlen1] - c;
		}
		if (numlen1 < 0 && numlen2 >= 0)
		{
			res[i] = number2[numlen2] - c;
		}
		c = 0;
		if (res[i] < '0')
		{
			c = 1;
			res[i] = res[i] + 10;
		}
	}
	//the reverse sum result in array res.
	//printf("%s + %s = %s", number1, number2, res);
	if (c == 1)
	{
		if (strlen(res) >= 2056)
		{
			printf("Buffer overflow! Maybe the number was too long!\n");
			exit(0);
		}
		else res[strlen(res)] = '1';
	}
	if (strlen(res) >= 2056)
	{
		printf("Buffer overflow! Maybe the number was too long!\n");
		exit(0);
	}
	if (BigNumber == 2 && argv[2][0] == '-' || BigNumber == 1 && argv[3][0] == '-')
	{

	}
	else res[strlen(res)] = '-';
	int tempLen = strlen(res);
	//char tempRes[2056];
	ZeroMemory(tempRes, 2056);
	//reverse the array res, and put it into the tempRes
	int j = 0;
	int firstZero = 0;
	for (int k = tempLen-1; k >= 0; k--,j++)
	{
		tempRes[j] = res[k];
	}
}

void multiplication(char **argv, char *res)
{
	char number1[2048];
	char number2[2048];
	char temp[2056];
	char Addtemp[4096];
	char tempres[4096];

	ZeroMemory(number1, 2048);
	ZeroMemory(number2, 2048);
	ZeroMemory(temp, 2056);
	ZeroMemory(Addtemp, 4096);
	ZeroMemory(tempres, 4096);


	// find the long number 
	// and put it into the number1
	int numlen1 = strlen(argv[2]);
	numlen1 = (argv[2][0] == '-' ? numlen1-1 : numlen1) ;
	int numlen2 = strlen(argv[3]);
	numlen2 = (argv[3][0] == '-' ? numlen2-1 : numlen2) ;
	
	int longNumber = (numlen1 >= numlen2) ? 1 : 2;

	if (longNumber == 1)
	{
		if (argv[2][0] == '-')
		{
			memcpy(number1, argv[2]+1, strlen(argv[2]) - 1);
		}
		else memcpy(number1, argv[2], strlen(argv[2]));

		if (argv[3][0] == '-')
		{
			memcpy(number2, argv[3]+1, strlen(argv[3]) - 1);
		}
		else memcpy(number2, argv[3], strlen(argv[3]));
	}
	if (longNumber == 2)
	{
		if (argv[2][0] == '-')
		{
			memcpy(number2, argv[2]+1, strlen(argv[2]) - 1);
		}
		else memcpy(number2, argv[2], strlen(argv[2]));


		if (argv[3][0] == '-')
		{
			memcpy(number1, argv[3]+1, strlen(argv[3]) - 1);
		}
		else memcpy(number1, argv[3], strlen(argv[3]));
	}
	// now the longer number is in the number1
	// and the short number is in the number2
	
	int c = 0;
	numlen1 = strlen(number1) - 1;
	numlen2 = strlen(number2) - 1;
	int i = 0;
	int RoundCount = 0;
	
	for (i = 0; numlen2 >= 0; i++, numlen2--)
	{

		for (int j = numlen1, t = 0; j >= 0; j--, t++)
		{
			temp[t] = (number2[numlen2] - '0') * (number1[j] - '0') + c;
			c = temp[t]/10;
			temp[t] = (temp[t] % 10) + '0';
		}
		if (c != 0)
		{
			if (strlen(temp) >= 2056)
			{
				printf("Buffer overflow!\n");
				exit(0);
			}
			else temp[strlen(temp)] = c + '0';
		}
#ifdef _DEBUG
		printf("[Debug]i:%d temp:%s\n", i, temp);
#endif
		// ฒน0
		int zeroNumber = 0;
		for (zeroNumber = 0; zeroNumber < i; zeroNumber++)
		{
			Addtemp[zeroNumber] = '0';
		}
		//Addtemp = temp
		memcpy(Addtemp+zeroNumber, temp, strlen(temp));

		//reverse addTemp
		char ttt[4096];
		memcpy(ttt, Addtemp, 4096);
		ZeroMemory(Addtemp, 4096);
		for (int i = 0, j = strlen(ttt)-1; i < strlen(ttt); i++, j--)
		{
			Addtemp[i] = ttt[j];
		}
		//reverse tempres
		ZeroMemory(ttt, 4096);
		memcpy(ttt, tempres, 4096);
		for (int i = 0, j = strlen(ttt)-1; i < strlen(ttt); i++,j--)
		{
			tempres[i] = ttt[j];
		}
		//add to res
#ifdef _DEBUG
		printf("[Debug]Addtemp:%s\n",Addtemp);
#endif 

		EveryAdd(Addtemp, tempres, RoundCount);

#ifdef _DEBUG
		printf("[Debug]tempres:%s\n", tempres);
#endif 
		// if finished add. must clear sth.
		ZeroMemory(Addtemp,4096);
		ZeroMemory(temp, 2056);
		c = 0;
		RoundCount++;
	}
	strlen(tempres) >= 4096 ? (printf("Buffer overflow!\n"),exit(0)) : 1;
		
	if (argv[2][0] == '-' && argv[3][0] != '-' || 
		argv[2][0] != '-' && argv[3][0] == '-')
	{		
		tempres[strlen(tempres)] = '-';
	}
	// at the end of this function
	// we need to reverse the res
	
	for (int i = 0, j = strlen(tempres)-1; i < strlen(tempres); i++, j--)
	{
		res[i] = tempres[j];
	}
}


void EveryAdd(char *AddTemp, char *res, int RoundCount)
{
	char number1[4096];
	char number2[4096];

	ZeroMemory(number1, 4096);
	ZeroMemory(number2, 4096);

	strlen(AddTemp) >= 4096 ? (printf("Buffer overflow!\n"),exit(0)) : 
		memcpy(number1, AddTemp, strlen(AddTemp));

	strlen(res) >= 4096 ? (printf("Buffer overflow!\n"),exit(0)) : 
		memcpy(number2, res, strlen(res));

	ZeroMemory(res, 4096);

	int c = 0;
	int i = 0;
	int numlen1 = strlen(number1) - 1;
	int numlen2 = strlen(number2) - 1;

	for (i = 0; numlen1 >= 0 || numlen2 >= 0; i++, numlen1--, numlen2--)
	{
		if (numlen1 >= 0 && numlen2 >= 0)
		{
			res[i] = number1[numlen1] + number2[numlen2] + c - '0';
		}
		if (numlen1 >= 0 && numlen2 < 0)
		{
			res[i] = number1[numlen1] + c;
		}
		if (numlen1 < 0 && numlen2 >= 0)
		{
			res[i] = number2[numlen2] + c;
		}
		c = 0;
		if (res[i] > '9')
		{
			c = 1;
			res[i] = res[i] - 10;
		}
	}
	if (c == 1)
	{
		res[strlen(res)] = '1';
	}
}