#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void initial(int bombs[][11]);											//將格子內資訊初始化為0
void show(void);														//印出遊戲初始的格子 
void open(int *x, int *y);												//輸入座標
void putBomb(int bombs[][11], int x, int y);							//放置地雷
void calculateNumOfBombs(int bombs[][11]);								//計算非地雷區附近有幾顆地雷 
void showOpen(int bombs[][11], int x, int y);							//打開所踩位置
void openSurrounding(int bombs[][11], int x, int y);					//打開周圍8格（周圍8格沒地雷）  
void checkNoBomb(int bombs[][11], int x, int y);						//檢查周圍8格有沒有地雷
int  checkOver(int bombs[][11], int x, int y);							//檢查遊戲是否結束
void showCurrentCondition(int bombs[][11], int x, int y, int over);		//顯示目前
void showPlayingCondititon(int bombs[][11]);							//顯示未結束
void showOverCondititon(int bombs[][11], int over);						//遊戲結束(地雷位置)
char playAgain(void);													//再來一次?

int main(void)
{
	int  bombs[11][11], x, y, over;
	char again;

	do
	{
		system("cls");
		initial(bombs);									//將格子內資訊初始化為0
		show();											//印出遊戲初始的格子 
		open(&x, &y);									//輸入座標
		putBomb(bombs, x, y);							//放置地雷
		calculateNumOfBombs(bombs);						//計算非地雷區附近有幾彈地雷
		showOpen(bombs, x, y);							//打開所踩位置
		checkNoBomb(bombs, x, y);						//打開周圍8格（如果周圍8格沒地雷）
		over = checkOver(bombs, x, y);					//檢查遊戲是否結束
		showCurrentCondition(bombs, x, y, over);		//顯示目前
		while (over == 0)
		{
			open(&x, &y);
			showOpen(bombs, x, y);						//輸入座標
			checkNoBomb(bombs, x, y);					//打開周圍8格（如果周圍8格沒地雷）
			over = checkOver(bombs, x, y);				//檢查遊戲是否結束
			showCurrentCondition(bombs, x, y, over);	//顯示目前
		}
		again = playAgain();							//再來一次?
	} while (again == 'Y' || again == 'y');

	return 0;
}

//將格子內資訊初始化為0
void initial(int bombs[][11])
{
	int i, j;
	for (i = 0; i < 11; i++)
	for (j = 0; j < 11; j++)
		bombs[i][j] = 0;
}

//印出遊戲初始的格子 
void show(void)
{
	int i, j;
	printf("              踩地雷\n");
	printf("---------------------------------------\n");
	printf("	不懂規則請先google唷!\n");
	printf("---------------------------------------\n\n");
	printf("    ");
	for (i = 1; i <= 9; i++)
		printf("%2d", i);
	printf("\n");
	for (i = 1; i <= 9; i++)
	{
		for (j = 0; j <= 9; j++)
		{
			if (j == 0)
				printf("%4d", i);
			else
				printf("口");
		}
		printf("\n");
	}
}

//輸入座標
void open(int *x, int *y)
{
	int op_x, op_y;
	printf("\n輸入x,y座標(空白鍵隔開) : ");
	scanf("%d%d", y, x);
}

//放置地雷
void putBomb(int bombs[][11], int x, int y)
{
	srand(time(NULL));          //  亂數種子 
	int  n = 0,
		rand_num,
		bomb_x,
		bomb_y;


	do
	{
		rand_num = rand() % 81;
		bomb_x = (rand_num % 9) + 1;
		bomb_y = ((rand_num - bomb_x) / 9) + 1;
		if (bombs[bomb_x][bomb_y] != -1 && !(bomb_x == x && bomb_y == y))
		{
			bombs[bomb_x][bomb_y] = -1;         //-1 表示地雷
			n++;
		}
	} while (n < 15);      // 地雷數量15顆
}
//計算非地雷區附近有幾顆地雷
void calculateNumOfBombs(int bombs[][11])
{
	int i, j, u, v;
	for (i = 1; i <= 9; i++)
	for (j = 1; j <= 9; j++)
	if (bombs[i][j] == 0)
	for (u = i - 1; u <= i + 1; u++)
	for (v = j - 1; v <= j + 1; v++)
	if (bombs[u][v] == -1)
		bombs[i][j]++;
}

//打開所踩位置
void showOpen(int bombs[][11], int x, int y)
{
	if (bombs[x][y] == -1)
		bombs[x][y] = -2;                //踩到地雷的位置-1改-2(遊戲結束顯示用)

	if (bombs[x][y] >= 0 && bombs[x][y] <= 8)
		bombs[x][y] += 10;				//代表踩過 +10
}

