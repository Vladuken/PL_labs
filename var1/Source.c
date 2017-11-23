#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#define SIZE 100
#define BADMARK 5

struct studinfo
{
	int group;
	char lastname[30];
	int m1;
	int m2;
	int m3;
	int m4;
	int m5;
};


void create_db_to_file(int size);
int add(struct studinfo name[SIZE],int size);
void print_stud(struct studinfo name[SIZE],int size);
void print_to_file(struct studinfo name[SIZE], int size);
int del(struct studinfo name[SIZE], int size);
void edit(struct studinfo name[SIZE], int size);
void help();
void part1(struct studinfo name[SIZE], int size);
void part2(struct studinfo name[SIZE], int size);

void main()
{
	srand(time(NULL));

	//create_db_to_file(7);

	FILE *f1, *f2;
	struct studinfo name[SIZE] = {0};

	//global
	int size = 0;

	//считать из файла размер массива
	f2 = fopen("size.txt", "r");
	fscanf(f2, "%d", &size);
	fclose(f2);


	//printf("%d", size);

	//считать массив из файла
	f1 = fopen("new_ch_db.txt", "r");
	fread(name, sizeof(struct studinfo), size, f1);
	fclose(f1);
	help();
	print_stud(name, size);
	int check = 0;
	printf("Input comand:\n");
	scanf("%d", &check);
	while (check)
	{
		if (check == 1)
		{
			size = add(name, size);
		}
		if (check == 2)
		{
			size = del(name, size);
		}
		if (check == 3)
		{
			edit(name, size);
		}
		if (check == 4)
		{
			print_stud(name, size);
		}
		if (check == 5)
		{
			help();
		}
		if (check == 6)
		{
			part1(name,size);
		}
		if (check == 7)
		{
			part2(name, size);
		}
		
		
		printf("Input comand:\n");
		scanf("%d", &check);
	}
	

	print_to_file(name, size);

	//записать в файла размер массива
	f2 = fopen("size.txt", "w");
	fprintf(f2, "%d", size);
	fclose(f2);


	getchar();
}


void help()
{
	printf("%40s", "Add student - 1\n");
	printf("%40s", "Delete student - 2\n");
	printf("%40s", "Edit student - 3\n");
	printf("%40s", "Print student list - 4\n");
	printf("%40s", "Help - 5\n");
	printf("%40s", "Part1 - 6\n");
	printf("%40s", "Part2 - 7\n");
	printf("\n\n\n");

}
void create_db_to_file(int size)
{

	FILE *f1, *f2;
	struct studinfo name[50];
	{
		name[0].group = 651001;
		strcpy(name[0].lastname, "Petrushkevich");
		name[0].m1 = 2;
		name[0].m2 = 6;
		name[0].m3 = 6;
		name[0].m4 = 6;
		name[0].m5 = 6;

		name[1].group = 651004;
		strcpy(name[1].lastname, "Polkhovskiy");
		name[1].m1 = 6;
		name[1].m2 = 3;
		name[1].m3 = 9;
		name[1].m4 = 2;
		name[1].m5 = 10;

		name[2].group = 651001;
		strcpy(name[2].lastname, "Azarov");
		name[2].m1 = 6;
		name[2].m2 = 8;
		name[2].m3 = 8;
		name[2].m4 = 7;
		name[2].m5 = 4;

		name[3].group = 651001;
		strcpy(name[3].lastname, "Borisevich");
		name[3].m1 = 7;
		name[3].m2 = 7;
		name[3].m3 = 9;
		name[3].m4 = 6;
		name[3].m5 = 9;

		name[4].group = 651005;
		strcpy(name[4].lastname, "Pliska");
		name[4].m1 = 5;
		name[4].m2 = 8;
		name[4].m3 = 7;
		name[4].m4 = 5;
		name[4].m5 = 4;

		name[5].group = 651001;
		strcpy(name[5].lastname, "Tsaruk");
		name[5].m1 = 10;
		name[5].m2 = 6;
		name[5].m3 = 7;
		name[5].m4 = 8;
		name[5].m5 = 6;

		name[6].group = 651006;
		strcpy(name[6].lastname, "Makarchik");
		name[6].m1 = 7;
		name[6].m2 = 5;
		name[6].m3 = 8;
		name[6].m4 = 4;
		name[6].m5 = 9;


	}

	f2 = fopen("size.txt", "w");
	fprintf(f2, "%d", 6);
	fclose(f2);

	f1 = fopen("new_ch_db.txt", "w");
	fwrite(name, sizeof(struct studinfo), size, f1);
	fclose(f1);

}

int add(struct studinfo name[SIZE],int size)
{
	char lastname[30];
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int m4 = 0;
	int m5 = 0;
	int group = 0;

	printf("Name: \n");
	scanf("%s",lastname);

	printf("Exam 1:");
	scanf("%d",&m1);

	printf("Exam 2:");
	scanf("%d", &m2);

	printf("Exam 3:");
	scanf("%d", &m3);

	printf("Exam 4:");
	scanf("%d", &m4);

	printf("Exam 5:");
	scanf("%d", &m5);

	printf("Group:");
	scanf("%d", &group);
	



	//добавляем в массив
	

	name[size].group = group;
	strcpy(name[size].lastname, lastname);
	name[size].m1 = m1;
	name[size].m2 = m2;
	name[size].m3 = m3;
	name[size].m4 = m4;
	name[size].m5 = m5;

	size++;

	return size;
}

