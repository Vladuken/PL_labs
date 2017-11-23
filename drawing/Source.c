#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>


#include <windows.h>
#include <conio.h>
#include <math.h>




#define HEIGHT 499
#define WIDTH 949
#define SCALE 2
#define TIMER 200

/*
#define HEIGHT 45
#define WIDTH 45
#define SCALE 10
#define TIMER 0
*/
#define CELL '0'
#define WALL '#'
#define DISTANCE 2
#define VISITED ' '

#define TRUEPATH 'O'
#define FALSEPATH '-'
typedef struct cell
{
	int x;
	int y;
} cell;
void drawmaze(int **maze);
typedef struct cellString 
{
	cell* cells;
	int size;
} cellString;

cellString getNeighbours(int** maze, cell c)
{
	int i = 0;
	int x = c.x;
	int y = c.y;
	cell up = { x, y - DISTANCE };
	cell rt = { x + DISTANCE, y };
	cell dw = { x, y + DISTANCE };
	cell lt = { x - DISTANCE, y };
	cell cell_lst[4] = { dw, rt, up, lt };
    int size = 0;

	cellString cells;
	cells.size=0;
	cells.cells = malloc(4 * sizeof(cell));

	for (int i = 0; i < 4; i++) 
	{ //для каждого направдения
		if (cell_lst[i].x > 0 && cell_lst[i].x < HEIGHT && cell_lst[i].y > 0 && cell_lst[i].y < WIDTH) 
		{ //если не выходит за границы лабиринта
			int mazeCellCurrent = maze[cell_lst[i].x][cell_lst[i].y];
			cell cellCurrent = cell_lst[i];
			if (mazeCellCurrent != WALL && mazeCellCurrent != VISITED) 
			{ //и не посещена\является стеной
				cells.cells[size] = cellCurrent; //записать в массив;
				size++;
			}
		}
	}
	cells.size = size;
	return cells;
}

cellString getFreeNeighbours(int** maze, cell c)
{
	int i = 0;
	int x = c.x;
	int y = c.y;
	cell up = { x, y - (DISTANCE/2) };
	cell rt = { x + (DISTANCE/2), y };
	cell dw = { x, y + (DISTANCE/2) };
	cell lt = { x - (DISTANCE/2), y };
	cell cell_lst[4] = { dw, rt, up, lt };

	cell up2 = { x, y - (DISTANCE) };
	cell rt2 = { x + (DISTANCE), y };
	cell dw2 = { x, y + (DISTANCE) };
	cell lt2 = { x - (DISTANCE), y };
	cell cell_lst2[4] = { dw2, rt2, up2, lt2 };


	int size = 0;

	cellString cells;
	cells.size = 0;
	cells.cells = malloc(4 * sizeof(cell));

	for (int i = 0; i < 4; i++)
	{ //для каждого направдения
		if (cell_lst2[i].x > 0 && cell_lst2[i].x < HEIGHT && cell_lst2[i].y > 0 && cell_lst2[i].y < WIDTH)
		{ //если не выходит за границы лабиринта
			int mazeCellCurrent = maze[cell_lst[i].x][cell_lst[i].y];
			int mazeCellCurrentTrue = maze[cell_lst2[i].x][cell_lst2[i].y];
			cell cellCurrent = cell_lst2[i];
			if (mazeCellCurrent != WALL && mazeCellCurrentTrue == VISITED)
			{ //и не посещена\является стеной
				cells.cells[size] = cellCurrent; //записать в массив;
				size++;
			}
		}
	}
	cells.size = size;
	return cells;
}

typedef struct _node
{
	cell data;
	struct _node *next;
}_node;




void push(_node **head, cell data)
{
	_node *tmp = malloc(sizeof(_node));

	tmp->next = *head;
	tmp->data = data;
	*head = tmp;

}
cell pop(_node **head)
{
	cell tmp;
	tmp = (*head)->data;
	*head = (*head)->next;
	return tmp;
}

