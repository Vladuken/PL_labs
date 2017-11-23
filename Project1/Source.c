#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define SIZE 7
#define SZ 900
struct studinfo 
{
	char lastname[30];
	char place[30];
	int math;
	int phis;
	int rus;
	float middle;
};


void part1();
void create_db();
void part2();



void main()
{
	srand(time(NULL));
	create_db();

	part1();
	part2();

	getchar();
	
}


void part1()
{
	//ќписание данных 
	FILE *f1, *f2;
	signed int number;


	f1 = fopen("f1.txt", "w");
	for (int i = 0; i <= 10; i++)
	{
		fprintf(f1, "%d\n", rand() % 100 - 50);
	}
	fclose(f1);

	f1 = fopen("f1.txt", "r");
	f2 = fopen("f2.txt", "w");
	for (int i = 0; i <= 10; i++)
	{
		fscanf(f1, "%d", &number);

		if (number > 0)
		{
			fprintf(f2, "%d\n", number);
		}
	}

	fclose(f1);
	fclose(f2);
}
void create_db()
{	

	FILE *f1;
	struct studinfo name[50];
	{
		strcpy(name[0].lastname, "Petrushkevich");
		strcpy(name[0].place, "Pinsk");
		name[0].math = 2;
		name[0].phis = 6;
		name[0].rus = 6;

		strcpy(name[1].lastname, "Azarov");
		strcpy(name[1].place, "Mogilev");
		name[1].math = 9;
		name[1].phis = 10;
		name[1].rus = 8;

		strcpy(name[2].lastname, "Tsaruk");
		strcpy(name[2].place, "Minsk");
		name[2].math = 8;
		name[2].phis = 8;
		name[2].rus = 9;

		strcpy(name[3].lastname, "Borisevich");
		strcpy(name[3].place, "Minsk");
		name[3].math = 3;
		name[3].phis = 8;
		name[3].rus = 7;

		strcpy(name[4].lastname, "Polkhovskiy");
		strcpy(name[4].place, "Pinsk");
		name[4].math = 8;
		name[4].phis = 7;
		name[4].rus = 6;

		strcpy(name[5].lastname, "Moroz");
		strcpy(name[5].place, "Gomel");
		name[5].math = 7;
		name[5].phis = 7;
		name[5].rus = 6;

		strcpy(name[6].lastname, "Prudnikov");
		strcpy(name[6].place, "Klimovichi");
		name[6].math = 3;
		name[6].phis = 4;
		name[6].rus = 3;

		strcpy(name[7].lastname, "Tsandruk");
		strcpy(name[7].place, "TURKMENISTAN");
		name[7].math = 10;
		name[7].phis = 3;
		name[7].rus = 6;

	}

	f1 = fopen("db.txt", "w");
	
	fwrite(name, sizeof(struct studinfo),SIZE,f1);
	
	fclose(f1);
}

void part2()
{
	FILE *f1, *f2;
	struct studinfo name[50];

	f1 = fopen("db.txt", "r");
	fread(name, sizeof(struct studinfo), SIZE, f1);

	printf("Students: \n\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%20s  Place: %12s  Exam: %2d \n", name[i].lastname, name[i].place, name[i].math);
	}

	int good_index = 0;
	int bad_index = 0;
	struct studinfo good[50];
	struct studinfo bad[50];

	//заполнение двух массивов разными перемеными
	for (int i = 0; i < SIZE; i++)
	{
		if (name[i].math > 4)
		{
			good[good_index] = name[i];
			good_index++;
		}
		else
		{
			bad[bad_index] = name[i];
			bad_index++;
		}
	}

	printf("\nStudents with good marks:\n\n\n");
	//вывести хорошие оценки
	for (int i = 0; i < good_index; i++)
	{
		printf("%20s  Place: %12s  Exam: %2d \n", good[i].lastname, good[i].place, good[i].math);
	}

	printf("\nStudents with bad marks:\n\n\n");
	//вывести плохие оценки
	for (int i = 0; i < bad_index; i++)
	{
		printf("%20s  Place: %12s  Exam: %2d \n", bad[i].lastname, bad[i].place, bad[i].math);
	}


	f1 = fopen("db.txt", "w");
	fwrite(good, sizeof(struct studinfo), good_index+1, f1);
	f2 = fopen("baddb.txt", "w");
	fwrite(bad, sizeof(struct studinfo), bad_index+1, f2);

	fclose(f1);
	fclose(f2);

}





