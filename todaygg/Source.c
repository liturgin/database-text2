#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct CourseWork
{
	char Autor[50];               // �����
	char Name[50];                // �������� ������
	char Discipline[20];          // �������
	int Day, Month, Year;         // ���� �����
	int Assessment;               // ������
};
typedef struct CourseWork CourseWork_type;

CourseWork_type AddCourseWork();// ���������� �������� ������
void ShowCourseWorks(CourseWork_type* CourseWorks, int countCourseWorks); // ����� ������ � �������� �������
CourseWork_type SearchName(CourseWork_type* CourseWorks, int countCourseWorks, char* searchName); // ����� �� ����
CourseWork_type* SearchDate(CourseWork_type* CourseWorks, int countCourseWorks, int searchDayS, int searchMonthS, int searchYearS, int searchDayE, int searchMonthE, int searchYearE);//����� �� ����
CourseWork_type* SortByAssessment(CourseWork_type* CourseWorks, int countCourseWorks); // ���������� �� �������
void WriteToFile(CourseWork_type* CourseWorks, int countCourseWorks, char* filename); // ������ ������ � ����
int SizeFromFile(char* filename); // ���������� ������� � �����
CourseWork_type* ReadFromFile(CourseWork_type* CourseWorks, char* filename);//������ �� �����

int main()
{
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");

	CourseWork_type* CourseWorks = NULL;
	int countCourseWorks = 0, menu;
	char filename[25];

	printf("������� �������� �����: ");
	scanf("%s", &filename);

	do
	{
		printf("1 - �������� �������� ������\n"
			"2 - ����� ����������� �������� �����\n"
			"3 - ����� �������� ������\n"
			"4 - ������������� �������� ������ �� ������\n"
			"5 - ������ ������ � ������� � ����\n"
			"6 - ������ ������ � ������� �� �����\n"
			"7 - ������� ����\n"
			"0 - �����\n");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1: //���������� �������� ������
		{
			CourseWorks = realloc(CourseWorks, ++countCourseWorks * sizeof(CourseWork_type));
			CourseWorks[countCourseWorks - 1] = AddCourseWork();
			break;
		}
		case 2: // ����� ���� �������
		{
			ShowCourseWorks(CourseWorks, countCourseWorks);
			break;
		}
		case 3: //����� �� �������
		{
			int menu_case3;

			printf("�������� �������� ������:\n"
				"1 - ����� �� ����\n"
				"2 - ����� �� ����\n");
			scanf("%d", &menu_case3);

			if (menu_case3 == 1)
			{
				char searchName[25];

				printf("������� ���� ��� ������\n");
				scanf("%s", &searchName);

				CourseWork_type foundCourseWork = SearchName(CourseWorks, countCourseWorks, searchName);
				if (foundCourseWork.Name != "-")
				{
					printf("---------------------------------------------------------------------------------------------------------\n");
					printf("|                ����                   |        �����        |       �������       |   ����   | ������ |\n");
					printf("---------------------------------------------------------------------------------------------------------\n");

					printf("|%39s|%21s|%21s|%2d.%2d.%4d|%8d|\n", foundCourseWork.Name, foundCourseWork.Autor, foundCourseWork.Discipline, foundCourseWork.Day, foundCourseWork.Month, foundCourseWork.Year, foundCourseWork.Assessment);
					printf("---------------------------------------------------------------------------------------------------------\n");
				}
			}
			else
			{
				int searchDayStart, searchMonthStart, searchYearStart;
				int searchDayEnd, searchMonthEnd, searchYearEnd;

				printf("������� �������� ��� ������ � ������� __.__.____-__.__.____\n");
				scanf("%d.%d.%d-%d.%d.%d", &searchDayStart, &searchMonthStart, &searchYearStart,
					&searchDayEnd, &searchMonthEnd, &searchYearEnd);

				ShowCourseWorks(SearchDate(CourseWorks, countCourseWorks, searchDayStart, searchMonthStart, searchYearStart, searchDayEnd, searchMonthEnd, searchYearEnd), countCourseWorks);
			}
			break;
		}
		case 4: // ���������� �� �������
		{
			ShowCourseWorks(SortByAssessment(CourseWorks, countCourseWorks), countCourseWorks);
			break;
		}
		case 5: //������ ������ � ����
		{
			WriteToFile(CourseWorks, countCourseWorks, filename);
			break;
		}
		case 6: // ������ ������ �� �����
		{
			countCourseWorks = SizeFromFile(filename) - 1;
			CourseWorks = realloc(CourseWorks, sizeof(CourseWork_type) * countCourseWorks);
			CourseWorks = ReadFromFile(CourseWorks, filename);
			ShowCourseWorks(CourseWorks, countCourseWorks);
			break;
		}
		case 7: //����� �����
		{
			printf("������� �������� �����: ");
			scanf("%s", &filename);
			break;
		}
		case 0: //�����
			break;
		default:
			printf("������������ �����\n");
		}
	} while (menu != 0);
}

