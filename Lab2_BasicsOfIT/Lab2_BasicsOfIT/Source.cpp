#include <iostream>

#define MAX_INPUT_TEXT_SIZE 999
#define NONE -134553562
#define EXPONENT_LEN 8
#define MANTISSA_LEN 23

#include <cassert>


char* getCinText()
{
	char temporaryStr[MAX_INPUT_TEXT_SIZE];

	std::cin.getline(temporaryStr, MAX_INPUT_TEXT_SIZE);
	int strSize = strlen(temporaryStr) + 1; // add 1 to include null operator (/0)

	char* outputStr = new char[strSize];

	for (int i = 0; i < strSize; i++)
		outputStr[i] = temporaryStr[i];
	
	return outputStr;
}

bool cmprStr(char* str1, char* str2)
{
	bool output = false;

	int str1len = strlen(str1);
	int str2len = strlen(str2);

	if (str1len == str2len)
		for (int i = 0; i < str1len; i++)
			if (str1[i] != str2[i])
				return false;
	return true;
}

int fromHexToInt(char* HEX)
{
	int numLenght = strlen(HEX);
	int* decArray = new int[numLenght];
	for (int i = numLenght - 1; i >= 0; i--)
	{
		if (HEX[i] >= '0' && HEX[i] <= '9')
			decArray[(numLenght - 1) - i] = (int)HEX[i] - (int)'0';
		else if (HEX[i] >= 'A' && HEX[i] <= 'F')
			decArray[(numLenght - 1) - i] = (int)HEX[i] - (int)'A' + 10;
	}

	int resultNum = 0;
	for (int i = 0; i < numLenght; i++)
		resultNum += decArray[i] * pow(16, i);

	delete[numLenght] decArray;
	return resultNum;
}

int fromHexToInt(const char* HEX)
{
	return fromHexToInt((char*)HEX);
}
int to_int(char* numstr, int by_id, int to_id = 0)
{
	int resultNum = 0;
	for (int i = by_id; i <= to_id; i++)
	{
		resultNum += (numstr[i] - '0') * pow(10, (to_id - by_id) - (i - by_id));
		int point = 0;
	}

	return resultNum;
}

int to_int(char* numstr)
{
	int numstrlen = strlen(numstr);
	return to_int(numstr, numstrlen);
}

long double to_floatfracpart(char* numstr, int by_id, int to_id)
{
	int numStrLen = by_id;
	long double result = 0;
	for (int i = by_id; i <= to_id; i++)
	{
		result += (numstr[i] - '0') * pow(10, -(i - by_id + 1));
		int point2 = 0;
	}


	int point = 0;
	return result;
}

int* getBinIntNum(int num, int arraySize, int* outputlen)
{
	int* tempResult = new int[arraySize];
	float tempnum = num;
	int lastID = NONE;
	for (int i = arraySize - 1; i >= 0; i--)
	{
		tempnum /= 2.0;
		int intpart = floor(tempnum);
		float fracpart = (float)tempnum - intpart;
		tempResult[i] = fracpart * 2.0;
		if (tempResult[i] == 1)
			lastID = i;
	}

	if (lastID == NONE)
	{
		*outputlen = 1;
		lastID = 0;
	}
	else
		*outputlen = arraySize - (lastID);
	int* result = new int[*outputlen];
	for (int i = 0; i < *outputlen; i++)
	{
		result[i] = tempResult[lastID + i];
	}
	delete[arraySize] tempResult;
	return result;
}

int* getBinIntNumWithSign(int num, int arraySize, int* outputlen)
{
	int sign = (num >= 0) ? 0 : 1;
	num = (sign == 0) ? num : -num;

	int outputlenLocal = 0;

	int* intpartBin = getBinIntNum(num, arraySize, &outputlenLocal);

	int* result = new int[outputlenLocal];
	return 0;
}

float* getBinFracNum(float num, int arraySize, int* outputlen)
{
	double long* tempResult = new double long[arraySize];
	double long tempnum = num;
	int lastID = 0;
	for (int i = 0; i < arraySize; i++)
	{
		tempnum *= 2;

		int intpart = floor(tempnum);
		double long fracpart = tempnum - intpart;

		tempResult[i] = intpart;
		tempnum = fracpart;
		if (tempResult[i] == 1)
			lastID = i;
	}
	
	*outputlen = lastID + 1;
	float* result = new float[*outputlen];
	for (int i = 0; i < *outputlen; i++)
		result[i] = tempResult[i];

	delete[arraySize] tempResult;
	return result;
}

