#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define BASE -777

struct QUEUE //структура очередь
{
	int info;
	struct QUEUE *next;
};


void AddQ(int data, struct QUEUE ** last);
void PrintQ(struct QUEUE ** first);
struct QUEUE *first = NULL, *last = NULL;

struct QUEUE *newfirst = NULL, *newlast = NULL;

void CleanseQ(struct QUEUE ** first);

void main()
{
	int check = 0;
	int data = 0;
	printf("want to add more?(0-no)\n");
	scanf("%d", &check);
	while (check)
	{
		printf("add data:\n");
		scanf("%d", &data);
		AddQ(data, &last);
		printf("want to add more?(0-no)\n");
		scanf("%d", &check);
	}

	PrintQ(first);

	CleanseQ(first);
	PrintQ(first);

	getchar();
	getchar();
}





int EmptyQ(struct QUEUE **first) //проверка пустоты очереди
{
	if ((*first) == NULL)
		return 1;
	else
		return 0;
}

void AddQ(int data,struct QUEUE ** last) //добавление элемента 
{
	if ((*last) != NULL)
	{
		struct QUEUE *temp = (struct QUEUE*) malloc(sizeof(*temp));
		temp->info = data;
		temp->next = NULL;
		(*last)->next = temp;
		(*last) = temp;
	}
	else
	{
		struct QUEUE *temp = (struct QUEUE*) malloc(sizeof(*temp));
		(*last) = temp;
		(*last)->info = data;
		(*last)->next = NULL;
		first = (*last);
	}

	

	
}

void PrintQ(struct QUEUE ** first) 
{
	struct QUEUE *temp = first;
	while ((temp)->next != NULL) 
	{
		if (temp->info != BASE)
		{
			printf("%d ", (temp)->info);
		}
		
		temp = temp->next;
	}
	if (temp->info != BASE)
	{
		printf("%d \n", (temp)->info);
	}
}

void CleanseQ(struct QUEUE ** first)
{
	struct QUEUE *temp = first;
	int count = 1;
	while ((temp)->next != NULL)
	{
		if ((temp->next) != NULL)
		{
			if (temp->next->next != NULL)
			{
				((*temp->next) = *temp->next->next);
				count++;
			}
			
				
		}
		
		
		temp = temp->next;
		
		/*
		if (count % 2 == 0)
		{
			//AddQ(temp->info);
			(*temp) = (*temp->next);
			
		}
		//printf("%d ", (temp)->info);
		if (temp->next != NULL)
		{
			temp = temp->next;
		}
		*/
		count++;
	}
	if (count % 2 == 0) 
	{
		temp->info = BASE;
	}
	//printf("%d \n", temp->info);
}





