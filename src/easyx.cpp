
// 程序名称：数独游戏
// 开发环境：VS2019 + EasyX_20200902
#include "Global.h"
#include"sudoku_easyx.h"
extern int sudoku[ROW][COL];//完整版
extern int starting_grid[ROW][COL];//挖洞版
extern int holes;
int sudoku_easyx()
{
	void (*fun[2])() = { select1,select3 };
	initgraph(900, 620);
	while (1)
	{
		dataInit();
		while (process < 2)
			fun[process++]();
		t1 = clock();
		GameInit(gameMode,sudoku);
		while (1)
		{

			if (peekmessage(&msg, EM_MOUSE, true))
				msg = getmessage();
			GameUpdate();
			GameDraw();
			isWin = WinJudge();//是不是填满了
			if (isWin) {
				//judge_win();//是不是和sudoku一样
				 issame = judge_win();
				
					Sleep(1000);
					break;
			}
			else if (restart) {
				Sleep(1000);
				break;
			}
			
			if (endGame)
				break;
			
			
			//if (noMistake == 0)
				//isWin = WinJudge();
			/*if (is_same || restart)
			{
				Sleep(1000);
				break;
			}*/
		}
		if (issame)
			end();
		else 
			react();
		if (endGame)
			break;
	}
	closegraph();
	return 0;
}


