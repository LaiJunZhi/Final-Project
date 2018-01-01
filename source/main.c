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

