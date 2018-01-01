#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void initial(int bombs[][11]);											//�N��l����T��l�Ƭ�0
void show(void);														//�L�X�C����l����l 
void open(int *x, int *y);												//��J�y��
void putBomb(int bombs[][11], int x, int y);							//��m�a�p
void calculateNumOfBombs(int bombs[][11]);								//�p��D�a�p�Ϫ��񦳴X���a�p 
void showOpen(int bombs[][11], int x, int y);							//���}�ҽ��m
void openSurrounding(int bombs[][11], int x, int y);					//���}�P��8��]�P��8��S�a�p�^  
void checkNoBomb(int bombs[][11], int x, int y);						//�ˬd�P��8�榳�S���a�p
int  checkOver(int bombs[][11], int x, int y);							//�ˬd�C���O�_����
void showCurrentCondition(int bombs[][11], int x, int y, int over);		//��ܥثe
void showPlayingCondititon(int bombs[][11]);							//��ܥ�����
void showOverCondititon(int bombs[][11], int over);						//�C������(�a�p��m)
char playAgain(void);													//�A�Ӥ@��?

int main(void)
{
	int  bombs[11][11], x, y, over;
	char again;

	do
	{
		system("cls");
		initial(bombs);									//�N��l����T��l�Ƭ�0
		show();											//�L�X�C����l����l 
		open(&x, &y);									//��J�y��
		putBomb(bombs, x, y);							//��m�a�p
		calculateNumOfBombs(bombs);						//�p��D�a�p�Ϫ��񦳴X�u�a�p
		showOpen(bombs, x, y);							//���}�ҽ��m
		checkNoBomb(bombs, x, y);						//���}�P��8��]�p�G�P��8��S�a�p�^
		over = checkOver(bombs, x, y);					//�ˬd�C���O�_����
		showCurrentCondition(bombs, x, y, over);		//��ܥثe
		while (over == 0)
		{
			open(&x, &y);
			showOpen(bombs, x, y);						//��J�y��
			checkNoBomb(bombs, x, y);					//���}�P��8��]�p�G�P��8��S�a�p�^
			over = checkOver(bombs, x, y);				//�ˬd�C���O�_����
			showCurrentCondition(bombs, x, y, over);	//��ܥثe
		}
		again = playAgain();							//�A�Ӥ@��?
	} while (again == 'Y' || again == 'y');

	return 0;
}

//�N��l����T��l�Ƭ�0
void initial(int bombs[][11])
{
	int i, j;
	for (i = 0; i < 11; i++)
	for (j = 0; j < 11; j++)
		bombs[i][j] = 0;
}

//�L�X�C����l����l 
void show(void)
{
	int i, j;
	printf("              ��a�p\n");
	printf("---------------------------------------\n");
	printf("	�����W�h�Х�google��!\n");
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
				printf("�f");
		}
		printf("\n");
	}
}

//��J�y��
void open(int *x, int *y)
{
	int op_x, op_y;
	printf("\n��Jx,y�y��(�ť���j�}) : ");
	scanf("%d%d", y, x);
}

//��m�a�p
void putBomb(int bombs[][11], int x, int y)
{
	srand(time(NULL));          //  �üƺؤl 
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
			bombs[bomb_x][bomb_y] = -1;         //-1 ��ܦa�p
			n++;
		}
	} while (n < 15);      // �a�p�ƶq15��
}
//�p��D�a�p�Ϫ��񦳴X���a�p
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

//���}�ҽ��m
void showOpen(int bombs[][11], int x, int y)
{
	if (bombs[x][y] == -1)
		bombs[x][y] = -2;                //���a�p����m-1��-2(�C��������ܥ�)

	if (bombs[x][y] >= 0 && bombs[x][y] <= 8)
		bombs[x][y] += 10;				//�N���L +10
}

