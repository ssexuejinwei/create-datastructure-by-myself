#include<iostream>
#include<vector>
using namespace std;
template<class T>
T r(vector<T>& c) {
	return c[0];
}

int main() {
	vector<int>a1{ 1,2,3 };
	int i = r(a1);
	return 0;
}