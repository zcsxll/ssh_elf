#include "zcs_list.h"

ZcsList::ZcsList()
{
	root_dir_ = "";

	ASSERT(setupterm(NULL, fileno(stdout), NULL) == 0, "");
	rows_ = tigetnum((char*)"lines");
    cols_ = tigetnum((char*)"cols");
	valid_rows_ = rows_ - 10;
	max_len_ = (cols_ - 12) / 3;
	max_cnt_ = valid_rows_ * 3;
	//printf("%d %d\n", valid_rows_, max_cnt_);

	selected_ = -1;
}

ZcsList::~ZcsList()
{
}

int ZcsList::init(const string &path)
{
	root_dir_ = path;

	DIR *dir = opendir(path.c_str());
	struct dirent *d;
	items_.clear();
	vector<string> v;
	while((d = readdir(dir)) != NULL)
	{
		if(d->d_type != DT_REG)
			continue;
		string name = d->d_name;
		if(name.rfind(".sh") != name.length() - 3)
			continue;
		ASSERT(name.length() <= max_len_, "length of \"%s\" > %d", name.c_str(), max_len_);
		v.push_back(name);
		ASSERT(v.size() <= max_cnt_, "not implemented");
	}
	sort(v.begin(), v.end());

	for(int i = 0, row = 0, col = 0; i < v.size(); i ++)
	{
		items_.push_back(ZcsItem(v[i], row + 1, col + 1));
		row ++;
		if(row >= valid_rows_)
		{
			row = 0;
			col += (max_len_ + 4);
		}
	}
	return 0;
}

void ZcsList::paint()
{
	for(int i = 0; i < items_.size(); i ++)
	{
		items_[i].paint(0);
	}
}

int ZcsList::select(const string &cmd)
{
	if(selected_ < 0)
	{
		selected_ = 0;
	}
	else
	{
		items_[selected_].paint(0);
		if(cmd == "D")
		{
			selected_ = (selected_ + 1) % items_.size();
		}
		else if(cmd == "U")
		{
			selected_ = selected_ > 0 ? selected_ - 1 : items_.size() - 1;
		}
		else if(cmd == "L")
		{
			if(selected_ >= valid_rows_)
			{
				selected_ = selected_ - valid_rows_;
			}
			else
			{
				for(; selected_ + valid_rows_ < items_.size(); selected_ += valid_rows_);
			}
		}
		else if(cmd == "R")
		{
			if(selected_ + valid_rows_ < items_.size())
			{
				selected_ = selected_ + valid_rows_;
			}
			else
			{
				for(; selected_ - valid_rows_ >= 0; selected_ -= valid_rows_);
			}
		}
	}
	items_[selected_].paint(1);
	return 0;
}

int ZcsList::confirm(string &shell_path)
{
	if(selected_ < 0)
	{
		shell_path = "";
		return -1;
	}
	shell_path = root_dir_ + "/" + items_[selected_].name_;
	return selected_;
}