void dataInit()
{
	process = 0;
	restart = 0;
	sleepTime = 0;
	faults = 0;
	endGame = 0;
	for (int i = 0; i < MAP_ROW; i++)
		for (int j = 0; j < MAP_COL; j++)
	    Map1[i][j] = Map2[i][j] =Map_HL[i][j] = Map_Mistake[i][j] = 0;
}
void start1()
{
	BeginBatchDraw();
	setbkcolor(WHITE); //设置窗口背景颜色
	settextcolor(BLACK);
	setbkmode(1); //设置文字背景透明
	cleardevice();
	TCHAR s[5];
	_stprintf_s(s, _T("%d/2"), process);
	outtextxy(0, 0, s);
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 100;             // 设置字体高度为 100
	wcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	outtextxy(300, 100, _T("数  独"));


	settextstyle(40, 0, _T("宋体"));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);


	rectangle(340, 290, 560, 360);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>290 && currentPos.Y < 360)
	{
		settextcolor(BLUE);
		line(370, 350, 530, 350);
	}
	else
		settextcolor(BLACK);
	outtextxy(370, 305, L"标准数独");
	/*rectangle(340, 390, 560, 460);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
	{
		settextcolor(BLUE);
		line(350, 450, 550, 450);
	}
	else
		settextcolor(BLACK);
	outtextxy(350, 405, L"对角线数独");*/
	EndBatchDraw();

}
void select1()
{
	int post = 1;
	while (post)
	{
		start1();
		ExMessage msg = getmessage(); // 获取鼠标信息
		int x = msg.x;
		int y = msg.y;
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			currentPos.X = x;
			currentPos.Y = y;
			break;
		case WM_LBUTTONUP:
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>290 && currentPos.Y < 360)
			{
				gameMode = 1;
				post = 0;
			}
			/*if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
			{
				gameMode = 0;
				post = 0;
			}*/
			break;
		default:
			break;
		}
	}


}
void start2()
{
	BeginBatchDraw();
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1); //设置文字背景透明
	cleardevice();
	TCHAR s[5];
	_stprintf_s(s, _T("%d/3"), process);
	outtextxy(0, 0, s);
	settextstyle(40, 0, _T("宋体"));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);


	//rectangle(340, 90, 560, 160);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>90 && currentPos.Y < 160)
	{
		settextcolor(BLUE);
		line(370, 150, 530, 150);
	}
	else
		settextcolor(BLACK);
	outtextxy(370, 105, L"容    易");


	//rectangle(340, 190, 560, 260);
	//if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>190 && currentPos.Y < 260)
	//{
	//	settextcolor(BLUE);
	//	line(370, 250, 530, 250);
	//}
	//else
	//	settextcolor(BLACK);
	//outtextxy(370, 205, L"一    般");


	//rectangle(340, 290, 560, 360);
	//if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>290 && currentPos.Y < 360)
	//{
	//	settextcolor(BLUE);
	//	line(370, 350, 530, 350);
	//}
	//else
	//	settextcolor(BLACK);
	//outtextxy(370, 305, L"专    家");


	//rectangle(340, 390, 560, 460);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
	{
		settextcolor(BLUE);
		line(370, 450, 530, 450);
	}
	else
		settextcolor(BLACK);
	outtextxy(370, 405, L"返    回");
	EndBatchDraw();
}
void select2()
{
	int post = 1;
	while (post)
	{
		start2();
		ExMessage msg = getmessage(); // 获取鼠标信息
		int x = msg.x;
		int y = msg.y;
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			currentPos.X = x;
			currentPos.Y = y;
			break;
		case WM_LBUTTONUP:
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>90 && currentPos.Y < 160)
			{
				post = 0;
				gameDifficulty = 0;
			}
			/*if (currentpos.x > 340 && currentpos.x < 560 && currentpos.y>190 && currentpos.y < 260)
			{
				post = 0;
				gamedifficulty = 1;
			}
			if (currentpos.x > 340 && currentpos.x < 560 && currentpos.y>290 && currentpos.y < 360)
			{
				post = 0;
				gamedifficulty = 2;
			}*/
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
			{
				post = 0;
				process -= 2;
			}
			break;
		default:
			break;
		}
	}


}
void start3()
{
	BeginBatchDraw();
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1); //设置文字背景透明
	cleardevice();
	TCHAR s[5];
	_stprintf_s(s, _T("%d/2"), process);
	outtextxy(0, 0, s);
	settextstyle(40, 0, _T("宋体"));
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);


	rectangle(340, 190, 560, 260);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>190 && currentPos.Y < 260)
	{
		settextcolor(BLUE);
		line(370, 250, 530, 250);
	}
	else
		settextcolor(BLACK);
	outtextxy(370, 205, L"开始游戏");


	rectangle(340, 390, 560, 460);
	if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
	{
		settextcolor(BLUE);
		line(370, 450, 530, 450);
	}
	else
		settextcolor(BLACK);
	outtextxy(370, 405, L"返    回");
	EndBatchDraw();
}
void select3()
{
	int post = 1;
	while (post)
	{
		start3();
		ExMessage msg = getmessage(); // 获取鼠标信息
		int x = msg.x;
		int y = msg.y;
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			currentPos.X = x;
			currentPos.Y = y;
			break;
		case WM_LBUTTONUP:
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>190 && currentPos.Y < 260)
				post = 0;
			if (currentPos.X > 340 && currentPos.X < 560 && currentPos.Y>390 && currentPos.Y < 460)
			{
				post = 0;
				process -= 2;
			}
			break;
		default:
			break;
		}
	}


}


