#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

char szClassName[] = "Window1";
HWND hWnd;
PAINTSTRUCT ps;
HDC hdc;
HDC memDC;
int click = 0;
int NumberLevel = 1;

PLAYER Player;
BALL Ball;
GAME Game;
MENU Menu;
BONUS Bon;
BLOCK** Block;
HBITMAP memBM;
BOOL isDrawing = TRUE;
HBITMAP hbGameOver;
HBITMAP hbMenuStart;
HBITMAP hbMenuExit;
HBITMAP hbWin;

LRESULT CALLBACK WndProc(HWND, UINT, UINT, LONG);

ATOM registerMyClass(HINSTANCE hInstance);

int createMyWindow(HINSTANCE hInstance, int nCmdShow);
void Bonus();
//////////////////////////////////////

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	Player.Position.x = 240;
	Player.Position.y = 400;
	Player.Weigth = 30;
	Player.Live = 3;
	Ball.Position.x = 240;
	Ball.Position.y = 380;
	Ball.radius = 10;
	Ball.NormalSpeed = 3;
	Ball.State = FALSE;
	Game.GameStart = FALSE;
	Game.GameOver = FALSE;
	Game.GameWin = FALSE;
	Menu.CountButton = 2;
	Menu.CurButton = 0;
	Bon.AdWall = FALSE;

	Block = Level(NumberLevel);
	
	createMyWindow(hInstance, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void Motion()
{
	if (Ball.State == FALSE)
	{
		Ball.Position.x = Player.Position.x;
	}
	else
	{
		if (Ball.Position.x + Ball.Speed.x > 470 - Ball.radius || Ball.Position.x + Ball.Speed.x < Ball.radius)
		{
			Ball.Speed.x = -Ball.Speed.x;
		}
		if (Ball.Position.y + Ball.Speed.y > 440 - Ball.radius || Ball.Position.y + Ball.Speed.y < Ball.radius || Bon.AdWall == TRUE && Ball.Position.y + Ball.Speed.y > 420 - Ball.radius)
		{
			Ball.Speed.y = -Ball.Speed.y;
		}
		if (Ball.Position.y + Ball.Speed.y >= Player.Position.y - 10 - Ball.radius
			&& Ball.Position.x - Ball.radius <= Player.Position.x + Player.Weigth && Ball.Position.x + Ball.radius >= Player.Position.x - Player.Weigth)
		{
			if (Ball.Position.x > Player.Position.x&& Ball.Position.x <= Player.Position.x + Player.Weigth / 5)
			{
				Ball.Speed.x = 0.26;
				Ball.Speed.y = -0.97;
			}
			if (Ball.Position.x > Player.Position.x + Player.Weigth / 5 && Ball.Position.x <= Player.Position.x + Player.Weigth / 5 * 2)
			{
				Ball.Speed.x = 0.5;
				Ball.Speed.y = -0.87;
			}
			if (Ball.Position.x > Player.Position.x + Player.Weigth / 5 * 2 && Ball.Position.x <= Player.Position.x + Player.Weigth / 5 * 3)
			{
				Ball.Speed.x = 0.71;
				Ball.Speed.y = -0.71;
			}
			if (Ball.Position.x > Player.Position.x + Player.Weigth / 5 * 3 && Ball.Position.x <= Player.Position.x + Player.Weigth / 5 * 4)
			{
				Ball.Speed.x = 0.87;
				Ball.Speed.y = -0.5;
			}
			if (Ball.Position.x > Player.Position.x + Player.Weigth / 5 * 4 && Ball.Position.x - Ball.radius <= Player.Position.x + Player.Weigth)
			{
				Ball.Speed.x = 0.97;
				Ball.Speed.y = -0.26;
			}

			if (Ball.Position.x < Player.Position.x && Ball.Position.x >= Player.Position.x - Player.Weigth / 5)
			{
				Ball.Speed.x = -0.26;
				Ball.Speed.y = -0.97;
			}
			if (Ball.Position.x < Player.Position.x - Player.Weigth / 5 && Ball.Position.x >= Player.Position.x - Player.Weigth / 5 * 2)
			{
				Ball.Speed.x = -0.5;
				Ball.Speed.y = -0.87;
			}
			if (Ball.Position.x < Player.Position.x - Player.Weigth / 5 * 2 && Ball.Position.x >= Player.Position.x - Player.Weigth / 5 * 3)
			{
				Ball.Speed.x = -0.71;
				Ball.Speed.y = -0.71;
			}
			if (Ball.Position.x < Player.Position.x - Player.Weigth / 5 * 3 && Ball.Position.x >= Player.Position.x - Player.Weigth / 5 * 4)
			{
				Ball.Speed.x = -0.87;
				Ball.Speed.y = -0.5;
			}
			if (Ball.Position.x < Player.Position.x - Player.Weigth / 5 * 4 && Ball.Position.x + Ball.radius >= Player.Position.x - Player.Weigth)
			{
				Ball.Speed.x = -0.97;
				Ball.Speed.y = -0.26;
			}

			if (Ball.Position.x == Player.Position.x)
			{
				Ball.Speed.x = 0;
				Ball.Speed.y = -1;
			}
		}
		Ball.Position.x += Ball.Speed.x * Ball.NormalSpeed;
		Ball.Position.y += Ball.Speed.y * Ball.NormalSpeed;

	}

	if (Ball.Position.y > Player.Position.y&& Bon.AdWall != TRUE)
	{
		if (Player.Live != 0)
		{
			Player.Live--;
			Ball.State = FALSE;
			Ball.Position.x = Player.Position.x;
			Ball.Position.y = Player.Position.y - 20;
		}
		else
			Game.GameOver = TRUE;
	}
		
}

void BlockBreak()
{
	int CountFalse = 0;
	for (int i = 0; i < Block[0]->Lev.CountY; i++)
	{
		for (int j = 0; j < Block[0]->Lev.CountX; j++)
		{
			if (Ball.Position.y <= Block[i][j].Position.y + 2 * Ball.radius + 2 && Ball.Position.x <= Block[i][j].Position.x + 30 &&
				Ball.Position.x >= Block[i][j].Position.x - 30 && Block[i][j].State != FALSE && Ball.Position.y >= Block[i][j].Position.y - 2 * Ball.radius - 2)
			{
				if (Block[i][j].Bonus != 0 && Block[i][j].Strength == 1)
				{
					Ball.Speed.y = -Ball.Speed.y;
					Block[i][j].State = FALSE;
					Block[i][j].BonusFall = TRUE;
					return;
				}
				if (Block[i][j].Strength == 1)
					Block[i][j].State = FALSE;
				else
					Block[i][j].Strength--;
				Ball.Speed.y = -Ball.Speed.y;
				return;
			}
			if (Ball.Position.y <= Block[i][j].Position.y + 13 && Block[i][j].State != FALSE && Ball.Position.y >= Block[i][j].Position.y - 10 &&
				(Ball.Position.x + Ball.radius >= Block[i][j].Position.x - 30 && Ball.Position.x - Ball.radius <= Block[i][j].Position.x + 30))
			{
				if (Block[i][j].Bonus != 0 && Block[i][j].Strength == 1)
				{
					Ball.Speed.x = -Ball.Speed.x;
					Block[i][j].State = FALSE;
					Block[i][j].BonusFall = TRUE;
					return;
				}
				if (Block[i][j].Strength == 1)
					Block[i][j].State = FALSE;
				else
					Block[i][j].Strength--;
				Ball.Speed.x = -Ball.Speed.x;
				return;
			}
			if (Block[i][j].State == FALSE)
			{
				CountFalse++;
			}
		}
	}
	if (CountFalse == Block[0]->Lev.CountX * Block[0]->Lev.CountY)
	{
		NumberLevel++;
		free(Block);
		Block = Level(NumberLevel);
		CountFalse = 0;
		Ball.State = FALSE;
		Ball.Position.x = Player.Position.x;
		Ball.Position.y = Player.Position.y - 20;
		if (NumberLevel == 4)
			Game.GameWin = TRUE;
	}
}

void MotionBonus()
{
	for (int i = 0; i < Block[0]->Lev.CountY; i++)
	{
		for (int j = 0; j < Block[0]->Lev.CountX; j++)
		{
			if (Block[i][j].BonusFall == TRUE)
				Block[i][j].Position.y++;
			if (Block[i][j].Position.y + 10 >= Player.Position.y && Block[i][j].Position.x + 25 >= Player.Position.x - Player.Weigth && Block[i][j].Position.x - 25 <= Player.Position.x + Player.Weigth)
			{
				Player.BonusTimer = 0;
				Bonus();
				Player.ActiveBonus = Block[i][j].Bonus;
				Block[i][j].BonusFall = FALSE;
				Player.BonusTimer = 300;
				Block[i][j].Position.y -= 10;
			}
			if (Block[i][j].Position.y + 10 >= Player.Position.y)
			{
				Block[i][j].BonusFall = FALSE;
				Block[i][j].Position.y -= 10;
			}
		}
	}

}

//Бонусы:
//0. Ничего
//1. Ускорение мяча
//2. Удлинение игрока
//3. Дополнительная стенка
//4. Пулемет
void Bonus()
{
	switch (Player.ActiveBonus)
	{
	case 1:
		if (Player.BonusTimer != 0)
		{
			Ball.NormalSpeed = 6;
			Player.BonusTimer--;
		}
		else
			Ball.NormalSpeed = 3;
		break;
	case 2:
		if (Player.BonusTimer != 0)
		{
			Player.Weigth = 60;
			Player.BonusTimer--;
		}
		else
			Player.Weigth = 30;
		break;
	case 3:
		if (Player.BonusTimer != 0)
		{
			Bon.AdWall = TRUE;
			Player.BonusTimer--;
		}
		else
			Bon.AdWall = FALSE;
		break;
	case 4:
		if (Player.BonusTimer == 300)
		{
			Bon.Gun.Shot = malloc(sizeof(SHOT));
			Bon.Gun.CountShot = 0;
			Bon.Gun.State = TRUE;
		}	
		Player.BonusTimer--;
		break;
	default:
		break;
	}

}

void AdditionalWall()
{
	HPEN GreenPen;
	GreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	SelectObject(memDC, GreenPen);
	MoveToEx(memDC, 0, 420, NULL);
	LineTo(memDC, 480, 420);
	DeleteObject(GreenPen);
}

void Gun()
{
	if (Bon.Gun.CountShot >= 0 && (Player.BonusTimer == 299 || Player.BonusTimer == 239 || Player.BonusTimer == 179 || Player.BonusTimer == 119 || Player.BonusTimer == 59))
	{
		Bon.Gun.Shot = realloc(Bon.Gun.Shot, (Bon.Gun.CountShot + 1) * sizeof(SHOT));
		Bon.Gun.Shot[Bon.Gun.CountShot].ShotPos.x = Player.Position.x;
		Bon.Gun.Shot[Bon.Gun.CountShot].ShotPos.y = Player.Position.y - 10;
		Bon.Gun.Shot[Bon.Gun.CountShot].State = TRUE;
		Bon.Gun.CountShot++;
	}
	HPEN BluePen;
	BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	SelectObject(memDC, BluePen);
	for (int i = 0; i < Bon.Gun.CountShot; i++)
	{
		if (Bon.Gun.Shot[i].State != FALSE)
		{
			Bon.Gun.Shot[i].ShotPos.y--;
			MoveToEx(memDC, Bon.Gun.Shot[i].ShotPos.x, Bon.Gun.Shot[i].ShotPos.y, NULL);
			LineTo(memDC, Bon.Gun.Shot[i].ShotPos.x, Bon.Gun.Shot[i].ShotPos.y + 20);
		}
		
	}
	
	for (int i = 0; i < Block[0]->Lev.CountY; i++)
	{
		for (int j = 0; j < Block[0]->Lev.CountX; j++)
		{
			for (int k = 0; k < Bon.Gun.CountShot; k++)
				if (Bon.Gun.Shot[k].ShotPos.y <= Block[i][j].Position.y && Bon.Gun.Shot[k].ShotPos.x <= Block[i][j].Position.x + 25 && Bon.Gun.Shot[k].ShotPos.x >= Block[i][j].Position.x - 25 && (Block[i][j].State != FALSE || Block[i][j].State == FALSE && Bon.Gun.Shot[k].ShotPos.y < 5))
				{
					Block[i][j].State = FALSE;
					Bon.Gun.Shot[k].State = FALSE;
					
				}
		}
	}

	if (Bon.Gun.CountShot == 5 && Bon.Gun.Shot[1].State != TRUE && Bon.Gun.Shot[2].State != TRUE && Bon.Gun.Shot[3].State != TRUE && Bon.Gun.Shot[4].State != TRUE && Bon.Gun.Shot[5].State != TRUE)
	{
		Bon.Gun.State = FALSE;
		free(Bon.Gun.Shot);
	}

	DeleteObject(BluePen);
}

void DrawMenu()
{
	HPEN BlackPen, RedPen;
	HBRUSH BlueBrush, WhiteBrush;

	BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	RedPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	BlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	
	for (int i = 0; i < Menu.CountButton; i++)
	{
		if (Menu.CurButton == i)
			SelectObject(memDC, RedPen);
		else
			SelectObject(memDC, BlackPen);
		Rectangle(memDC, 90, i * 100 + 90, 390, i * 100 + 190);
	}
	BitBlt(hdc, 0, 0, 480, 480, memDC, 0, 0, SRCCOPY);
	
	hbMenuStart = (HBITMAP)LoadImage(NULL, TEXT("Start.bmp"), IMAGE_BITMAP, 300, 100, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(memDC, hbMenuStart);
	BitBlt(hdc, 91, 91, 297, 97, memDC, 0, 0, SRCCOPY);

	hbMenuExit = (HBITMAP)LoadImage(NULL, TEXT("Exit.bmp"), IMAGE_BITMAP, 300, 97, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(memDC, hbMenuExit);
	BitBlt(hdc, 91, 191, 297, 197, memDC, 0, 0, SRCCOPY);

	DeleteObject(BlueBrush);
	DeleteObject(WhiteBrush);
	DeleteObject(BlackPen);
	DeleteObject(RedPen);
	DeleteObject(hbMenuStart);
	DeleteObject(hbMenuExit);
	DeleteObject(memBM);
	DeleteDC(memDC);

}

void Win()
{
	FillRect(memDC, &ps.rcPaint, (HBRUSH)RGB(0, 0, 0));
	BitBlt(hdc, 0, 0, 480, 480, memDC, 0, 0, SRCCOPY);
	hbWin = (HBITMAP)LoadImage(NULL, TEXT("Win.bmp"), IMAGE_BITMAP, 465, 100, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(memDC, hbWin);
	BitBlt(hdc, 0, 100, 480, 200, memDC, 0, 0, SRCCOPY);
	KillTimer(hWnd, 1);
}

void GameOver()
{
	FillRect(memDC, &ps.rcPaint, (HBRUSH)RGB(0, 0, 0));
	BitBlt(hdc, 0, 0, 480, 480, memDC, 0, 0, SRCCOPY);
	hbGameOver = (HBITMAP)LoadImage(NULL, TEXT("GameOver.bmp"), IMAGE_BITMAP, 465, 100, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(memDC, hbGameOver);
	BitBlt(hdc, 0, 100, 480, 200, memDC, 0, 0, SRCCOPY);
	KillTimer(hWnd, 1);
}

void Scene()
{
	hdc = BeginPaint(hWnd, &ps);
	memDC = CreateCompatibleDC(hdc);
	memBM = CreateCompatibleBitmap(hdc, 480, 480);
	HGDIOBJ oldBMP = SelectObject(memDC, memBM);

	GetClientRect(hWnd, &ps.rcPaint);
	FillRect(memDC, &ps.rcPaint, RGB(0, 0, 0));


	if (Game.GameStart == TRUE)
	{
		HPEN hBlackPen;
		hBlackPen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(memDC, hBlackPen);

		HBRUSH hRedBrush, hWhiteBrush, hGreenBrush;
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
		for (int i = 0; i < Block[0]->Lev.CountY; i++)
		{
			for (int j = 0; j < Block[0]->Lev.CountX; j++)
			{
				if (Block[i][j].Strength == 1)
					SelectObject(memDC, hRedBrush);
				else
					SelectObject(memDC, hGreenBrush);

				if (Block[i][j].State != FALSE || Block[i][j].BonusFall == TRUE)
					Rectangle(memDC, (int)Block[i][j].Position.x - 25, (int)Block[i][j].Position.y - 10, (int)Block[i][j].Position.x + 25, (int)Block[i][j].Position.y + 10);


			}
		}


		SelectObject(memDC, hWhiteBrush);
		Rectangle(memDC, (int)Player.Position.x - Player.Weigth, (int)Player.Position.y - 10, (int)Player.Position.x + Player.Weigth, (int)Player.Position.y + 10);
		Ellipse(memDC, (int)Ball.Position.x - 10, (int)Ball.Position.y - 10, (int)Ball.Position.x + 10, (int)Ball.Position.y + 10);
		if (Bon.AdWall == TRUE)
			AdditionalWall();
		if (Bon.Gun.State == TRUE)
		{
			Gun();
		}
		TextOutA(memDC, 10, 400, "Live:", 5);
		char c[3];
		_itoa(Player.Live, c, 10);
		TextOutA(memDC, 45, 400, (LPCSTR)c, 1);

		MotionBonus();
		Motion();
		BlockBreak();
		Bonus();

		DeleteObject(hWhiteBrush);
		DeleteObject(hRedBrush);
		DeleteObject(hGreenBrush);
		DeleteObject(hbGameOver);
		DeleteObject(hBlackPen);
	}
	else
	{
		DrawMenu();
		return;
	}

	BitBlt(hdc, 0, 0, 480, 480, memDC, 0, 0, SRCCOPY);

	if (Game.GameOver == TRUE)
	{
		GameOver();
	}

	if (Game.GameWin == TRUE)
	{
		Win();
	}

	SelectObject(memDC, oldBMP);
	DeleteObject(memBM);
	DeleteDC(memDC);

	EndPaint(hWnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_TIMER:
	{
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_PAINT:
	{
		Scene();
		break;
	}
	case WM_LBUTTONDOWN:
	{
		click = 1;
		break;
	}
	case WM_LBUTTONUP:
	{
		click = 0;
		if (LOWORD(lParam) >= Player.Position.x - 30 && LOWORD(lParam) <= Player.Position.x + 30)
			Ball.State = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (click == 1 && LOWORD(lParam) >= Player.Position.x - 30 && LOWORD(lParam) <= Player.Position.x + 30 && LOWORD(lParam) < 435 && LOWORD(lParam) > 29)
		{
			Player.Position.x = LOWORD(lParam);
		}
		break;
	}
	case WM_KEYDOWN:
	{
		if (Game.GameStart == FALSE)
		{
			switch (wParam)
			{
			case VK_DOWN:
			{
				if (Menu.CurButton < Menu.CountButton - 1)
				{
					Menu.CurButton++;
					InvalidateRect(hWnd, NULL, FALSE);
				}
					
				break;
			}
			case VK_UP:
			{
				if (Menu.CurButton > 0)
				{
					Menu.CurButton--;
					InvalidateRect(hWnd, NULL, FALSE);
				}
					
				break;
			}
			case VK_RETURN:
			{
				switch (Menu.CurButton)
				{
				case 0:
					Game.GameStart = TRUE;
					SetTimer(hWnd, 1, 1, NULL);
					break;
				case 1:
					exit(0);
					break;
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
		}
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int createMyWindow(HINSTANCE hInstance, int nCmdShow)
{
	registerMyClass(hInstance);

	hWnd = CreateWindow(szClassName, L"task 8", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 480, 480, NULL, NULL, hInstance, NULL);

	if (!hWnd) { return 0; }
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

ATOM registerMyClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	return RegisterClass(&wc);
}