#pragma once
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
	BOOL GameStart;
	BOOL GameOver;
	BOOL GameWin;
} GAME;

typedef struct
{
	int CurButton;
	int CountButton;
} MENU;

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

BLOCK** Level(int NumberLevel);
char ITOA(int Num);