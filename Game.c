#include "Game.h"

SCENE Motion(SCENE sc, int GameState)
{
	if (sc.Ball.State == FALSE)
	{
		sc.Ball.Position.x = sc.Player.Position.x;
	}
	else
	{
		if (sc.Ball.Position.x + sc.Ball.Speed.x > 470 - sc.Ball.radius || sc.Ball.Position.x + sc.Ball.Speed.x < sc.Ball.radius)
		{
			sc.Ball.Speed.x = -sc.Ball.Speed.x;
		}
		if (sc.Ball.Position.y + sc.Ball.Speed.y > 440 - sc.Ball.radius || sc.Ball.Position.y + sc.Ball.Speed.y < sc.Ball.radius || sc.Bon.AdWall == TRUE && sc.Ball.Position.y + sc.Ball.Speed.y > 420 - sc.Ball.radius)
		{
			sc.Ball.Speed.y = -sc.Ball.Speed.y;
		}
		if (sc.Ball.Position.y + sc.Ball.Speed.y >= sc.Player.Position.y - 10 - sc.Ball.radius
			&& sc.Ball.Position.x - sc.Ball.radius <= sc.Player.Position.x + sc.Player.Weigth && sc.Ball.Position.x + sc.Ball.radius >= sc.Player.Position.x - sc.Player.Weigth)
		{
			if (sc.Ball.Position.x > sc.Player.Position.x&& sc.Ball.Position.x <= sc.Player.Position.x + sc.Player.Weigth / 5)
			{
				sc.Ball.Speed.x = 0.26;
				sc.Ball.Speed.y = -0.97;
			}
			if (sc.Ball.Position.x > sc.Player.Position.x + sc.Player.Weigth / 5 && sc.Ball.Position.x <= sc.Player.Position.x + sc.Player.Weigth / 5 * 2)
			{
				sc.Ball.Speed.x = 0.5;
				sc.Ball.Speed.y = -0.87;
			}
			if (sc.Ball.Position.x > sc.Player.Position.x + sc.Player.Weigth / 5 * 2 && sc.Ball.Position.x <= sc.Player.Position.x + sc.Player.Weigth / 5 * 3)
			{
				sc.Ball.Speed.x = 0.71;
				sc.Ball.Speed.y = -0.71;
			}
			if (sc.Ball.Position.x > sc.Player.Position.x + sc.Player.Weigth / 5 * 3 && sc.Ball.Position.x <= sc.Player.Position.x + sc.Player.Weigth / 5 * 4)
			{
				sc.Ball.Speed.x = 0.87;
				sc.Ball.Speed.y = -0.5;
			}
			if (sc.Ball.Position.x > sc.Player.Position.x + sc.Player.Weigth / 5 * 4 && sc.Ball.Position.x - sc.Ball.radius <= sc.Player.Position.x + sc.Player.Weigth)
			{
				sc.Ball.Speed.x = 0.97;
				sc.Ball.Speed.y = -0.26;
			}

			if (sc.Ball.Position.x < sc.Player.Position.x && sc.Ball.Position.x >= sc.Player.Position.x - sc.Player.Weigth / 5)
			{
				sc.Ball.Speed.x = -0.26;
				sc.Ball.Speed.y = -0.97;
			}
			if (sc.Ball.Position.x < sc.Player.Position.x - sc.Player.Weigth / 5 && sc.Ball.Position.x >= sc.Player.Position.x - sc.Player.Weigth / 5 * 2)
			{
				sc.Ball.Speed.x = -0.5;
				sc.Ball.Speed.y = -0.87;
			}
			if (sc.Ball.Position.x < sc.Player.Position.x - sc.Player.Weigth / 5 * 2 && sc.Ball.Position.x >= sc.Player.Position.x - sc.Player.Weigth / 5 * 3)
			{
				sc.Ball.Speed.x = -0.71;
				sc.Ball.Speed.y = -0.71;
			}
			if (sc.Ball.Position.x < sc.Player.Position.x - sc.Player.Weigth / 5 * 3 && sc.Ball.Position.x >= sc.Player.Position.x - sc.Player.Weigth / 5 * 4)
			{
				sc.Ball.Speed.x = -0.87;
				sc.Ball.Speed.y = -0.5;
			}
			if (sc.Ball.Position.x < sc.Player.Position.x - sc.Player.Weigth / 5 * 4 && sc.Ball.Position.x + sc.Ball.radius >= sc.Player.Position.x - sc.Player.Weigth)
			{
				sc.Ball.Speed.x = -0.97;
				sc.Ball.Speed.y = -0.26;
			}

			if (sc.Ball.Position.x == sc.Player.Position.x)
			{
				sc.Ball.Speed.x = 0;
				sc.Ball.Speed.y = -1;
			}
		}
		sc.Ball.Position.x += sc.Ball.Speed.x * sc.Ball.NormalSpeed;
		sc.Ball.Position.y += sc.Ball.Speed.y * sc.Ball.NormalSpeed;

	}

	if (sc.Ball.Position.y > sc.Player.Position.y&& sc.Bon.AdWall != TRUE)
	{
		if (sc.Player.Live != 0)
		{
			sc.Player.Live--;
			sc.Ball.State = FALSE;
			sc.Ball.Position.x = sc.Player.Position.x;
			sc.Ball.Position.y = sc.Player.Position.y - 20;
		}
		else
			GameState = GameOver;
	}
	return sc;
}

