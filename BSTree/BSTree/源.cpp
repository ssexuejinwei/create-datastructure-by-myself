#include"BSTSystem.h"
void InitInterface() {
	cout << "**\t\t����������\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ���:\t**" << endl;
	cout << "**\t\t 1 --- ��������������\t**" << endl;
	cout << "**\t\t 2 --- ����Ԫ��\t\t**" << endl;
	cout << "**\t\t 3 --- ��ѯԪ��\t\t**" << endl;
	cout << "**\t\t 4 --- �˳�����\t\t**" << endl;
	cout << "==========================================" << endl;
	return;
}
int main() {
	InitInterface();
	BSTSystem bstsystem;
	bstsystem.Choose();
	return 0;
}