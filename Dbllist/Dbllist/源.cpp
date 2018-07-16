#include<iostream>
#include"БъЭЗ.h"
using namespace std;
int main() {
	int num;
	dbllist<int> mydbllist;
	for (int i = 0; i < 5; i++) {
		cin >> num;
		mydbllist.Insert(i+1, num, 1);
	}
	//mydbllist.Remove(2, 1, num);
	//cout << num;
	//mydbllist.exchage(2, 0);
	//mydbllist.Insert(mydbllist.length()-1,num, 1);
	//cout << mydbllist.length();
	return 0;
}