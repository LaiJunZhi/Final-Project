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

