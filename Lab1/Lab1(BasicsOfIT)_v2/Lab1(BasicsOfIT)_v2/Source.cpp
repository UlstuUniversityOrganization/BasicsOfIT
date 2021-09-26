#include <iostream>

#define YES 1
#define NO 0;
#define MAX_INPUT_TEXT_SIZE 5000
int* GetRelativeSerialNum(char* text, int textSize)
{
	int* num = new int[textSize];

	for (int i = 0; i < textSize; i++)
		num[i] = (unsigned int)text[i];

	bool* used = new bool[textSize];
	for (int i = 0; i < textSize; i++)
		used[i] = false;

	int id = 0;
	int order = 0;
	for (int i = 0; i < textSize; i++)
	{
		int min = 99999999;
		for (int j = 0; j < textSize; j++)
		{
			if (used[j] == false)
			{
				int symbolCode = (int)text[j];

				if (symbolCode >= (int)'A' && symbolCode <= (int)'Z')
					symbolCode += 'a' - 'A';

				if (min > symbolCode)
				{
					min = symbolCode;
					id = j;
				}
			}
		}
		used[id] = true;
		num[id] = order;
		order++;
	}
	return num;
}

class DoubleCarryingEncryptor
{
public:
	DoubleCarryingEncryptor() {};

	char* Encrypte(char* text, int textSize, int columnsCount, char* key1, char* key2, int* encryptedTextSize)
	{
		int rawsCount = ceil((float)textSize / (float)columnsCount);

		char** symbolsTable = new char* [columnsCount];
		for (int i = 0; i < columnsCount; i++)
			symbolsTable[i] = new char[rawsCount];

		for (int y = 0; y < rawsCount; y++)
			for (int x = 0; x < columnsCount; x++)
			{
				int id = x + columnsCount * y;
				if (id < textSize)
					symbolsTable[x][y] = text[id];
				else
					symbolsTable[x][y] = ' ';
			}

		int temporaryTextSize;

		temporaryTextSize = strlen(key1);

		int key1Size = temporaryTextSize;

		char* key1Local = new char[columnsCount];
		for (int i = 0; i < columnsCount; i++)
		{
			if (i < temporaryTextSize)
				key1Local[i] = key1[i];
			else
				key1Local[i] = ' ';
		}

		temporaryTextSize = strlen(key2);

		char* key2Local = new char[temporaryTextSize];
		for (int i = 0; i < temporaryTextSize; i++)
			key2Local[i] = key2[i];

		int* key1Order = GetRelativeSerialNum(key1Local, columnsCount);
		int* key2Order = GetRelativeSerialNum(key2Local, rawsCount);

		for (int i = 0; i < columnsCount; i++)
		{
			int min = 9999999;
			int id = 0;
			for (int j = i; j < columnsCount; j++)
			{
				if (min > key1Order[j])
				{
					min = key1Order[j];
					id = j;
				}
			}
			std::swap(key1Order[id], key1Order[i]);
			for (int k = 0; k < rawsCount; k++)
				std::swap(symbolsTable[id][k], symbolsTable[i][k]);
		}

		for (int i = 0; i < rawsCount; i++)
		{
			int min = 9999999;
			int id = 0;
			for (int j = i; j < rawsCount; j++)
			{
				if (min > key2Order[j])
				{
					min = key2Order[j];
					id = j;
				}
			}
			std::swap(key2Order[id], key2Order[i]);
			for (int k = 0; k < columnsCount; k++)
				std::swap(symbolsTable[k][id], symbolsTable[k][i]);
		}

		char* encryptedText = new char[rawsCount * columnsCount];
		for (int y = 0; y < rawsCount; y++)
			for (int x = 0; x < columnsCount; x++)
			{
				int id = x + columnsCount * y;
				encryptedText[id] = symbolsTable[x][y];
				int point = 0;
			}


		*encryptedTextSize = rawsCount * columnsCount;
		return encryptedText;
	}

