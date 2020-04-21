#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

char szClassName[] = "Window1";
HWND hWnd;
PAINTSTRUCT ps;
HDC hdc;
HDC memDC;
int click = 0;
int NumberLevel = 1;
int GameState = 0;
HBITMAP memBM;
BOOL isDrawing = TRUE;
SCENE sc;


LRESULT CALLBACK WndProc(HWND, UINT, UINT, LONG);

ATOM registerMyClass(HINSTANCE hInstance);

int createMyWindow(HINSTANCE hInstance, int nCmdShow);

void InitGame()
{
	sc.Player.Position.x = 240;
	sc.Player.Position.y = 400;
	sc.Player.Weigth = 30;
	sc.Player.Live = 3;
	sc.Ball.Position.x = 240;
	sc.Ball.Position.y = 380;
	sc.Ball.radius = 10;
	sc.Ball.NormalSpeed = 3;
	sc.Ball.State = FALSE;
	sc.Bon.AdWall = FALSE;

	sc.Block = Level(NumberLevel);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow)
{
	InitGame();
	sc.Menu.CountButton = 2;
	sc.Menu.CurButton = 0;
	createMyWindow(hInstance, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void Scene()
{
	hdc = BeginPaint(hWnd, &ps);
	memDC = CreateCompatibleDC(hdc);
	memBM = CreateCompatibleBitmap(hdc, 480, 480);
	HGDIOBJ oldBMP = SelectObject(memDC, memBM);

	GetClientRect(hWnd, &ps.rcPaint);
	FillRect(memDC, &ps.rcPaint, RGB(0, 0, 0));


	if (GameState == 1)
	{
		HPEN hBlackPen;
		hBlackPen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
		SelectObject(memDC, hBlackPen);

		HBRUSH hRedBrush, hWhiteBrush, hGreenBrush;
		hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
		hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
		for (int i = 0; i < sc.Block[0]->Lev.CountY; i++)
		{
			for (int j = 0; j < sc.Block[0]->Lev.CountX; j++)
			{
				if (sc.Block[i][j].Strength == 1)
					SelectObject(memDC, hRedBrush);
				else
					SelectObject(memDC, hGreenBrush);

				if (sc.Block[i][j].State != FALSE || sc.Block[i][j].BonusFall == TRUE)
					Rectangle(memDC, (int)sc.Block[i][j].Position.x - 25, (int)sc.Block[i][j].Position.y - 10, (int)sc.Block[i][j].Position.x + 25, (int)sc.Block[i][j].Position.y + 10);


			}
		}


		SelectObject(memDC, hWhiteBrush);
		Rectangle(memDC, (int)sc.Player.Position.x - sc.Player.Weigth, (int)sc.Player.Position.y - 10, (int)sc.Player.Position.x + sc.Player.Weigth, (int)sc.Player.Position.y + 10);
		Ellipse(memDC, (int)sc.Ball.Position.x - 10, (int)sc.Ball.Position.y - 10, (int)sc.Ball.Position.x + 10, (int)sc.Ball.Position.y + 10);
		if (sc.Bon.AdWall == TRUE)
			AdditionalWall(memDC);
		if (sc.Bon.Gun.State == TRUE)
		{
			sc = Gun(memDC, sc);
		}
		TextOutA(memDC, 10, 400, "Live:", 5);
		char c[3];
		_itoa(sc.Player.Live, c, 10);
		TextOutA(memDC, 45, 400, (LPCSTR)c, 1);

		sc = MotionBonus(sc, GameState);
		sc = Motion(sc, GameState);
		sc = BlockBreak(sc, GameState, NumberLevel);
		sc = Bonus(sc);

		DeleteObject(hWhiteBrush);
		DeleteObject(hRedBrush);
		DeleteObject(hGreenBrush);
		DeleteObject(hBlackPen);
	}
	else
	{
		DrawMenu(hdc, memDC, memBM, sc);
		return;
	}

	BitBlt(hdc, 0, 0, 480, 480, memDC, 0, 0, SRCCOPY);

	if (GameState == 2)
	{
		GameOv(hdc, memDC, memBM, ps, hWnd);
	}

	if (GameState == 3)
	{
		Win(hdc, memDC, memBM, ps, hWnd);
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
		if (LOWORD(lParam) >= sc.Player.Position.x - 30 && LOWORD(lParam) <= sc.Player.Position.x + 30)
			sc.Ball.State = TRUE;
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (click == 1 && LOWORD(lParam) >= sc.Player.Position.x - 30 && LOWORD(lParam) <= sc.Player.Position.x + 30 && LOWORD(lParam) < 435 && LOWORD(lParam) > 29)
		{
			sc.Player.Position.x = LOWORD(lParam);
		}
		break;
	}
	case WM_KEYDOWN:
	{
		if (GameState != 1)
		{
			switch (wParam)
			{
			case VK_DOWN:
			{
				if (sc.Menu.CurButton < sc.Menu.CountButton - 1)
				{
					sc.Menu.CurButton++;
					InvalidateRect(hWnd, NULL, FALSE);
				}

				break;
			}
			case VK_UP:
			{
				if (sc.Menu.CurButton > 0)
				{
					sc.Menu.CurButton--;
					InvalidateRect(hWnd, NULL, FALSE);
				}

				break;
			}
			case VK_RETURN:
			{
				switch (sc.Menu.CurButton)
				{
				case 0:
					GameState = 1;
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

	hWnd = CreateWindow(szClassName, "Arcanoid", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 480, 480, NULL, NULL, hInstance, NULL);

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