void str()
{
	struct studinfo name[50];
	{
		strcpy(name[0].lastname, "Petrushkevich");
		strcpy(name[0].place, "Pinsk");
		name[0].math = 6;
		name[0].phis = 6;
		name[0].rus = 6;

		strcpy(name[1].lastname, "Azarov");
		strcpy(name[1].place, "Mogilev");
		name[1].math = 9;
		name[1].phis = 10;
		name[1].rus = 8;

		strcpy(name[2].lastname, "Tsaruk");
		strcpy(name[2].place, "Minsk");
		name[2].math = 8;
		name[2].phis = 8;
		name[2].rus = 9;

		strcpy(name[3].lastname, "Borisevich");
		strcpy(name[3].place, "Minsk");
		name[3].math = 8;
		name[3].phis = 8;
		name[3].rus = 7;

		strcpy(name[4].lastname, "Polkhovskiy");
		strcpy(name[4].place, "Pinsk");
		name[4].math = 8;
		name[4].phis = 7;
		name[4].rus = 6;

		strcpy(name[5].lastname, "Moroz");
		strcpy(name[5].place, "Gomel");
		name[5].math = 7;
		name[5].phis = 7;
		name[5].rus = 6;

		strcpy(name[6].lastname, "Prudnikov");
		strcpy(name[6].place, "Klimovichi");
		name[6].math = 3;
		name[6].phis = 4;
		name[6].rus = 3;

		strcpy(name[7].lastname, "Tsandruk");
		strcpy(name[7].place, "TURKMENISTAN");
		name[7].math = 10;
		name[7].phis = 3;
		name[7].rus = 6;

	}

	int UniSum = 0;
	int unicount = 0;
	float UniMiddle = 0.0;
	//вывести всех
	for (int i = 0; i < 8; i++)
	{
		UniSum += name[i].math + name[i].phis + name[i].rus;
		unicount += 3;
		name[i].middle = ((float)name[i].math + name[i].phis + name[i].rus) / 3;
		printf("%20s  Place: %12s  Math: %2d  Physics: %2d  Russian: %2d   Middle: %.2f\n", name[i].lastname, name[i].place, name[i].math, name[i].phis, name[i].rus, name[i].middle);
	}
	UniMiddle = (float)UniSum / unicount;
	printf("\n\n");
	printf("  Unvercity middle: %.2f \n", UniMiddle);
	printf("\n\n\n\n");

	//¬ывести всех с 10 и средним баллом больше чем средний
	for (int i = 0; i < 8; i++)
	{
		if ((name[i].middle > UniMiddle) && ((name[i].math == 10) || (name[i].phis == 10) || (name[i].rus == 10)))
			printf("%20s  Place: %12s  Math: %2d  Physics: %2d  Russian: %2d   Middle: %.2f\n", name[i].lastname, name[i].place, name[i].math, name[i].phis, name[i].rus, name[i].middle);
	}

	for (int i = 0; i < 8; i++)
	{
		if ((name[i].middle > UniMiddle) && ((name[i].math != 10) && (name[i].phis != 10) && (name[i].rus != 10)))
			printf("%20s  Place: %12s  Math: %2d  Physics: %2d  Russian: %2d   Middle: %.2f\n", name[i].lastname, name[i].place, name[i].math, name[i].phis, name[i].rus, name[i].middle);
	}





}

