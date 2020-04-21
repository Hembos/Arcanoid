#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

HBITMAP hbMenuStart;
HBITMAP hbMenuExit;
HBITMAP hbGameOver;
HBITMAP hbWin;

void DrawMenu(HDC hdc, HDC memDC, HBITMAP memBM, SCENE sc)
{
	HPEN BlackPen, RedPen;
	HBRUSH BlueBrush, WhiteBrush;

	BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	RedPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	BlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));

	for (int i = 0; i < sc.Menu.CountButton; i++)
	{
		if (sc.Menu.CurButton == i)
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

void Win(HDC hdc, HDC memDC, HBITMAP memBM, PAINTSTRUCT ps, HWND hWnd)
{
	FillRect(memDC, &ps.rcPaint, (HBRUSH)RGB(0, 0, 0));
	BitBlt(hdc, 0, 0, 480, 480, memDC, 0, 0, SRCCOPY);
	hbWin = (HBITMAP)LoadImage(NULL, TEXT("Win.bmp"), IMAGE_BITMAP, 465, 100, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(memDC, hbWin);
	BitBlt(hdc, 0, 100, 480, 200, memDC, 0, 0, SRCCOPY);
	KillTimer(hWnd, 1);
	DeleteObject(hbGameOver);
}

void GameOv(HDC hdc, HDC memDC, HBITMAP memBM, PAINTSTRUCT ps, HWND hWnd)
{
	FillRect(memDC, &ps.rcPaint, (HBRUSH)RGB(0, 0, 0));
	BitBlt(hdc, 0, 0, 480, 480, memDC, 0, 0, SRCCOPY);
	hbGameOver = (HBITMAP)LoadImage(NULL, TEXT("GameOver.bmp"), IMAGE_BITMAP, 465, 100, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	SelectObject(memDC, hbGameOver);
	BitBlt(hdc, 0, 100, 480, 200, memDC, 0, 0, SRCCOPY);
	KillTimer(hWnd, 1);
}
