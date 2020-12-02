#include <iostream>
#include <fstream>

#include <unistd.h>

#include "zcs_list.h"

using namespace std;

const string get_conf_path()
{
	FILE *fp = popen("which se", "r");
	char buf[256];
	fgets(buf, sizeof(buf), fp);
	pclose(fp);

	int off = strlen(buf);
	for(;off >= 0 && buf[off] != '/'; off --);
	if(off >= 0)
	{
		buf[off] = 0;
	}

	string conf_path = (strlen(buf) == 0 ? string(".") : string(buf)) + "/ssh_elf.conf";
	//printf("[%s]\n", conf_path.c_str());
	return conf_path;
}

int main(int argc, char **argv)
{
	const string conf_path = get_conf_path();

	if(argc == 2)
	{
		ofstream ofs(conf_path.c_str(), ios::out);
		ofs << argv[1] << endl;
		ofs.close();
	}
	ifstream ifs(conf_path.c_str(), ios::in);
	ASSERT(ifs.is_open(), "set ssh_elf.conf first. (%s <path to shells>)", argv[0]);
	string root_dir;
	ifs >> root_dir;
	ifs.close();

	printf("\033[2J");//清屏
	printf("\033[?25l");//隐藏光标
	fflush(stdout);

	ZcsList zl;
	zl.init(root_dir);
	zl.paint();

	string shell_path = "";
	while(true)
	{
		struct termios old_tm, tm;
		ASSERT(tcgetattr(STDIN_FILENO, &old_tm) == 0, "");
		cfmakeraw(&tm);
		ASSERT(tcsetattr(STDIN_FILENO, TCSANOW, &tm) == 0, ""); //输入不回显，无需回车
		int c = getchar();
		ASSERT(tcsetattr(STDIN_FILENO, TCSANOW, &old_tm) == 0, "");//设置getchar()需要回车
		if(c == 'q')
		{
			break;
		}
		if(c == 13 && zl.confirm(shell_path) >= 0)
		{
			break;
		}
		else
		{
			switch(c)
			{
			case 65:
				zl.select("U");//up
				break;
			case 66:
				zl.select("D");//down
				break;
			case 67:
				zl.select("R");//right
				break;
			case 68:
				zl.select("L");//left
				break;
			}
		}
	}
	printf("\033[?25h");//显示光标
	zl.move_cursor_end();

	if(shell_path != "")
	{
		printf("\033[0;0H");
		printf("\033[2J");//清屏
		ZPBLUE("exec [%s]\n", shell_path.c_str());
		system(shell_path.c_str());
	}
	return 0;
}