void print_maze(int **maze)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
}
int** createmaze()
{
	int **maze;
	maze = (int **)malloc(HEIGHT * sizeof(int*));


	for (int i = 0; i < HEIGHT; i++)
	{
		maze[i] = (int*)malloc(WIDTH * sizeof(int));
	}

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if ((i % 2 != 0 && j % 2 != 0) && //если ячейка нечетная по x и y, 
				(i < HEIGHT - 1 && j < WIDTH - 1))   //и при этом находится в пределах стен лабиринта
				maze[i][j] = CELL;       //то это КЛЕТКА
			else maze[i][j] = WALL;           //в остальных случаях это СТЕНА.
		}
	}

	return maze;
}

int** remove_wall(cell first, cell second, int** maze, int variable)
{
	int xDiff = second.x - first.x;
	int yDiff = second.y - first.y;
	int addX, addY;
	cell target;

	addX = (xDiff != 0) ? (xDiff / abs(xDiff)) : 0;
	addY = (yDiff != 0) ? (yDiff / abs(yDiff)) : 0;

	target.x = first.x + addX;
	target.y = first.y + addY;

	/*
	if (first.x - second.x == 2 || first.x - second.x == -2)
	{
		if (first.x - second.x > 0)
		{
			target_x = first.x + 1;
		}
		else
		{
			target_x = second.x - 1;
		}
	}
	else
	{
		return maze;
	}
	if (first.y - second.y == 2 || first.y - second.y == -2)
	{
		if (first.y - second.y > 0)
		{
			target_x = first.y + 1;
		}
		else
		{
			target_x = second.y - 1;
		}
	}
	else
	{
		return maze;
	}
	*/

	maze[target.x][target.y] = variable; /////////////////////////////
	return maze;
}
int some_unvisited(int **maze)
{
	int count = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (maze[i][j] == '0')
			{
				return 1;
			}
		}
	}
	return 0;
}




int **finish_maze(int **maze)
{

	//maze = remove_wall(startcell,fff,maze);


	//push(&head, startcell);
	//printf("%d", pop(&head).y);
	_node *head = NULL;
	cell startCell = { 1,1 };
	cell currentCell = startCell;
	cell neighbourCell;
	int randNum = 0;
	int x = 0;
	do
	{
		cellString Neighbours = getNeighbours(maze, currentCell);
		if (Neighbours.size)
		{
			randNum = rand() % (Neighbours.size);
			neighbourCell = Neighbours.cells[randNum];
			push(&head, currentCell);
			maze = remove_wall(currentCell, neighbourCell, maze,VISITED);

			maze[currentCell.x][currentCell.y] = VISITED;
			maze[neighbourCell.x][neighbourCell.y] = VISITED;
			currentCell = neighbourCell;

			free(Neighbours.cells);
		}
		else
		{
			if (head)
			{
				currentCell = pop(&head);
			}
		}
		//printf("\n\n\n\n\n");
		//print_maze(maze);

		x++;
	} while (some_unvisited(maze));

	return maze;
}


int **find_exit(int **maze)
{

	//maze = remove_wall(startcell,fff,maze);


	//push(&head, startcell);
	//printf("%d", pop(&head).y);
	_node *head = NULL;
	cell startCell = { 1,1 };
	cell endCell = {HEIGHT -2, WIDTH - 2};

	cell currentCell = startCell;
	cell neighbourCell;
	int randNum = 0;
	do
	{
		cellString Neighbours = getFreeNeighbours(maze, currentCell);
		if (Neighbours.size)
		{
			randNum = rand() % (Neighbours.size);
			neighbourCell = Neighbours.cells[randNum];
			push(&head, currentCell);
			
			maze[currentCell.x][currentCell.y] = TRUEPATH;
			maze[neighbourCell.x][neighbourCell.y] = TRUEPATH;
			maze = remove_wall(currentCell, neighbourCell, maze, TRUEPATH);
			currentCell = neighbourCell;

			free(Neighbours.cells);
		}
		else
		{
			if (head)
			{
				maze[currentCell.x][currentCell.y] = FALSEPATH;
				//maze = remove_wall(currentCell, neighbourCell, maze, FALSEPATH);
				neighbourCell = pop(&head);
				maze = remove_wall(currentCell, neighbourCell, maze, FALSEPATH);
				currentCell = neighbourCell;
			}
		}
		//printf("\n\n\n\n\n");
		//drawmaze(maze);
		//Sleep(5);
	} while ((currentCell.x != endCell.x) || (currentCell.y != endCell.y));
	//print_maze(maze);
	return maze;
}


