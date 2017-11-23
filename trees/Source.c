#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>


typedef int dataType;

typedef struct _tree
{
	struct _tree *leftTree, *rightTree;
	dataType data;
} treeType;



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
		if (data > (**tree).data)
			addBinTree(&(**tree).rightTree, data);
	}
}

treeType* createBinTree()
{
	treeType *tree = NULL;
	int count;
	printf("Введите количество элементов дерева: ");
	scanf_s("%d", &count);

	dataType element;
	for (int i = 0; i < count; i++)
	{
		printf("%d%s", i + 1, " элемент дерева:\n");
		scanf_s("%d", &element);
		addBinTree(&tree, element);
	}
	return tree;
}


void writeTree(treeType *tree)
{
	treeType *queue[100];
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

		for (int i = 0; i < 60 / (level / 2 + 1); i++)
			printf(" ");
		if (temp->data == ' ')
			printf("%c", temp->data);
		else
			printf("%d", temp->data);
	}
}

void writeTreeLeaves(treeType **tree)
{
	if (!(*tree == NULL))
	{
		if ((**tree).leftTree == NULL && ((**tree).rightTree == NULL))
		{
			printf("%d  ", (**tree).data);
		}

		writeTreeLeaves(&(**tree).leftTree);
		writeTreeLeaves(&(**tree).rightTree);

	}	
	
	
}

int main()
{
	setlocale(LC_ALL, "Rus");
	treeType *tree = createBinTree();
	printf("Введенное дерево:\n");
	writeTree(tree);
	printf("\n\n\n");

	
	getchar();
	getchar();
}
