# COMSHOMEWORK
通软作业及源码

src:源码目录
bin:编译好的可执行文件目录

homework3:
/* filename:test2.h */ extern int add(int i, int j); 
/* filename:test2.c */ int add(int i, int j) { return i + j; }; 
/* filename:test.c */ #include "test2.h" main() { int a, b; a = 2; b = 3; printf("the sum of a+b is %d", add(a + b)); }; 上述三段代码分属三个文件，文件名在注释中已给出，编写编译上述三个文件的makefile，上传代码及运行截图。 使用gdb工具查看add函数中 i 的值，上传截图；


homework4:
例1：设计一个程序以只读方式打开系统配置文件“/etc/inittab”
例1改进：设计一个程序以只读方式打开系统配置文件“/etc/inittab”，从中读取100个字符并打印。
例2：设计一个程序，打开当前目录下文件“./test”写入字符串“Hello,welcome to CQUPT!” 。


homework5:
1、新建名为自己学号的文本文件，并将名为test_file_1.txt的文件中第200-300个字符及最后100个字符copy到新建的文件中。（需要考虑异常情况的处理，文件在“已共享的文件”中） 
2、将名为test_file_1.txt的文件打开，获取它的类型并显示其相关时间信息后。然后将它的长度截断至你学号尾号的长度，但维持它的访问时间和修改时间不变。 
3、在你的主目录下创建名为你的学号的文件夹，并改变其为当前目录。将test_file_1.txt和test_file_2.txt文件cope到当前目录，并读取当前目录文件，显示当前目录下文件的名称及相关时间、大小等信息。


homework8:
编译共享文件中的ex6-1.c和ex6-2.c，运行并上传截图。


homework9:
进程间通信_利用fifo实现简单的本地聊天功能（可反复聊天 ）

shixun_msg:
编写利用消息队列进行通信的程序，其中一个进程读入指定文件的内容，另外一个进程显示读取的内容

homework 10:
编译7-1和7-2
