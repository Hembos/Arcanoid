#pragma once
#include <Windows.h>
#include <Windows.h>
#include <malloc.h>
#include <stdio.h>
#include <ctype.h>

typedef struct
{
	double x;
	double y;
} Point;

typedef struct
{
	Point Position;
	int ActiveBonus;
	int BonusTimer;
	int Weigth;
	int Live;
} PLAYER;

typedef struct
{
	Point Position;
	Point Speed;
	int radius;
	BOOL State;
	int NormalSpeed;
} BALL;

typedef struct
{
	int CountX;
	int CountY;
} LEVEL;


typedef struct
{
	Point Position;
	BOOL State;
	int Strength;
	int Bonus;
	BOOL BonusFall;
	LEVEL Lev;
} BLOCK;

typedef struct
{
	POINT ShotPos;
	BOOL State;
} SHOT;

typedef struct
{
	SHOT* Shot;
	int CountShot;
	BOOL State;
} GUN;

typedef struct
{
	BOOL AdWall;
	GUN Gun;
} BONUS;

typedef enum
{
	GameStart = 1,
	GameOver,
	GameWin
} GAME;

typedef struct
{
	int CurButton;
	int CountButton;
} MENU;

typedef struct
{
	PLAYER Player;
	BALL Ball;
	BLOCK** Block;
	BONUS Bon;
	LEVEL Lev;
	MENU Menu;
} SCENE;


void DrawMenu(HDC hdc, HDC memDC, HBITMAP memBM, SCENE sc);
BLOCK** Level(int NumberLevel);
SCENE Motion(SCENE sc, int GameState);
SCENE BlockBreak(SCENE sc, int GameState, int NumberLevel);
SCENE Bonus(SCENE sc);
SCENE MotionBonus(SCENE sc, int GameState);
void AdditionalWall(HDC memDC);
SCENE Gun(HDC memDC, SCENE sc);