SCENE BlockBreak(SCENE sc, int GameState, int NumberLevel)
{
	int CountFalse = 0;
	for (int i = 0; i < sc.Block[0]->Lev.CountY; i++)
	{
		for (int j = 0; j < sc.Block[0]->Lev.CountX; j++)
		{
			if (sc.Ball.Position.y <= sc.Block[i][j].Position.y + 2 * sc.Ball.radius + 2 && sc.Ball.Position.x <= sc.Block[i][j].Position.x + 30 &&
				sc.Ball.Position.x >= sc.Block[i][j].Position.x - 30 && sc.Block[i][j].State != FALSE && sc.Ball.Position.y >= sc.Block[i][j].Position.y - 2 * sc.Ball.radius - 2)
			{
				if (sc.Block[i][j].Bonus != 0 && sc.Block[i][j].Strength == 1)
				{
					sc.Ball.Speed.y = -sc.Ball.Speed.y;
					sc.Block[i][j].State = FALSE;
					sc.Block[i][j].BonusFall = TRUE;
					return sc;
				}
				if (sc.Block[i][j].Strength == 1)
					sc.Block[i][j].State = FALSE;
				else
					sc.Block[i][j].Strength--;
				sc.Ball.Speed.y = -sc.Ball.Speed.y;
				return sc;
			}
			if (sc.Ball.Position.y <= sc.Block[i][j].Position.y + 13 && sc.Block[i][j].State != FALSE && sc.Ball.Position.y >= sc.Block[i][j].Position.y - 10 &&
				(sc.Ball.Position.x + sc.Ball.radius >= sc.Block[i][j].Position.x - 30 && sc.Ball.Position.x - sc.Ball.radius <= sc.Block[i][j].Position.x + 30))
			{
				if (sc.Block[i][j].Bonus != 0 && sc.Block[i][j].Strength == 1)
				{
					sc.Ball.Speed.x = -sc.Ball.Speed.x;
					sc.Block[i][j].State = FALSE;
					sc.Block[i][j].BonusFall = TRUE;
					return sc;
				}
				if (sc.Block[i][j].Strength == 1)
					sc.Block[i][j].State = FALSE;
				else
					sc.Block[i][j].Strength--;
				sc.Ball.Speed.x = -sc.Ball.Speed.x;
				return sc;
			}
			if (sc.Block[i][j].State == FALSE)
			{
				CountFalse++;
			}
		}
	}
	if (CountFalse == sc.Block[0]->Lev.CountX * sc.Block[0]->Lev.CountY)
	{
		NumberLevel++;
		free(sc.Block);
		sc.Block = Level(NumberLevel);
		CountFalse = 0;
		sc.Ball.State = FALSE;
		sc.Ball.Position.x = sc.Player.Position.x;
		sc.Ball.Position.y = sc.Player.Position.y - 20;
		if (NumberLevel == 4)
			GameState = GameWin;
	}
	return sc;
}

//Бонусы:
//0. Ничего
//1. Ускорение мяча
//2. Удлинение игрока
//3. Дополнительная стенка
//4. Пулемет
SCENE Bonus(SCENE sc)
{
	switch (sc.Player.ActiveBonus)
	{
	case 1:
		if (sc.Player.BonusTimer != 0)
		{
			sc.Ball.NormalSpeed = 6;
			sc.Player.BonusTimer--;
		}
		else
			sc.Ball.NormalSpeed = 3;
		break;
	case 2:
		if (sc.Player.BonusTimer != 0)
		{
			sc.Player.Weigth = 60;
			sc.Player.BonusTimer--;
		}
		else
			sc.Player.Weigth = 30;
		break;
	case 3:
		if (sc.Player.BonusTimer != 0)
		{
			sc.Bon.AdWall = TRUE;
			sc.Player.BonusTimer--;
		}
		else
			sc.Bon.AdWall = FALSE;
		break;
	case 4:
		if (sc.Player.BonusTimer == 300)
		{
			sc.Bon.Gun.Shot = malloc(sizeof(SHOT));
			sc.Bon.Gun.CountShot = 0;
			sc.Bon.Gun.State = TRUE;
		}
		sc.Player.BonusTimer--;
		break;
	default:
		break;
	}
	return sc;
}

