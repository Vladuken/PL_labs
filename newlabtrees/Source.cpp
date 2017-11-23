// file.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdio.h"
#include "string.h"
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#define MAX_LEN 256

//���������� ��������� ������, ��� ����� � ������� � ����� ��� �������

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
//  �������������� ������ �������. ��������� �� ��������� � ����������� (� �������� �������� ������)
//
//  ����� ����������, ���������� ���������: +,-,*,/,(,),^; ��� �������� ����� ������� ����-��������������
//  ��� �������� - ��������������
//
void PostfixNotation(const char *_infix, char *_postfix)
{
	char stack[MAX_LEN];    // ���� ��� �������� ���������� ��� ��������������
	int st_ptr = 0;             // ��������� ������� �����

	int out_index = 0;      // ������ � �������� ������
	int in_index = 0;       // ������ �� ������� ������

							// �������� ������ �������� ������ (��� �� ������ ���� ������)
	do
	{
		char c = _infix[in_index];  // ����� ������� ������ ������� ������

		switch (c)
		{
		case '+':
		case '-':
			// ����������� �� ����� � �������� ������ ��� ��������� � ������� ��� ������ �����������
			while (st_ptr != 0)
			{
				char op = stack[st_ptr - 1];    // �������� � ������� �����
				if (op != '(')  // ��� ���������, ����� ����. ������ ����� ������� ��� ������ ���������
				{
					_postfix[out_index++] = op; // ��������� �������� � �������� ������
					pop(stack, st_ptr);         // ������� �������� �� �����
				}
				else
					break;
			}
			// �������� �������� � ����
			push(stack, st_ptr, c);
			break;

		case '*':
		case '/':
			// ����������� �� ����� � �������� ������ ��� ��������� � ������� ��� ������ �����������
			while (st_ptr != 0)
			{
				char op = stack[st_ptr - 1];
				if ((op == '^') || (op == '*') || (op == '/'))
				{
					_postfix[out_index++] = op; // ��������� �������� � �������� ������
					pop(stack, st_ptr);         // ������� �������� �� �����
				}
				else
					break;
			}
			// �������� �������� � ����
			push(stack, st_ptr, c);
			break;

		case '(':
			// ������ �������� � ����
			push(stack, st_ptr, c);
			break;

		case ')':
			// ����������� �� ����� � �������� ������ ��� �������� �� ����������� ������ (����. ������ ������ �����������)
			while (st_ptr != 0)
			{
				char op = pop(stack, st_ptr);   // �������� �� ����� ��������
				if (op == '(')                  // ���� �������� ����������� ������
					break;                      // ������������ ���������
				else
				{
					_postfix[out_index++] = op; // �������� �������� � �������� ������
				}
			}
			break;

		case '^':
			// �������� �������� � ���� (����������� ������ �� �����, ��� ���������� � ������� �����������)
			push(stack, st_ptr, c);
			break;

		default:        // ������ �����
			_postfix[out_index] = c;    // ��������� ����� � �������� ������
			out_index++;
			break;
		}

		in_index++; // ��������� � ���������� ������� ������� ������
	} while (_infix[in_index] != 0);    // ������ ��������

										// ����������� ��� ��������� � �������� ������
	while (st_ptr != 0)
		_postfix[out_index++] = pop(stack, st_ptr);

	// ����������� ������ ����
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

	printf("��������� �������:\n");
	printf("%s\n", str_infix);

	PostfixNotation(str_infix, str_postfix);
	

	treeType* tree = createBinTree(str_postfix);
	//writeTree(tree->next);
	printf("������ (�������������� ���):\n");
	print_Tree(tree->next, 0);
	printf("\n����������� ������� (�������� �������� ������):\n");
	printf("%s\n", str_postfix);
	
	getchar();
	return 0;
}