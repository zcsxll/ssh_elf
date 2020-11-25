#pragma once

#include <string>
#include <vector>

#include <dirent.h>
#include <term.h>

#include "common.h"
#include "zcs_item.h"

using namespace std;

class ZcsList
{
private:
	string root_dir_;

	int rows_;
	int cols_;
	int valid_rows_;
	int max_len_;
	int max_cnt_;

	int selected_;
	vector<ZcsItem> items_;

public:
	ZcsList();
	~ZcsList();

	int init(const string &path);
	void paint();
	int select(const string &cmd);
	int confirm(string &shell_path);
	void move_cursor_end()
	{
		int last_row = items_.size() >= valid_rows_ ? valid_rows_ : items_.size();
		printf("\033[%d;0H", last_row + 2);
	}
};
