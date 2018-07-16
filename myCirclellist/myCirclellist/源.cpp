#include"CirList.h"
#include<iostream>
int main() {
	using namespace std;
	Cirlist<int> list;
	int x;
	int n, s, m, k;
	cin >> n >> s >> m >> k;
	LinkNode<int>* p;
	for (int i = 0; i < n; i++)
		list.Insert(i + 1, i + 1);
	p = list.locate(s);
	while (n > k) {
		for (int i = 1; i < m; i++) {
			if (p == list.getRear()) {
				p = list.getHead()->link;
				continue;
			}
			p = p->link;
		}
		LinkNode<int>* next;
		if (p == list.getRear()) {
			next = list.getHead()->link;
		}
		else
			next = p->link;
		list.Remove(x, p);
		p = next;
		cout << x << " ";
		n--;
	}
	return 0;
}