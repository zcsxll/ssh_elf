# ssh_elf
把指定目录的sh脚本文件名称显示在终端上，通过方向键选择脚本，回车键执行脚本

# 编译
先在ssh_elf目录创建文件夹obj，然后make

# 安装和使用
【1】创建一些可以运行的sh文件，放在某个目录中，比如/Users/xxx/shells  
【2】./ssh_elf /Users/xxx/shells  
【3】./ssh_elf

# 效果
如下图，通过四个方向键调整选定的脚本，按回车键执行脚本并退出，按q直接退出
<p align="left">
<img src="https://github.com/zcsxll/ssh_elf/blob/main/ui.jpg" width="600">
</p>
