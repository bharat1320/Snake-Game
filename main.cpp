#include<iostream>
#include<thread>
#include<conio.h>		//to use _getch
#include<cstdlib>		//to use rand
#include<ctime>			//to use time() in srand

#define up 72
#define down 80
#define left 75
#define right 77

using namespace std;

const int length = 20;
const int breath = length*2;
char food = 'f';
static bool gameCONTINUITY = 1;
static char a[length][breath];
char snake = 'S';
long score = -1;
char name[30];

void moveup();
void movedown();
void moveleft();
void moveright();
auto snakeDIRECTION = moveleft; //this is the function poinnter keeping track of current direction..
auto SPEED = 0.5s;
//using lists so that snake body is organized after several turns..

struct list
{
public:
	int x;
	int y;
	list* next = NULL;
};
list* head = new list;
list* tail = NULL;
list* spare = NULL;

// PRIMITIVE FUNCTIONS

void display()
{
	while (gameCONTINUITY)
	{
		cout << "\n-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-    ITS  < -:" << name << ":- >  YOU BIT** ";
		cout << "    -|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-\n\n";
		for (int i = 0; i < length; i++)
			printf("					%s\n", &a[i]);
		cout <<"\n\n\t\t\t\t\t\t      SCORE :- "<< score;
		system("CLS");	//clear screen
	}
}

inline int input()
{
	int ch;
	ch = _getch();
	if (ch == 224)
		ch = _getch();
	return ch;
}

void newFOOD()
{
	float found = 1;
	int x, y;
	srand(time(0));
	while (found)
	{
		x = (rand() % (length-3)) + 1;
		y = (rand() % (breath-3)) + 1;
		if (a[x][y] == ' ')
		{
			a[x][y] = food;
			found = 0;
		}
	}
	score++;	//this keeps updating the score
}

void initialize()
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < breath - 1; j++)
		{
			if (i == 0 || i == length - 1 || j == 0 || j == breath - 2)
				a[i][j] = '#';
			else
				a[i][j] = ' ';
		}
		a[i][breath - 1] = '\0';
	}
}

void moveup()
{
	if (a[(head->x) - 1][head->y] == '#' || a[(head->x) - 1][head->y] == snake)
		gameCONTINUITY = 0;
	else if (a[(head->x) - 1][head->y] == food)
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x) - 1;
		head->y = (spare->y);
		a[head->x][head->y] = snake;
		newFOOD();
	}
	else
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x) - 1;
		head->y = (spare->y);
		a[head->x][head->y] = snake;
		a[tail->x][tail->y] = ' ';
		tail = tail->next;
	}
}

void movedown()
{
	if (a[(head->x) + 1][head->y] == '#' || a[(head->x) + 1][head->y] == snake)
		gameCONTINUITY = 0;
	else if (a[(head->x) + 1][head->y] == food)
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x) + 1;
		head->y = (spare->y);
		a[head->x][head->y] = snake;
		newFOOD();
	}
	else
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x) + 1;
		head->y = (spare->y);
		a[head->x][head->y] = snake;
		a[tail->x][tail->y] = ' ';
		tail = tail->next;
	}
}

void moveleft()
{
	if (a[head->x][(head->y) - 1] == '#' || a[head->x][(head->y) - 1] == snake)
		gameCONTINUITY = 0;
	else if (a[head->x][(head->y) - 1] == food)
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x);
		head->y = (spare->y) - 1;
		a[head->x][head->y] = snake;
		newFOOD();
	}
	else
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x);
		head->y = (spare->y) - 1;
		a[head->x][head->y] = snake;
		a[tail->x][tail->y] = ' ';
		tail = tail->next;
	}
}

void moveright()
{
	if (a[head->x][(head->y) + 1] == '#' || a[head->x][(head->y) + 1] == snake)
		gameCONTINUITY = 0;
	else if (a[head->x][(head->y) + 1] == food)
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x);
		head->y = (spare->y) + 1;
		a[head->x][head->y] = snake;
		newFOOD();
	}
	else
	{
		spare = head;
		head = new list;
		spare->next = head;
		head->x = (spare->x);
		head->y = (spare->y) + 1;
		a[head->x][head->y] = snake;
		a[tail->x][tail->y] = ' ';
		tail = tail->next;
	}
}

void direction()
{
	while (gameCONTINUITY)
	{
		switch (input())
		{
		case up:	if (snakeDIRECTION != movedown || head == tail) { snakeDIRECTION = moveup; }
					break;
		case down:	if (snakeDIRECTION != moveup || head==tail) { snakeDIRECTION = movedown; }
					break;
		case left:	if (snakeDIRECTION != moveright || head==tail) { snakeDIRECTION = moveleft; }
					break;
		case right:	if (snakeDIRECTION != moveleft || head == tail) { snakeDIRECTION = moveright; }
					break;
		}
	}
}

void rungame()
{
	initialize();
	head->x = length / 2;	//initialized the snake head
	head->y = breath / 2;	//initialized the snake head
	tail = head;
	newFOOD();
	thread display_THREAD(display);
	//down is the lambda function for running the code faster
	thread moveSNAKE_THREAD([]() {while (gameCONTINUITY) { snakeDIRECTION();	this_thread::sleep_for(SPEED); }	}); 
	thread direction_THREAD(direction);
	direction_THREAD.join();
	moveSNAKE_THREAD.join();
	display_THREAD.join();
}

int main()
{
	while (gameCONTINUITY)
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tWHATS YOUR NAME BUDDY : )  ";
		cin >> name;
		system("CLS");

		rungame();
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t( ; WELL HAI LAUNDE ; )  ";
	}

}

//expansion of lambda function moveSNAKE()
//inline void moveSNAKE()
//{
//	while (gameCONTINUITY)
//	{	
//		snakeDIRECTION();
//		this_thread::sleep_for(SPEED);
//	}
//} 

/*thread commands :-
* start a thread
thread threadNAME(function, parameter 1,parameter 2,....);
*join a thread
threadNAME.join();
*sleep thread
this_thread::sleep_for(1.5s);
*/
