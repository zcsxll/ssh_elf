#pragma once

#include <iostream>
#include <string>

using namespace std;

class ZcsItem
{
public:
	string name_;
	int row_;
	int col_;
	int normal_front_color_;
	int normal_back_color_;
	int select_front_color_;
	int select_back_color_;

	ZcsItem(string &name, int row, int col,
			int normal_front_color = 37, int normal_back_color = 40,
			int select_front_color = 30, int select_back_color = 47);
	void paint(int selected = 0);
};
