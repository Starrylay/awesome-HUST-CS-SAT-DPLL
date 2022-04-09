// 作者：陈昊 <2975280738@qq.com>
// 最后修改：2020-11-1
//

#ifndef SUDOKU_EASYX_H
#define SUDOKU_EASYX_H
#include <conio.h>
#include <graphics.h>
#include <time.h>

#define MAP_COL 9
#define MAP_ROW 9


COORD currentPos = { 0,0 }, numPos = { 10,0 }, coord, waitPos;
clock_t t1, t2;
ExMessage msg;
int sleepTime = 0;
int flag_w = 1;
int num = 1;
int process;
int second = 0, minute = 0;
int gameDifficulty = 0, gameMode = 0, restart, faults, endGame;
int isWin = 0, noMistake = 0;
int issame = 0;
int Map1[MAP_ROW][MAP_COL], Map2[MAP_ROW][MAP_COL];
int Map_HL[MAP_ROW][MAP_COL], Map_Mistake[MAP_ROW][MAP_COL];
int showanswer = 0;

void react();
int judge_win();
void dataInit();
void select1();
void start1();
void select2();
void start2();
void select3();
void start3();
void end();
void GameDraw();
void GameUpdate();
void HeighLight(int);
COORD FindLeftUpperCornor(COORD);
int FindMistake(int);
int WinJudge();
void GameInit(int,int[][9]);
void Dig(int);
//#pragma once
#endif;//
