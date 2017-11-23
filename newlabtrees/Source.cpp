// file.cpp: определяет точку входа для консольного приложения.
//

#include "stdio.h"
#include "string.h"
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#define MAX_LEN 256

//построение бинарного дерева, его вывод в консоль и вывод его листьев

typedef char dataType;

typedef struct _tree
{
	struct _tree *leftTree, *rightTree, *next;
	dataType data;
} treeType;

void addToTree(treeType **tree, dataType data)
{
	if (*tree == NULL)
	{
		*tree = (treeType *)calloc(1, sizeof(treeType));
		(**tree).data = data;
	}
	else
	{
		if ((**tree).leftTree == NULL)
		{
			addToTree(&(**tree).leftTree, data);
		}
		else if ((**tree).rightTree == NULL)
		{
			addToTree(&(**tree).rightTree, data);
		}
		else
		{
			*tree = (treeType *)calloc(1, sizeof(treeType));
			(**tree).data = data;
		}
	}
}

void addBinTree(treeType **tree, dataType data)
{
	if (*tree == NULL)
	{
		*tree = (treeType *)calloc(1, sizeof(treeType));
		(**tree).data = data;
	}
	else
	{
		if (data < (**tree).data)
			addBinTree(&(**tree).leftTree, data);
		if (data >(**tree).data)
			addBinTree(&(**tree).rightTree, data);
	}
}

treeType* createBinTree(char *s)
{
	treeType *tree = NULL;
	treeType *stack = NULL;
	treeType *buff = NULL;
	for (int i = 0; i <= strlen(s); i++)
	{
		buff = (treeType *)calloc(1, sizeof(treeType));
		buff->data = s[i];
		if ((s[i] == '+') || (s[i] == '-') || s[i] == '*' || s[i] == '/' || s[i] == '^')
		{
			buff->rightTree = stack;
			buff->leftTree = stack->next;
			buff->next = stack->next->next;
			stack = buff;
		}
		else
		{
			buff->rightTree = NULL;
			buff->leftTree = NULL;
			buff->next = stack;
			stack = buff;
		}
	}
	return stack;
}


void writeTree(treeType *tree)
{
	treeType *queue[200];
	treeType *temp;
	int start, end, level = 1;
	start = 0;
	end = 0;

	treeType nullTree;
	nullTree.data = ' ';
	int isEnd = 0;

	queue[end++] = tree;
	while (start != end && !isEnd)
	{
		temp = queue[start++];
		if (start == level)
		{
			printf("\n");
			level *= 2;
		}

		queue[end++] = (temp != NULL && temp != &nullTree && temp->leftTree != NULL) ? temp->leftTree : &nullTree;
		queue[end++] = (temp != NULL && temp != &nullTree && temp->rightTree != NULL) ? temp->rightTree : &nullTree;

		isEnd = 1;
		for (int i = start; i < end && isEnd; i++)
			isEnd = queue[i] == &nullTree || queue[i] == NULL;

		for (int i = 0; i < 100 / (level / 2 + 1); i++)
			printf(" ");
		if (temp->data == ' ')
			printf("%c", temp->data);
		else
			printf("%c", temp->data);
	}
}
	


void print_Tree(treeType *p, int level)
{
	if (p)
	{
		print_Tree(p->rightTree, level + 1);
		for (int i = 0; i< level; i++) printf("   ");
		printf("%c\n", (p->data));
		print_Tree(p->leftTree, level + 1);
	}
}
//



void push(char *_stack, int &_ptr, char data);
char pop(char *_stack, int &_ptr);


//
//  Преобразование записи математ. выражения из инфиксной в постфиксную (в обратную польскую запись)
//
//  Сразу оговоримся, допустимые операторы: +,-,*,/,(,),^; все операции будем считать лево-ассоциативными
//  Все операнды - односимвольные
//
void PostfixNotation(const char *_infix, char *_postfix)
{
	char stack[MAX_LEN];    // стек для хранения операторов при преобразовании
	int st_ptr = 0;             // указатель вершины стека

	int out_index = 0;      // индекс в выходной строке
	int in_index = 0;       // индекс во входной строке

							// начинаем разбор входящей строки (она не должна быть пустой)
	do
	{
		char c = _infix[in_index];  // берем текущий символ входной строки

		switch (c)
		{
		case '+':
		case '-':
			// выталкиваем из стека в выходную строку все операторы с большим или равным приоритетом
			while (st_ptr != 0)
			{
				char op = stack[st_ptr - 1];    // оператор в вершине стека
				if (op != '(')  // все операторы, кроме откр. скобки имеют больший или равный приоритет
				{
					_postfix[out_index++] = op; // добавляем оператор в выходную строку
					pop(stack, st_ptr);         // удаляем оператор из стека
				}
				else
					break;
			}
			// помещаем оператор в стек
			push(stack, st_ptr, c);
			break;

		case '*':
		case '/':
			// выталкиваем из стека в выходную строку все операторы с большим или равным приоритетом
			while (st_ptr != 0)
			{
				char op = stack[st_ptr - 1];
				if ((op == '^') || (op == '*') || (op == '/'))
				{
					_postfix[out_index++] = op; // добавляем оператор в выходную строку
					pop(stack, st_ptr);         // удаляем оператор из стека
				}
				else
					break;
			}
			// помещаем оператор в стек
			push(stack, st_ptr, c);
			break;

		case '(':
			// просто помещаем в стек
			push(stack, st_ptr, c);
			break;

		case ')':
			// выталкиваем из стека в выходную строку все элементы до открывающей скобки (откр. скобку просто отбрасываем)
			while (st_ptr != 0)
			{
				char op = pop(stack, st_ptr);   // забираем из стека оператор
				if (op == '(')                  // если достигли открывающей скобки
					break;                      // выталкивание закончили
				else
				{
					_postfix[out_index++] = op; // добавили оператор в выходную строку
				}
			}
			break;

		case '^':
			// помещаем оператор в стек (выталкивать ничего не нужно, нет операторов с большим приоритетом)
			push(stack, st_ptr, c);
			break;

		default:        // символ цифры
			_postfix[out_index] = c;    // добавляем цифру в выходную строку
			out_index++;
			break;
		}

		in_index++; // переходим к следующему символу входной строки
	} while (_infix[in_index] != 0);    // разбор закончен

										// выталкиваем все операторы в выходную строку
	while (st_ptr != 0)
		_postfix[out_index++] = pop(stack, st_ptr);

	// завершающий символ нуля
	_postfix[out_index] = 0;
}


void push(char *_stack, int &_ptr, char data)
{
	_stack[_ptr++] = data;
}

char pop(char *_stack, int &_ptr)
{
	return _stack[--_ptr];
}


int main()
{
	setlocale(LC_ALL, "Rus");
	char str_infix[] = "a*(q+b*c*(y-g+d)^n^k+s*l)/x-f*(t*p+w)";
	//char str_infix[] = "x*y+c*b*(d-a)";

	char str_postfix[MAX_LEN];
	char reverced_str[MAX_LEN];

	printf("Инфиксная нотация:\n");
	printf("%s\n", str_infix);

	PostfixNotation(str_infix, str_postfix);
	

	treeType* tree = createBinTree(str_postfix);
	//writeTree(tree->next);
	printf("Дерево (горизонтальный вид):\n");
	print_Tree(tree->next, 0);
	printf("\nПостфиксная нотация (обратная польская запись):\n");
	printf("%s\n", str_postfix);
	
	getchar();
	return 0;
}