#include "zcs_item.h"


ZcsItem::ZcsItem(string &name, int row, int col,
		int normal_front_color, int normal_back_color,
		int select_front_color, int select_back_color)
{
	name_ = name;
	row_ = row;
	col_ = col;
	normal_front_color_ = normal_front_color;
	normal_back_color_ = normal_back_color;
	select_front_color_ = select_front_color;
	select_back_color_ = select_back_color;
}

void ZcsItem::paint(int select)
{
	printf("\033[%d;%dH", row_, col_);
	if(0 == select)
		printf("\033[%d;%d;1m%s\033[0m", normal_front_color_, normal_back_color_, name_.c_str());
	else
		printf("\033[%d;%d;1m%s\033[0m", select_front_color_, select_back_color_, name_.c_str());
	fflush(stdout);
}