int del(struct studinfo name[SIZE], int size)
{
	struct studinfo newname[SIZE] = { 0 };
	char lastname[30];
	printf("Input name: \n");
	scanf("%s", lastname);
	int buffsize = size;
	
	
	//
	int newbuffsize = size;
	for (int i = 0; i < size; i++)
	{
		if (strcmp(name[i].lastname, lastname) == 0)
		{
			name[i].group = -1;
			strcpy(name[i].lastname, "0");
			name[i].m1 = 0;
			name[i].m2 = 0;
			name[i].m3 = 0;
			name[i].m4 = 0;
			name[i].m5 = 0;

			newbuffsize--;
		}
	}
	size = newbuffsize;


	int index = 0;

	//заполнение нового массива
	for (int i = 0; i < buffsize; i++)
	{
		if (name[i].group != -1)
		{
			newname[index].group = name[i].group;
			strcpy(newname[index].lastname, name[i].lastname);
			newname[index].m1 = name[i].m1;
			newname[index].m2 = name[i].m2;
			newname[index].m3 = name[i].m3;
			newname[index].m4 = name[i].m4;
			newname[index].m5 = name[i].m5;
			index++;
		}
	}

	//заполнение старого массива
	for (int i = 0; i < size; i++)
	{
		name[i].group = newname[i].group;
		strcpy(name[i].lastname, newname[i].lastname);
		name[i].m1 = newname[i].m1;
		name[i].m2 = newname[i].m2;
		name[i].m3 = newname[i].m3;
		name[i].m4 = newname[i].m4;
		name[i].m5 = newname[i].m5;
	}

	return size;
}

void edit(struct studinfo name[SIZE], int size)
{
	printf("Input name: \n");
		char lastname[30];
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int m4 = 0;
	int m5 = 0;
	int group = 0;

	scanf("%s", lastname);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(name[i].lastname, lastname) == 0)
		{
			
			printf("Name: \n");
			scanf("%s", lastname);

			printf("Exam 1:");
			scanf("%d", &m1);

			printf("Exam 2:");
			scanf("%d", &m2);

			printf("Exam 3:");
			scanf("%d", &m3);

			printf("Exam 4:");
			scanf("%d", &m4);

			printf("Exam 5:");
			scanf("%d", &m5);

			printf("Group:");
			scanf("%d", &group);

			name[i].group = group;
			strcpy(name[i].lastname, lastname);
			name[i].m1 = m1;
			name[i].m2 = m2;
			name[i].m3 = m3;
			name[i].m4 = m4;
			name[i].m5 = m5;

		}
	}


}

void print_stud(struct studinfo name[SIZE],int size)
{
	//вывод студентов
	printf("Students: \n\n");
	for (int i = 0; i < size; i++)
	{
		printf("%10d  Name: %15s  Exam: %3d%3d%3d%3d%3d \n", name[i].group, name[i].lastname, name[i].m1, name[i].m2, name[i].m3, name[i].m4, name[i].m5);
	}
}

void print_to_file(struct studinfo name[SIZE], int size)
{
	FILE *f;
	f = fopen("new_ch_db.txt", "w");
	fwrite(name, sizeof(struct studinfo), size, f);
	fclose(f);
}

void part1(struct studinfo name[SIZE], int size)
{
	printf("List of bad students: \n");
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		count = 0;
		if(name[i].m1 < BADMARK)  { count++; }
		if (name[i].m2 < BADMARK) { count++; }
		if (name[i].m3 < BADMARK) { count++; }
		if (name[i].m4 < BADMARK) { count++; }
		if (name[i].m5 < BADMARK) { count++; }

		if (count)
		{
			printf("%20s %10d Number:%3d \n", name[i].lastname, name[i].group, count);
		}
	}
}

void part2(struct studinfo name[SIZE], int size)
{
	int groupsum = 0;
	int sum = 0;
	int count = 5;
	int groupcount = 0;
	int group = 0;
	float mid = 0.0;
	float groupmid = 0.0;
	printf("Input group number:\n");
	scanf("%d", &group);
	printf("\n\nStudents of group %d\n\n", group);
	for (int i = 0; i < size; i++)
	{
		sum = 0;
		if (name[i].group == group)
		{
			sum = name[i].m1 + name[i].m2 + name[i].m3 + name[i].m4 + name[i].m5;
			mid = (float)sum / count;
			groupsum += sum;
			groupcount += count;
			printf("%20s Marks: %4d%4d%4d%4d%4d  Middle:%.3f \n", name[i].lastname, name[i].m1 ,name[i].m2 ,name[i].m3 ,name[i].m4 ,name[i].m5, mid);
		}
	}
	if (groupcount) 
	{
		groupmid = (float)groupsum / groupcount;
	}
	else
	{
		groupmid = 0.0;
	}
	
	printf("\nGroup mid: %4f\n", groupmid);
}