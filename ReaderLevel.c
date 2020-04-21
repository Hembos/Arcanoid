#include "Game.h"

BLOCK** Level(int NumberLevel)
{
	BLOCK** Block;
	FILE* fp;
	char c;
	int i = 0, j = 0;
	char Level[6];
	int x, y;
	fopen_s(&fp, "Text.txt", "r");
	if (fp == NULL)
	{
		exit(1);
	}
	for (; ; )
	{
		fgets(Level, 6, fp);
		if (!strcmp(Level, "Level"))
		{
			fseek(fp, 2, SEEK_CUR);
			c = (char)fgetc(fp);
			if (atoi(&c) == NumberLevel)
			{
				fseek(fp, 3, SEEK_CUR);
				c = (char)fgetc(fp);
				y = atoi(&c);
				fseek(fp, 1, SEEK_CUR);
				c = (char)fgetc(fp);
				x = atoi(&c);
				fseek(fp, 3, SEEK_CUR);
				break;
			}
			continue;
		}

	}



	Block = (BLOCK**)malloc(y * sizeof(BLOCK));
	if (Block == NULL)
		exit(1);

	for (int i = 0; i < y; i++)
	{
		Block[i] = (BLOCK*)malloc(x * sizeof(BLOCK));
		if (Block[i] == NULL)
			exit(1);
	}

	Block[0]->Lev.CountY = y;
	Block[0]->Lev.CountX = x;

	while ((c = fgetc(fp)) != EOF && c != 'L')
	{
		if (c == ',')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				Block[i][j++].Bonus = 0;
				break;
			case '1':
				Block[i][j++].Bonus = 1;
				break;
			case '2':
				Block[i][j++].Bonus = 2;
				break;
			case '3':
				Block[i][j++].Bonus = 3;
				break;
			case '4':
				Block[i][j++].Bonus = 4;
			default:
				break;
			}
			continue;
		}

		switch (c)
		{
		case '0':
			Block[i][j].State = FALSE;
			break;
		case '1':
			Block[i][j].State = TRUE;
			Block[i][j].Strength = 1;
			break;
		case '2':
			Block[i][j].State = TRUE;
			Block[i][j].Strength = 2;
			break;
		default:
			break;
		}
		if (j == 8 && c == '\n')
		{
			i++;
			j = 0;
		}

	}

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			Block[i][j].BonusFall = FALSE;
			Block[i][j].Position.x = (double)j * 50 + 60;
			Block[i][j].Position.y = (double)i * 20 + 10;
		}
	}

	fclose(fp);
	return Block;
}
