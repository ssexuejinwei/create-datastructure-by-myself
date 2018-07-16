#include"BSTSystem.h"
void InitInterface() {
	cout << "**\t\t二叉排序树\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t请选择要执行的操作:\t**" << endl;
	cout << "**\t\t 1 --- 建立二叉排序树\t**" << endl;
	cout << "**\t\t 2 --- 插入元素\t\t**" << endl;
	cout << "**\t\t 3 --- 查询元素\t\t**" << endl;
	cout << "**\t\t 4 --- 退出程序\t\t**" << endl;
	cout << "==========================================" << endl;
	return;
}
int main() {
	InitInterface();
	BSTSystem bstsystem;
	bstsystem.Choose();
	return 0;
}