int* getCompRepOfFloat(char* numstr, int bitsize = 0)
{
	int numstrlen = strlen(numstr);

	int sign = 0;
	if (numstr[0] == '-') sign = 1;


	int dotpos = NONE;
	for (int i = sign; i < numstrlen; i++)
		if (numstr[i] == '.' || numstr[i] == ',')
		{
			dotpos = i;
			break;
		}
	if (dotpos == NONE)
		dotpos = numstrlen;

	int intpart = to_int(numstr, sign, dotpos - 1);
	long double fracpart = to_floatfracpart(numstr, dotpos + 1, numstrlen - 1);

	int accuracyArraySize = 32;

	int intpartBinLen;
	int* intpartBin = getBinIntNum(intpart, accuracyArraySize, &intpartBinLen);

	int fracpartBinLen;
	float* fracpartBin = getBinFracNum(fracpart, accuracyArraySize, &fracpartBinLen);

#ifdef _DEBUG
	std::cout << std::endl;
	std::cout << "-----DEBUG-----" << std::endl;
	if (sign == 1)
		std::cout << "-";
	for (int i = 0; i < intpartBinLen; i++)
		std::cout << intpartBin[i];
	std::cout << ".";
	for (int i = 0; i < fracpartBinLen; i++)
		std::cout << fracpartBin[i];
	std::cout << std::endl;
#endif
	int dotposbin = intpartBinLen;
	int exponent = 0;

	if (intpartBinLen == 1 && intpartBin[0] == 0)
	{
		int one_id = NONE;
		for(int i = 0; i < fracpartBinLen; i++)
			if (fracpartBin[i] == 1)
			{
				one_id = i;
				break;
			}
		exponent = -(one_id + 1) + 127;
	}
	else
		exponent = dotposbin - 1 + 127;

	int exponentbin_len = 0;
	int* exponentbin = getBinIntNum(exponent, 8, &exponentbin_len);

#ifdef _DEBUG
	std::cout << "DotPos is:" << dotposbin << std::endl;
	std::cout << "exponent is:" << exponent << std::endl;
	std::cout << "exponentbin is:";
	for (int i = 0; i < exponentbin_len; i++)
		std::cout << exponentbin[i];
	std::cout << std::endl;
#endif
	const int floatsizeInBits = bitsize;
	int bitForSign = 1;

	int* resultBinNum = new int[floatsizeInBits];
	for (int i = 0; i < floatsizeInBits; i++)
		resultBinNum[i] = 0;

	const int exponent_len = 8;

	// fill sign
	resultBinNum[0] = sign;

	// fill exponent
	for (int i = exponent_len; i >= bitForSign; i--)
	{
		if ((exponentbin_len - 1) - (exponent_len - i) >= 0)
			resultBinNum[i] = exponentbin[(exponentbin_len - 1) - (exponent_len - i)];
	}

	// fill mantissa intpart
	for (int i = bitForSign + exponent_len; i < floatsizeInBits - 1; i++)
	{
		int interpartBin_id = (i - (bitForSign + exponent_len)) + 1;
		int fracerpartBin_id = interpartBin_id - intpartBinLen;

		int fracerpartBin_id_case2 = (i - (bitForSign + exponent_len)) + -(exponent - 127);

		if (exponent >= 127)
		{
			if (interpartBin_id < intpartBinLen)
				resultBinNum[i] = intpartBin[interpartBin_id];
			else if (fracerpartBin_id < fracpartBinLen)
				resultBinNum[i] = fracpartBin[fracerpartBin_id];
		}
		else	
		{
			if (fracerpartBin_id_case2 < fracpartBinLen)
				resultBinNum[i] = fracpartBin[fracerpartBin_id_case2];
		}

	}

#ifdef _DEBUG
	std::cout << "Result bin num is:";
	for (int i = 0; i < floatsizeInBits; i++)
	{
		std::cout << resultBinNum[i];
		if (i == 0 || i == 8)
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "-----DEBUG-----" << std::endl;
	std::cout << std::endl;
#endif
	return resultBinNum;
}

int main()
{
	bool started = true;
	while(started)
	{
		std::cout << "Choose what you want the program to do:" << std::endl;
		std::cout << "	1. Convert HEX number to DEC number" << std::endl;
		std::cout << "	2. Convert float number to binary representation of this number in computer" << std::endl;
		std::cout << "	3. Exit from the program" << std::endl;
		char* choose = getCinText();
		system("cls");

		switch (choose[0])
		{
		case '1':
		{
			std::cout << "Enter HEX:";

			char* inputHEX = getCinText();
			int inputHEXlen = strlen(inputHEX);

			std::cout << "DEC:" << fromHexToInt(inputHEX) << std::endl << std::endl;
			break;
		}
		case '2':
		{
			int floatsize = 32;

			std::cout << "Enter float number:";
			char* inputFloatNumber = getCinText();
			int inputFloatNumberLen = strlen(inputFloatNumber);

			int* binNum = getCompRepOfFloat(inputFloatNumber, floatsize);
			
			std::cout << std::endl << "Converted num is:";
			for (int i = 0; i < floatsize; i++)
				std::cout << binNum[i];
			std::cout << std::endl << std::endl;
			break;
		}
		case '3':
		{
			started = false;
			break;
		}
		}
	}
	return 0;
}