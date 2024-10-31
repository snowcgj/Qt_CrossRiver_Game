#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y)
{
	HANDLE h;//句柄,对象的索引
	COORD c;//结构体,坐标值
	c.X = x;
	c.Y = y;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}
void hide_cursor()
{
	HANDLE	h_GAME = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME, &cursor_info);
	cursor_info.bVisible = false;					//不显示光标
	SetConsoleCursorInfo(h_GAME, &cursor_info);
}
void show_cursor()
{
	HANDLE	h_GAME = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME, &cursor_info);
	cursor_info.bVisible = true;					//显示光标
	SetConsoleCursorInfo(h_GAME, &cursor_info);
}
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
class river
{
	string s, yuan, s1;
	int m = lev + 1, n = lev - 1, t = lev;
	clock_t t1, t2;
	int q = m, w = n, e = t;
	int state1 = 1, state2 = 1;
	int lev;
public:
	river()
	{
		lev = 2;
		int state1 = 1, state2 = 1;
		hide_cursor();
		t1 = clock();
		hide_cursor();
		s.append(lev, 'A'); s.append(1, ' '); s.append(lev, 'B');
		yuan.append(lev, 'B'); yuan.append(1, ' '); yuan.append(lev, 'A');
		s1 = s;
	}
	void Find(int& m, int& n, int& t, int& state1, int& state2)
	{
		int a, b, c;
		q = m, w = n, e = t;//保留原来的状态
		a = s.find(' ', 0);
		b = s.find('B', a);
		c = s.rfind('A', a);
		m = b, n = c, t = a;
		if (fabs(a - b) > 2 || (b == s.string::npos))
		{
			state1 = 0; m = q;
		}//意味着不能将“↑”继续向上移动了
		if (fabs(a - c) > 2 || (c == s.string::npos))
		{
			state2 = 0; n = w;
		}//意味着不能将“↓”继续向下移动了
	}
	void swapb()
	{
		s[t] = 'B';
		s[m] = ' ';
	}
	void swapa()
	{
		s[t] = 'A';
		s[n] = ' ';
	}
	void draw()
	{
		for (int i = 0; i < (2 * lev) + 1; ++i)
		{
			if (s[i] == 'B') {
				gotoxy(40, 20 + i * 2);
				cout << "↑";
			}
			else if (s[i] == 'A')
			{
				gotoxy(40, 20 + i * 2);
				cout << "↓";
			}
		}
	}
	void check_d()
	{
		if (s == yuan)
		{
			++lev;
			gotoxy(6, 6);
			cout << "第" << lev << "关开始了" << endl;
			m = lev + 1, n = lev - 1, t = lev;
			/*t2 = clock();
			if(clock()-t2>1000)
				system("cls");
			t2 = clock();*/
			t1 = clock();
			string s2, y2;
			s2.append(lev, 'A'); s2.append(1, ' '); s2.append(lev, 'B');
			y2.append(lev, 'B'); y2.append(1, ' '); y2.append(lev, 'A');
			s = s2; yuan = y2; s1 = s;
			cout << s1 << endl;
		}
	}
	void erase()
	{
		for (int i = 0; i < lev * 2 + 1; ++i)
		{
			gotoxy(40, 20 + i * 2);
			cout << "     ";
		}
	}
	void move()
	{
		while (1)
		{
			if (clock() - t1 > 500)
			{
				state1 = 1, state2 = 1;
				Find(m, n, t, state1, state2);
				if (GetAsyncKeyState(VK_UP) && state1)
					swapb();
				if (GetAsyncKeyState(VK_DOWN) && state2)
					swapa();
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					cout << "sorry,you fail" << endl;
					exit(0);
				}
				if (GetAsyncKeyState(VK_NUMPAD0))
				{
					s = s1;
					m = lev - 1, n = lev + 1, t = lev;
					q = m, w = n, e = t;
					state1 = 1, state2 = 1;
				}
				erase();
				draw();
				check_d();
				t1 = clock();
			}
		}
	}
	~river()
	{
		show_cursor();
	}
};
int main()
{
	river sd;
	sd.move();
}