SCENE MotionBonus(SCENE sc, int GameState)
{
	for (int i = 0; i < sc.Block[0]->Lev.CountY; i++)
	{
		for (int j = 0; j < sc.Block[0]->Lev.CountX; j++)
		{
			if (sc.Block[i][j].BonusFall == TRUE)
				sc.Block[i][j].Position.y++;
			if (sc.Block[i][j].Position.y + 10 >= sc.Player.Position.y && sc.Block[i][j].Position.x + 25 >= sc.Player.Position.x - sc.Player.Weigth && sc.Block[i][j].Position.x - 25 <= sc.Player.Position.x + sc.Player.Weigth)
			{
				sc.Player.BonusTimer = 0;
				Bonus(sc);
				sc.Player.ActiveBonus = sc.Block[i][j].Bonus;
				sc.Block[i][j].BonusFall = FALSE;
				sc.Player.BonusTimer = 300;
				sc.Block[i][j].Position.y -= 10;
			}
			if (sc.Block[i][j].Position.y + 10 >= sc.Player.Position.y)
			{
				sc.Block[i][j].BonusFall = FALSE;
				sc.Block[i][j].Position.y -= 10;
			}
		}
	}
	return sc;
}

void AdditionalWall(HDC memDC)
{
	HPEN GreenPen;
	GreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	SelectObject(memDC, GreenPen);
	MoveToEx(memDC, 0, 420, NULL);
	LineTo(memDC, 480, 420);
	DeleteObject(GreenPen);
}

SCENE Gun(HDC memDC, SCENE sc)
{
	if (sc.Bon.Gun.CountShot >= 0 && (sc.Player.BonusTimer == 299 || sc.Player.BonusTimer == 239 || sc.Player.BonusTimer == 179 || sc.Player.BonusTimer == 119 || sc.Player.BonusTimer == 59))
	{
		sc.Bon.Gun.Shot = realloc(sc.Bon.Gun.Shot, (sc.Bon.Gun.CountShot + 1) * sizeof(SHOT));
		sc.Bon.Gun.Shot[sc.Bon.Gun.CountShot].ShotPos.x = sc.Player.Position.x;
		sc.Bon.Gun.Shot[sc.Bon.Gun.CountShot].ShotPos.y = sc.Player.Position.y - 10;
		sc.Bon.Gun.Shot[sc.Bon.Gun.CountShot].State = TRUE;
		sc.Bon.Gun.CountShot++;
	}
	HPEN BluePen;
	BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	SelectObject(memDC, BluePen);
	for (int i = 0; i < sc.Bon.Gun.CountShot; i++)
	{
		if (sc.Bon.Gun.Shot[i].State != FALSE)
		{
			sc.Bon.Gun.Shot[i].ShotPos.y--;
			MoveToEx(memDC, sc.Bon.Gun.Shot[i].ShotPos.x, sc.Bon.Gun.Shot[i].ShotPos.y, NULL);
			LineTo(memDC, sc.Bon.Gun.Shot[i].ShotPos.x, sc.Bon.Gun.Shot[i].ShotPos.y + 20);
		}

	}

	for (int i = 0; i < sc.Block[0]->Lev.CountY; i++)
	{
		for (int j = 0; j < sc.Block[0]->Lev.CountX; j++)
		{
			for (int k = 0; k < sc.Bon.Gun.CountShot; k++)
				if (sc.Bon.Gun.Shot[k].ShotPos.y <= sc.Block[i][j].Position.y && sc.Bon.Gun.Shot[k].ShotPos.x <= sc.Block[i][j].Position.x + 25 && sc.Bon.Gun.Shot[k].ShotPos.x >= sc.Block[i][j].Position.x - 25 && (sc.Block[i][j].State != FALSE || sc.Block[i][j].State == FALSE && sc.Bon.Gun.Shot[k].ShotPos.y < 5))
				{
					sc.Block[i][j].State = FALSE;
					sc.Bon.Gun.Shot[k].State = FALSE;

				}
		}
	}

	if (sc.Bon.Gun.CountShot == 5 && sc.Bon.Gun.Shot[1].State != TRUE && sc.Bon.Gun.Shot[2].State != TRUE && sc.Bon.Gun.Shot[3].State != TRUE && sc.Bon.Gun.Shot[4].State != TRUE && sc.Bon.Gun.Shot[5].State != TRUE)
	{
		sc.Bon.Gun.State = FALSE;
		free(sc.Bon.Gun.Shot);
	}

	DeleteObject(BluePen);
	return sc;
}