	char* Decrypte(char* text, int textSize, int columnsCount, char* key1, char* key2, int* decryptedTextSize)
	{
		int rawsCount = ceil((float)textSize / (float)columnsCount);

		char** symbolsTable = new char* [columnsCount];
		for (int i = 0; i < columnsCount; i++)
			symbolsTable[i] = new char[rawsCount];

		for (int y = 0; y < rawsCount; y++)
			for (int x = 0; x < columnsCount; x++)
			{
				int id = x + columnsCount * y;
				if (id < textSize)
					symbolsTable[x][y] = text[id];
				else
					symbolsTable[x][y] = ' ';
			}

		int* key1Order = GetRelativeSerialNum(key1, columnsCount);
		int* key1ID = new int[columnsCount];
		for (int i = 0; i < columnsCount; i++)
			key1ID[i] = i;

		int* key2Order = GetRelativeSerialNum(key2, columnsCount);
		int* key2ID= new int[rawsCount];
		for (int i = 0; i < rawsCount; i++)
			key2ID[i] = i;

		for (int i = 0; i < columnsCount; i++)
		{
			int min = 9999999;
			int id = 0;
			for (int j = i; j < columnsCount; j++)
			{
				if (min > key1Order[j])
				{
					min = key1Order[j];
					id = j;
				}
			}
			std::swap(key1Order[id], key1Order[i]);
			std::swap(key1ID[id], key1ID[i]);
		}

		for (int i = 0; i < rawsCount; i++)
		{
			int min = 9999999;
			int id = 0;
			for (int j = i; j < rawsCount; j++)
			{
				if (min > key2Order[j])
				{
					min = key2Order[j];
					id = j;
				}
			}
			std::swap(key2Order[id], key2Order[i]);
			std::swap(key2ID[id], key2ID[i]);
		}


		for (int i = 0; i < columnsCount; i++)
		{
			int min = 9999999;
			int id = 0;
			for (int j = i; j < columnsCount; j++)
			{
				if (min > key1ID[j])
				{
					min = key1ID[j];
					id = j;
				}
			}
			std::swap(key1ID[id], key1ID[i]);
			for (int k = 0; k < rawsCount; k++)
				std::swap(symbolsTable[id][k], symbolsTable[i][k]);
		}


		for (int i = 0; i < rawsCount; i++)
		{
			int min = 9999999;
			int id = 0;
			for (int j = i; j < rawsCount; j++)
			{
				if (min > key2ID[j])
				{
					min = key2ID[j];
					id = j;
				}
			}
			std::swap(key2ID[id], key2ID[i]);
			for (int k = 0; k < columnsCount; k++)
				std::swap(symbolsTable[k][id], symbolsTable[k][i]);
		}

		// output text initialization

		char* decryptedText = new char[rawsCount * columnsCount];
		for (int y = 0; y < rawsCount; y++)
			for (int x = 0; x < columnsCount; x++)
			{
				int id = x + columnsCount * y;
				decryptedText[id] = symbolsTable[x][y];
				int point = 0;
			}

		*decryptedTextSize = rawsCount * columnsCount;
		return decryptedText;
	}
};

char* cinGetText()
{
	char temporaryText[MAX_INPUT_TEXT_SIZE];

	std::cin.ignore();
	std::cin.getline(temporaryText, MAX_INPUT_TEXT_SIZE);
	int textSize = strlen(temporaryText);

	char* text = new char[textSize];
	for (int i = 0; i < textSize + 1; i++)
		text[i] = temporaryText[i];

	return text;
}

int main()
{
	setlocale(0, "rus");

	bool clearAlerts = false;
	DoubleCarryingEncryptor encryptor;

	std::cout << "Do you want to encrypte or decrypte the text?" << std::endl;
	std::cout << "	1. Encrypte" << std::endl;
	std::cout << "	2. Decrypte" << std::endl;


	int choose = 0;
	std::cin >> choose;
	if(clearAlerts == true)
		system("cls");

	if(choose == 1)
		std::cout << "Enter the text for encrypting:";
	else if(choose == 2)
		std::cout << "Enter the text for decrypting:";

	char* text = cinGetText();
	int textSize = strlen(text);

	if (clearAlerts == true)
		system("cls");

	std::cout << "Enter columns count:";
	int columnsCount;
	std::cin >> columnsCount;

	if (clearAlerts == true)
		system("cls");

	std::cout << "Enter the key number one:";
	char* key1 = cinGetText();

	if (clearAlerts == true)
		system("cls");

	std::cout << "Enter the key number two:";
	char* key2 = cinGetText();

	if (clearAlerts == true)
		system("cls");

	switch (choose)
	{
		case 1:
		{
			int encryptedTextSize = 0;
			char* encryptedText = encryptor.Encrypte(text, textSize, columnsCount, key1, key2, &encryptedTextSize);

			std::cout << "This is what you got:" << std::endl;
			std::cout << std::endl;

			for (int i = 0; i < encryptedTextSize; i++)
				std::cout << encryptedText[i];
		}break;
		case 2:
		{
			int decryptedTextSize = 0;
			char* decryptedText = encryptor.Decrypte(text, textSize, 6, key1, key2, &decryptedTextSize);

			std::cout << "This is what you got:" << std::endl;
			std::cout << std::endl;


			for (int i = 0; i < decryptedTextSize; i++)
				std::cout << decryptedText[i];		
		}
	}
	return 0;
}