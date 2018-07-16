#include"Quene.h"
#include<iostream>
using namespace std;
void YANGVI(int n) {
	LinkedQueue<int> queue;
	queue.Enqueue(1);
	queue.Enqueue(1);
	int s = 0, t = 0, k = 0, u;
	for (int i = 1; i < n + 1; i++) {
		cout << endl;
		queue.Enqueue(k);
		for (int j = 1; j <= i + 2; j++) {
			queue.Dequeue(t);
			u = s + t;
			s = t;
			queue.Enqueue(u);
			if(s!=0)cout << s << '\t';
		}
	}
}
int main() {
	/*LinkedQueue<int> queue;
	for (int i = 0; i < 4; i++) {
		queue.Enqueue(i);
	}
	int num = queue.getSize();
	queue.Dequeue(num);
	queue.Dequeue(num);
	queue.make_empty();*/
	int num;
	cin >> num;
	YANGVI(num);
	return 0;
}