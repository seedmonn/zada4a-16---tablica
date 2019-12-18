/*-------------------------------------------------------------------*/
/*В текст файле слова отделяются друг от друга разделителем.
  Разделитель - параметр. Файл вывести в виде таблицы.
  Необходима возможность запуска из командной строк*/
  /*-------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#define PATH_NAME 100

int main(int argc, char* argv[])
{
	FILE* F1;
	char path[PATH_NAME];
	char delimiter, c;
	bool flag = 0;
	int8_t max_len_word = 0, count = 0;
	int16_t max_delimiter = 0, count_del = 0;
	errno_t file;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc < 2)
	{
		printf("Enter path to file: ");
		gets_s(path, PATH_NAME);
	}
	else
	{
		if (sizeof(argv) > PATH_NAME)
		{
			printf("Copy error! Size argv is larger that size path.\n");
			system("pause");
			return 0;
		}
		strcpy_s(path, sizeof(path), argv[1]);
	}

	printf("Enter delimiter: ");
	scanf_s("%c", &delimiter, 1);

	if ((file = fopen_s(&F1, path, "r")) != NULL)
	{
		printf("Error to open file for reading!\n");
		system("pause");
		return 0;
	}

	while (!feof(F1)) {

		/*fscanf_s(F1, "%s", word, (unsigned)_countof(word));*/
		c = fgetc(F1);

		if (c == delimiter)
		{
			if (count > max_len_word)
				max_len_word = count;
			count = 0;
			count_del++;
		}

		else if (c == '\n' || c == EOF)
		{
			if (count > max_len_word)
				max_len_word = count;
			count = 0;

			if (count_del > max_delimiter)
				max_delimiter = count_del;
			count_del = 0;
		}

		else
		{
			count++;
		}

	} rewind(F1);

	while (!feof(F1))
	{
		c = fgetc(F1);

		if (c == delimiter)
		{
			if (flag == 0) {
				while (count < max_len_word)
				{
					printf(" ");
					count++;
				}
				printf("|");
				count_del++;
			}

			count = 0;
			flag = 1;                                  // Признак того, что уже встретился один разделитель до этого
		}

		else if (c == '\n' || c == EOF)
		{
			if (flag == 0) {
				while (count < max_len_word)
				{
					printf(" ");
					count++;
				}
				printf("|");
			}

			count = 0;
			flag = 1;                                  // Признак того, что уже встретился один разделитель до этого


			while (count_del < max_delimiter)
			{
				while (count < max_len_word)
				{
					printf(" ");
					count++;
				}
				count = 0;
				printf("|");
				count_del++;
			}
			printf("\n------------------------------------------\n");
			count_del = 0;
		}

		else
		{
			flag = 0;
			printf("%c", c);
			count++;
		}
	} printf("\n");

	fclose(F1);
	printf("MAX_LEN_WORD: %hhd\n", max_len_word);
	printf("Path: %s\n", path);
	printf("EXE File: %s\n", argv[0]);
	system("pause");
	return 0;
}
