#include<iostream>
#include"LinkedStack.h"
using namespace std;
int main() {
	LinkedStack<int> stack;
	for (int i = 0; i < 5; i++) {
		stack.Push(i);
	}
	int num(0);
	stack.getTop(num);
	return 0;
}