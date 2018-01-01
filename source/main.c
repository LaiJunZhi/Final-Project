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

//打開周圍8格（周圍8格沒地雷） 
void openSurrounding(int bombs[][11], int x, int y)
{
	int i, j;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (bombs[i][j] >= 0 && bombs[i][j] <= 8 && i % 10 != 0 && j % 10 != 0)
			{
				bombs[i][j] += 10;
				checkNoBomb(bombs, i, j);
			}
		}
	}
}

//檢查周圍8格有沒有地雷
void checkNoBomb(int bombs[][11], int x, int y)
{
	if (bombs[x][y] == 10)        //10表示 周圍8格沒地雷 
		openSurrounding(bombs, x, y);
}

//檢查遊戲是否結束
int  checkOver(int bombs[][11], int x, int y)
{
	//result == 0 ->尚未結束，result == 1 ->贏，result == -1 ->輸
	int i, j, result = 1;
	if (bombs[x][y] == -2)        //輸入座標而踩到地雷的位置-2
	{
		result = -1;
	}
	else
	{
		for (i = 1; i <= 9 && result == 1; i++)
			for (j = 1; j <= 9 && result == 1; j++)
				if ((bombs[i][j] >= 0 && bombs[i][j] <= 8))   //沒踩出來的沒+10，代表還沒結束
					result = 0;
	}
	return result;
}
//顯示目前
void showCurrentCondition(int bombs[][11], int x, int y, int over)
{
	system("cls");
	printf("\n");
	int i, j;
	if (over == 0)
	{
		showPlayingCondititon(bombs);
	}
	else
	{
		showOverCondititon(bombs, over);
	}

}

//顯示未結束
void showPlayingCondititon(int bombs[][11])
{
	int i, j;
	printf("      ");
	for (i = 1; i <= 9; i++)
		printf("%2d", i);

	printf("\n    ┌－－－－－－－－－┐\n");

	for (i = 1; i <= 9; i++)
	{
		for (j = 0; j <= 9; j++)
		{
			if (j == 0)
				printf("%4d｜", i);
			else if (bombs[i][j] < 10)
				printf("口");
			else if (bombs[i][j] == 10)
				printf(" 0");
			else if (bombs[i][j] > 10 && bombs[i][j] <= 18)
				printf(" %d", bombs[i][j] - 10);  //前面有+10 印出-10的情形 顯示用
			if (j == 9)
				printf("｜%d", i);
		}
		printf("\n");
	}

	printf("    └－－－－－－－－－┘\n");
	printf("      ");

	for (i = 1; i <= 9; i++)
		printf("%2d", i);

	printf("\n");
}

//遊戲結束
void showOverCondititon(int bombs[][11], int over)
{
	int i, j;

	printf("  ┌－－－－－－－－－┐\n");

	for (i = 1; i <= 9; i++)
	{
		for (j = 0; j <= 10; j++)
		{
			if (j == 0)
				printf("  ｜");
			else if (j == 10)
				printf("｜");
			else if (bombs[i][j] % 10 == 0)
				printf("．");
			else if (bombs[i][j] == -1)
				printf(" *");
			else if (bombs[i][j] == -2)
				printf("⊕");
			else
				printf("%2d", bombs[i][j] % 10);
		}
		printf("\n");
	}

	printf("  └－－－－－－－－－┘\n");

	if (over == 1)
		printf("你竟然沒踩到地雷！\n\n");
	else
		printf("蹦…… \n\n");

	printf("數字代表周圍八格地雷總數量\n");
	printf("*代表地雷\n");
	printf("．代表周圍沒地雷\n");
	printf("⊕代表爆掉的地雷。\n");
}

//再來一次?
char playAgain(void)
{
	char again;

	do
	{
		printf("\n再來一次？(Y/N)  >>");
		scanf(" %c", &again);
	} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');

	return(again);
}