void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(WHITE); //设置背景颜色
	setbkmode(1);
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 40;                      // 设置字体高度为 40
	wcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体为“楷体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);


	/*画九宫格的框线*/
	setlinecolor(BLACK);
	for (int row = 1; row <= MAP_ROW + 1; row++) //横线
	{
		if ((row - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(60, row * 60, 600, row * 60);
	}
	for (int col = 1; col <= MAP_COL + 1; col++) //竖线
	{
		if ((col - 1) % 3 == 0)
			setlinestyle(PS_SOLID, 3);
		else
			setlinestyle(PS_DASH, 1);
		line(col * 60, 60, col * 60, 600);
	}


	/*先高亮后outtextxy数字，否则数字会被覆盖*/
	//高亮提示数字

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (Map_HL[i][j])
			{
				if (Map_HL[i][j] == 1)
					setfillcolor(RGB(85, 242, 85));//相同数字用绿色显示
				else
					setfillcolor(RGB(174, 174, 174));//同行列宫用浅灰色显示
				solidrectangle((j + 1) * 60 + 2, (i + 1) * 60 + 2, (j + 2) * 60 - 2, (i + 2) * 60 - 2);
			}
	setfillcolor(RGB(99, 99, 99));
	if (flag_w)
		solidrectangle((waitPos.X + 1) * 60 + 2, (waitPos.Y + 1) * 60 + 2, (waitPos.X + 2) * 60 - 2, (waitPos.Y + 2) * 60 - 2);
	//高亮错误数字所在的框格
	setfillcolor(RGB(250, 44, 20));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (Map_Mistake[i][j])
				solidrectangle((j + 1) * 60 + 1, (i + 1) * 60 + 1, (j + 2) * 60 - 1, (i + 2) * 60 - 1);


	//画宫格数字
	TCHAR str[10];
	if (showanswer == 0) {
		for (int row = 0; row < MAP_ROW; row++)
		{
			for (int col = 0; col < MAP_COL; col++)
			{
				//数字0就不需要显示了
				if (Map1[row][col])
				{
					if (Map2[row][col] == 1)
						settextcolor(BLUE);
					else if (Map_HL[row][col] || Map_Mistake[row][col])
						settextcolor(WHITE);
					else
						settextcolor(RGB(61, 61, 61));
					_stprintf_s(str, _T("%d"), Map1[row][col]);
					outtextxy((col + 1) * 60 + 20, (row + 1) * 60 + 10, str);
				}
			}
		}
	}
	else {
		for (int row = 0; row < MAP_ROW; row++)
		{
			for (int col = 0; col < MAP_COL; col++)
			{
				//数字0就不需要显示了
				if (Map1[row][col])
				{
					if (Map2[row][col] == 1)
						settextcolor(BLUE);
					else if (Map_HL[row][col] || Map_Mistake[row][col])
						settextcolor(WHITE);
					else
						settextcolor(RGB(61, 61, 61));
					_stprintf_s(str, _T("%d"), Map1[row][col]);
					outtextxy((col + 1) * 60 + 20, (row + 1) * 60 + 10, str);
				}
				else {
					settextcolor(RED);
					_stprintf_s(str, _T("%d"),sudoku[row][col]);
					outtextxy((col + 1) * 60 + 20, (row + 1) * 60 + 10, str);
				}
			}
		}
	}


	/*画数字键盘内外框*/
	setlinestyle(PS_SOLID, 1);
	rectangle(660, 60, 840, 300);
	rectangle(650, 50, 850, 310);


	////////////////////////////////////////////////////////////////////////
	//画数字键盘数字 & 计时器
	settextcolor(RGB(9, 74, 247));
	setlinestyle(PS_SOLID, 3);
	t2 = clock();
	second = (int)(double)(t2 - t1) / CLOCKS_PER_SEC;


	second -= sleepTime;
	minute = second / 60;
	second %= 60;
	_stprintf_s(str, _T("%02d:%02d"), minute, second);
	outtextxy(0, 0, str);


	/*_stprintf_s(str, _T("%d"), noMistake);
	outtextxy(400, 0, str);*/


	int n = 1;
	outtextxy(720, 250, _T("del"));
	for (int col = 0; col <= 2; col++)
	{
		for (int row = 10; row <= 12; row++)
		{
			_stprintf_s(str, _T("%d"), n++);
			outtextxy((row + 1) * 60 + 20, (col + 1) * 60 + 10, str);
		}
	}
	//用红框标注数字键盘中的当前所选数字
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 3);
	rectangle((numPos.X + 1) * 60, (numPos.Y + 1) * 60, (numPos.X + 2) * 60, (numPos.Y + 2) * 60);
	setfillcolor(RGB(249, 247, 176));


	///////////////////////////////////// 左下角  /////////////////////////////////////
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	settextstyle(30, 0, _T("宋体"));
	setfillcolor(RGB(158, 160, 169));

	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 350 && currentPos.Y < 400)
	{
		solidrectangle(660, 350, 840, 400);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLACK);
	outtextxy(670, 360, _T(" 暂    停"));


	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 420 && currentPos.Y < 470)
	{
		solidrectangle(660, 420, 840, 470);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLACK);
	outtextxy(670, 430, _T(" 重新开始"));
	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 490 && currentPos.Y < 540)
	{
		solidrectangle(660, 490, 840, 540);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLACK);
	outtextxy(670, 500, _T(" 退    出"));
	if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 560 && currentPos.Y < 610)
	{
		solidrectangle(660, 560, 840, 610);
		settextcolor(WHITE);
	}
	else
		settextcolor(BLACK);
	outtextxy(670, 570, _T(" 显示答案"));
	setfillcolor(BLACK);
	solidcircle(650, 380, 5);
	solidcircle(650, 450, 5);
	solidcircle(650, 520, 5);
	solidcircle(650, 590, 5);
	EndBatchDraw();
}
void GameUpdate()
{
	if (peekmessage(&msg, EM_MOUSE, true))
		msg = getmessage();

	int x = msg.x;
	int y = msg.y;
	switch (msg.message)
	{
	case WM_MOUSEMOVE:
		if (x > 60 && x < 600 && y > 60 && y < 600)
		{
			flag_w = 1;
			waitPos.X = (x - 60) / 60;
			waitPos.Y = (y - 60) / 60;
			coord.X = waitPos.Y;
			coord.Y = waitPos.X;
			coord = FindLeftUpperCornor(coord);
			if (Map1[waitPos.Y][waitPos.X])
				HeighLight(1);
			else
				HeighLight(0);
		}
		else
		{
			//消除红框
			flag_w = 0;
			//消除高亮
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					Map_HL[i][j] = 0;
		}
		currentPos.X = x;
		currentPos.Y = y;
		break;
	case WM_LBUTTONUP:
		if (x > 660 && x < 840 && y>60 && y < 240)
		{
			numPos.X = (x - 60) / 60;
			numPos.Y = (y - 60) / 60;
			num = 3 * numPos.Y + (numPos.X - 10) + 1;
		}
		else if (x > 720 && y > 240 && x < 780 && y < 300)
		{
			numPos.X = (x - 60) / 60;
			numPos.Y = (y - 60) / 60;
			num = 0;
		}
		else if (x > 60 && x < 600 && y > 60 && y < 600)
		{
			if (Map2[waitPos.Y][waitPos.X] == 1)
				Map1[waitPos.Y][waitPos.X] = num;
			else
			{
				clock_t t3, t4;
				t3 = clock();
				MessageBox(GetHWnd(), L"提示数字不可修改", L"注意", 0);
				t4 = clock();
				sleepTime += (int)(double)(t4 - t3) / CLOCKS_PER_SEC;
			}
			noMistake = FindMistake(gameMode);
			faults += noMistake;
		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 350 && currentPos.Y < 400)
		{
			clock_t t3, t4;
			t3 = clock();
			MessageBox(GetHWnd(), L"暂停中...", L"提示", 0);
			t4 = clock();
			sleepTime += (int)(double)(t4 - t3) / CLOCKS_PER_SEC;
		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 420 && currentPos.Y < 470)
		{
			clock_t t3, t4;
			t3 = clock();
			int result = MessageBox(GetHWnd(), _T("重新开始?"), _T("hello"), MB_YESNO);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
				restart = 1;
				break;
			}
			t4 = clock();
			sleepTime += (int)(double)(t4 - t3) / CLOCKS_PER_SEC;
		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 490 && currentPos.Y < 540)
		{
			int result=MessageBox(GetHWnd(), L"确认退出？", L"提示", MB_YESNO);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
				endGame = 1;
				break;
			}
			
		}
		else if (currentPos.X > 660 && currentPos.X < 840 && currentPos.Y > 560 && currentPos.Y < 610)
		{
			int result = MessageBox(GetHWnd(), L"显示答案", L"提示", MB_YESNO);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES: 
			{
				showanswer = 1;
				break;
			}
			}

		}
		break;
	default:
		break;
	}
	//the need of‘faults'
	msg.message = WM_MBUTTONUP;
}
void HeighLight(int post)
{
	int i, j;
	//清除上次的高亮数据
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			Map_HL[i][j] = 0;
	if (waitPos.Y >= 0 && waitPos.Y <= 8 && waitPos.X >= 0 && waitPos.X <= 8)
	{
		/*两种高亮模式*/
		if (post)//1.高亮相同的数字
		{
			for (i = 0; i < 9; i++)
				for (j = 0; j < 9; j++)
					if (Map1[i][j] == Map1[waitPos.Y][waitPos.X])
						Map_HL[i][j] = 1;


		}
		else//2.高亮同行、同列、同宫
		{
			for (i = 0; i < 9; i++)
				Map_HL[i][waitPos.X] = 2;
			for (i = 0; i < 9; i++)
				Map_HL[waitPos.Y][i] = 2;
			//2.1根据每一宫的左上角的行列来高亮对应的那一宫
			for (i = coord.X; i < coord.X + 3; i++)
				for (j = coord.Y; j < coord.Y + 3; j++)
					if (i >= 0 && i < 9 && j >= 0 && j < 9)
						Map_HL[i][j] = 2;
			if (gameMode == 0)
			{
				if (waitPos.Y == waitPos.X)
					for (int i = 0; i < 9; i++)
						Map_HL[i][i] = 2;
				if (waitPos.Y + waitPos.X == 8)
					for (int i = 0; i < 9; i++)
						Map_HL[i][8 - i] = 2;
			}
		}
	}


}
COORD FindLeftUpperCornor(COORD c1)
{
	COORD c2;
	for (int i = 0; i <= 6; i += 3)
	{
		c2.X = i;
		for (int j = 0; j <= 6; j += 3)
		{
			c2.Y = j;
			if (c1.X >= c2.X && c1.X <= c2.X + 2 && c1.Y >= c2.Y && c1.Y <= c2.Y + 2)
				return c2;
		}
	}
	//这是被迫加上的
	return c2;
}
int FindMistake(int mode)
{
	int i, j, r, c, post = 0;
	//清除上次的错误数据
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			Map_Mistake[i][j] = 0;
	//对每列检查错误
	for (i = 0; i < 9; i++)
	{
		int arr[10] = { 0 };
		for (j = 0; j < 9; j++)
			arr[Map1[i][j]]++;
		for (j = 0; j < 9; j++)
			if (arr[Map1[i][j]] >= 2 && Map1[i][j] != 0)
			{
				Map_Mistake[i][j] = 1;
				post = 1;
			}
	}
	//对每行检查错误
	for (i = 0; i < 9; i++)
	{
		int arr[10] = { 0 };
		for (j = 0; j < 9; j++)
			arr[Map1[j][i]]++;
		for (j = 0; j < 9; j++)
			if (arr[Map1[j][i]] >= 2 && Map1[j][i] != 0)
			{
				post = 1;
				Map_Mistake[j][i] = 1;
			}


	}
	//对每宫检查错误
	for (i = 0; i <= 6; i += 3)
	{
		for (j = 0; j <= 6; j += 3)
		{
			int arr[10] = { 0 };
			for (r = i; r <= i + 2; r++)
				for (c = j; c <= j + 2; c++)
					arr[(Map1[r][c])]++;
			for (r = i; r <= i + 2; r++)
				for (c = j; c <= j + 2; c++)
					if (arr[Map1[r][c]] >= 2 && Map1[r][c] != 0)
					{
						Map_Mistake[r][c] = 1;
						post = 1;
					}


		}
	}
	//对角线数独还需再判断对角线上数字是否符合条件
	if (mode == 0)
	{
		int arr[10] = { 0 };
		i = 0;
		while (i < 9)
			arr[Map1[i][i++]]++;
		i = 0;
		while (i < 9)
		{
			if (arr[Map1[i][i]] >= 2 && Map1[i][i] != 0)
			{
				Map_Mistake[i][i] = 1;
				post = 1;
			}
			i++;
		}
		int arrb[10] = { 0 };
		i = 0;
		while (i < 9)
			arrb[Map1[i][8 - i++]]++;
		i = 0;
		while (i < 9)
		{
			if (arrb[Map1[i][8 - i]] >= 2 && Map1[i][8 - i] != 0)
			{
				Map_Mistake[i][8 - i] = 1;
				post = 1;
			}
			i++;
		}


	}
	return post;
}
int WinJudge()
{
	int post = 1, P = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			if (Map1[i][j] == 0)
			{
				post = 0;
				P = 1;
				break;
			}
		if (P)
			break;
	}
	return post;
}
int judge_win() {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			if (Map1[i][j]!=sudoku[i][j])
			{
				return 0;
				
			}
	}
	return 1;
}
void GameInit(int post, int a[][9])
{
	//srand((unsigned)time(NULL));
	//int a[10];
	//int b[10] = { 0 };
	//for (int i = 1; i <= 9; i++)
	//{
	//	do {
	//		a[i] = rand() % 9 + 1;
	//	} while (b[a[i]]);
	//	b[a[i]]++;
	//}
	////现在两个数组a和c已经生成了对应关系了(很乱，但一一对应)
	////模式一(标准数独)
	//if (post)
	//{

	//	int map[9][9] = { {9,8,2,5,3,6,1,7,4},
	//	{4,3,6,7,1,9,5,8,2},
	//	{1,5,7,4,8,2,3,6,9},
	//	{8,4,5,6,2,7,9,3,1},
	//	{2,6,3,1,9,5,7,4,8},
	//	{7,1,9,8,4,3,2,5,6},
	//	{3,2,4,9,5,8,6,1,7},
	//	{6,9,1,3,7,4,8,2,5},
	//	{5,7,8,2,6,1,4,9,3} };


		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				Map1[i][j] = a[i][j];

	//}
	//else //对角线数独
	//{
	//	int map[9][9] = { {2,3,1,4,5,8,6,9,7},
	//	{5,4,7,6,9,3,2,1,8},
	//	{6,8,9,7,2,1,4,5,3},
	//	{8,9,6,1,4,5,3,7,2},
	//	{7,5,3,2,8,9,1,6,4},
	//	{1,2,4,3,6,7,9,8,5},
	//	{3,7,2,8,1,6,5,4,9},
	//	{4,6,5,9,7,2,8,3,1},
	//	{9,1,8,5,3,4,7,2,6} };


	//	for (int i = 0; i < 9; i++)
	//		for (int j = 0; j < 9; j++)
	//			Map1[i][j] = a[(map[i][j])];


	//}
	Dig(gameDifficulty);
}
void Dig(int post)
{
//	srand((unsigned)time(NULL));
//	int way[3][9] = { { 3,3,3,3,3,4,4,5,5 },
//	  { 4,4,4,4,4,5,5,6,6 },
//	  { 5,5,5,5,5,6,6,7,7 } };
//	int t[9] = { 0 };
//	int tmp[9] = { 0 }, n = 0;
//	for (int i = 0; i < 9; i++)
//	{
//		do {
//			n = rand() % 9;
//		} while (t[n]);
//		t[n]++;
//		tmp[i] = way[post][n];
//	}
//	int m = 0, x, y;
//	for (int i = 0; i < 9; i += 3)
//		for (int j = 0; j < 9; j += 3)
//		{
//			int dig[3][3] = { 0 };
//			for (int k = 0; k < tmp[m]; k++)
//			{
//				do {
//					x = rand() % 3;
//					y = rand() % 3;
//				} while (dig[x][y]);
//				dig[x][y] = 1;
//				Map2[i + x][j + y] = 1;//标记被挖去的位置
//			}
//			m++;
//
//
//		}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if(starting_grid[i][j]==0)
			Map2[i][j] = 1;
			if(Map2[i][j])
			Map1[i][j] = 0;
		}
			
	}
}
void react() {
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1);
	setfillcolor(RGB(158, 160, 169));
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 200;
	wcscpy_s(f.lfFaceName, _T("楷体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(30, 50, _T("YOU"));
	outtextxy(30, 350, _T("Fail!"));
	settextstyle(40, 0, _T("宋体"));


	outtextxy(550, 60, _T("游戏时间："));
	solidrectangle(550, 110, 850, 160);
	outtextxy(550, 190, _T("错误次数："));
	solidrectangle(550, 240, 850, 290);
	outtextxy(550, 330, _T("总得分  ："));
	solidrectangle(550, 380, 850, 430);


	TCHAR str[20];
	settextcolor(WHITE);
	_stprintf_s(str, _T("%02d分%02d秒"), minute, second);
	outtextxy(620, 110, str);
	_stprintf_s(str, _T("%d"), faults);
	outtextxy(680, 240, str);
	float a = (1 - (minute + (float)second / 60) / ((1) * 100)) * 20;
	float b = (float)(80 - faults) / 800 * 80;
	if ((minute * 60 + second) > (600 * (1)))
		a = 0;
	if (faults >= 30)
		b = 0;
	float scores = a + b;
	_stprintf_s(str, _T("%.2f"), scores);
	outtextxy(650, 380, str);
	Sleep(1000);
	int result = MessageBox(GetHWnd(), _T("再来一局?"), _T("hello"), MB_YESNO);
	switch (result)
	{
	case IDNO:
		endGame = 1;
		break;
	case IDYES:
		break;
	}
}
void end()
{
	setbkcolor(WHITE);
	settextcolor(BLACK);
	setbkmode(1);
	setfillcolor(RGB(158, 160, 169));
	cleardevice();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 200;
	wcscpy_s(f.lfFaceName, _T("楷体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(30, 50, _T("Good"));
	outtextxy(30, 350, _T("job!"));
	settextstyle(40, 0, _T("宋体"));


	outtextxy(550, 60, _T("完成时间："));
	solidrectangle(550, 110, 850, 160);
	outtextxy(550, 190, _T("错误次数："));
	solidrectangle(550, 240, 850, 290);
	outtextxy(550, 330, _T("总得分  ："));
	solidrectangle(550, 380, 850, 430);


	TCHAR str[20];
	settextcolor(WHITE);
	_stprintf_s(str, _T("%02d分%02d秒"), minute, second);
	outtextxy(620, 110, str);
	_stprintf_s(str, _T("%d"), faults);
	outtextxy(680, 240, str);
	float a = (1 - (minute + (float)second / 60) / ((1) * 10)) * 20;
	float b = (float)(80 - faults) / 80 * 80;
	if ((minute * 60 + second) > (600 * (1)))
		a = 0;
	if (faults >= 30)
		b = 0;
	float scores = a + b;
	_stprintf_s(str, _T("%.2f"), scores);
	outtextxy(650, 380, str);
	Sleep(1000);
	int result = MessageBox(GetHWnd(), _T("再来一局?"), _T("hello"), MB_YESNO);
	switch (result)
	{
	case IDNO:
		endGame = 1;
		break;
	case IDYES:
		break;
	}
	
}