CourseWork_type AddCourseWork()
{
	CourseWork_type newWork;

	printf("������� ������ ������\n");
	scanf("%s", &newWork.Autor);

	printf("������� �������� ������\n");
	scanf("%s", &newWork.Name);

	printf("������� �������\n");
	scanf("%s", &newWork.Discipline);

	printf("������� ���� ����� � ������� __.__.____\n");
	scanf("%d.%d.%d", &newWork.Day, &newWork.Month, &newWork.Year);

	printf("������� ������\n");
	scanf("%d", &newWork.Assessment);

	return newWork;
}

void ShowCourseWorks(CourseWork_type* CourseWorks, int countCourseWorks)
{
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("|                ����                   |        �����        |       �������       |   ����   | ������ |\n");
	printf("---------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < countCourseWorks; i++)
	{
		if (strcmp(CourseWorks[i].Name, "-") == 0) break;
		printf("|%39s|%21s|%21s|%2d.%2d.%4d|%8d|\n", CourseWorks[i].Name, CourseWorks[i].Autor, CourseWorks[i].Discipline, CourseWorks[i].Day, CourseWorks[i].Month, CourseWorks[i].Year, CourseWorks[i].Assessment);
		printf("---------------------------------------------------------------------------------------------------------\n");
	}
}

CourseWork_type SearchName(CourseWork_type* CourseWorks, int countCourseWorks, char* searchName)
{
	CourseWork_type founeCourseWork = { "-", "-", "-", 0, 0, 0, 0 };

	for (int i = 0; i < countCourseWorks; i++)
	{
		if (strcmp(CourseWorks[i].Name, searchName) == 0)
			return CourseWorks[i];
	}
	return founeCourseWork;
}

CourseWork_type* SearchDate(CourseWork_type* CourseWorks, int countCourseWorks, int searchDayS, int searchMonthS, int searchYearS, int searchDayE, int searchMonthE, int searchYearE)
{
	CourseWork_type* foundedWorks = malloc(sizeof(CourseWork_type));
	int countFoundWorks = 0;

	for (int i = 0; i < countCourseWorks; i++)
	{
		if (
			(CourseWorks[i].Year > searchYearS) ||
			(CourseWorks[i].Year == searchYearS && CourseWorks[i].Month > searchMonthS) ||
			(CourseWorks[i].Year == searchYearS && CourseWorks[i].Month == searchMonthS && CourseWorks[i].Day >= searchDayS)
			)
		{
			if (
				(CourseWorks[i].Year < searchYearE) ||
				(CourseWorks[i].Year == searchYearE && CourseWorks[i].Month < searchMonthE) ||
				(CourseWorks[i].Year == searchYearE && CourseWorks[i].Month == searchMonthE && CourseWorks[i].Day <= searchDayE)
				)
			{
				foundedWorks = realloc(foundedWorks, sizeof(CourseWork_type) * (countFoundWorks + 2));
				foundedWorks[countFoundWorks++] = CourseWorks[i];
			}
		}
	}
	strcpy(foundedWorks[countFoundWorks].Name, "-");

	return foundedWorks;
}

CourseWork_type* SortByAssessment(CourseWork_type* CourseWorks, int countCourseWorks)
{
	CourseWork_type temp;

	for (int i = 0; i < countCourseWorks - 1; i++)
		for (int j = 0; j < countCourseWorks - i - 1; j++)
		{
			if (CourseWorks[j].Assessment > CourseWorks[j + 1].Assessment)
			{
				temp = CourseWorks[j];
				CourseWorks[j] = CourseWorks[j + 1];
				CourseWorks[j + 1] = temp;
			}
		}

	return CourseWorks;
}

void WriteToFile(CourseWork_type* CourseWorks, int countCourseWorks, char* filename)
{
	FILE* fileWriter = fopen(filename, "w");

	for (int i = 0; i < countCourseWorks; i++)
	{
		fprintf(fileWriter, "%s %s %s %d.%d.%d %d\n", CourseWorks[i].Name, CourseWorks[i].Autor, CourseWorks[i].Discipline, CourseWorks[i].Day, CourseWorks[i].Month, CourseWorks[i].Year, CourseWorks[i].Assessment);
	}

	fclose(fileWriter);
}

int SizeFromFile(char* filename)
{
	FILE* fileReader = fopen(filename, "r");
	char buffer;
	int countWorks = 0;

	while (!feof(fileReader))
	{
		fscanf(fileReader, "%c", &buffer);
		if (buffer == '\n')
			countWorks++;
	}

	return countWorks;
}

CourseWork_type* ReadFromFile(CourseWork_type* CourseWorks, char* filename)
{
	FILE* fileReader = fopen(filename, "r");
	int countWorks = SizeFromFile(filename);

	for (int i = 0; i < countWorks; i++)
	{
		fscanf(fileReader, "%s %s %s %d.%d.%d %d\n", &CourseWorks[i].Name, &CourseWorks[i].Autor, &CourseWorks[i].Discipline, &CourseWorks[i].Day, &CourseWorks[i].Month, &CourseWorks[i].Year, &CourseWorks[i].Assessment);
	}
	fclose(fileReader);

	return CourseWorks;
}