void drawmaze(int **maze)
{
	HWND hwnd;
	char Title[1024];
	GetConsoleTitle(Title, 1024); // Узнаем имя окна
	hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна
	HDC hdc = GetDC(hwnd);    // Получаем контекст для рисования

	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	Sleep(TIMER);
	HBRUSH whitebrush = CreateSolidBrush(RGB(255, 255, 255)); // Создаем белую кисть
	HBRUSH blackbrush = CreateSolidBrush(RGB(0, 0, 0)); // Создаем белую кисть
	HBRUSH bluebrush = CreateSolidBrush(RGB(0, 0, 255)); // Создаем белую кисть
	HBRUSH redbrush = CreateSolidBrush(RGB(255, 0, 0)); // Создаем белую кисть
	
	HPEN whitepen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // Создаем красное перо
	HPEN blackpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Создаем красное перо
	HPEN bluepen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255)); // Создаем красное перо
	HPEN redpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // Создаем красное перо
	
	HPEN activepen = (HPEN)SelectObject(hdc, whitepen);
	HBRUSH active = (HBRUSH)SelectObject(hdc, whitebrush);
	//Rectangle(hdc, 0, 0, 1920, 1080);//Рисуем прямоугольник

	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			switch (maze[i][j])
			{
			case WALL:
				activepen = (HPEN)SelectObject(hdc, blackpen);
				active = (HBRUSH)SelectObject(hdc, blackbrush);
				Rectangle(hdc, j * SCALE, i * SCALE, j * SCALE + SCALE, i * SCALE + SCALE);//Рисуем прямоугольник
				break;
			case VISITED:
				activepen = (HPEN)SelectObject(hdc, whitepen);
				active = (HBRUSH)SelectObject(hdc, whitebrush);
				Rectangle(hdc, j * SCALE, i * SCALE, j * SCALE + SCALE, i * SCALE + SCALE);//Рисуем прямоугольник
				break;
			case TRUEPATH:
				activepen = (HPEN)SelectObject(hdc, redpen);
				active = (HBRUSH)SelectObject(hdc, redbrush);
				Rectangle(hdc, j * SCALE, i * SCALE, j * SCALE + SCALE, i * SCALE + SCALE);//Рисуем прямоугольник
				break;
			case FALSEPATH:
				activepen = (HPEN)SelectObject(hdc, bluepen);
				active = (HBRUSH)SelectObject(hdc, bluebrush);
				Rectangle(hdc, j * SCALE, i * SCALE, j * SCALE + SCALE, i * SCALE + SCALE);//Рисуем прямоугольник
				break;
			}
		}
	}

	ReleaseDC(hwnd, hdc);    // Освобождаем контекст рисования
							 //DeleteObject(p2);       // Удаляем созданное перо
							 //DeleteObject(b2);       // Удаляем созданную кисть
	//_getch();
}

int main()
{
	srand(time(NULL));
	int **maze = createmaze();
	maze = finish_maze(maze);
	//print_maze(maze);
	//printf("\n\n\n\n\n");
	maze = find_exit(maze);
	//print_maze(maze);
	drawmaze(maze);

	

	getchar();
}

