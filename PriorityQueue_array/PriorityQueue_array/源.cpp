#include"PriorityQueue.h"
int main() {
	int N;
	std::cin >> N;
	int num;
	PriorityQueue PQueue(N);
	for (int i = 0; i < N; i++) {
		std::cin >> num;
		PQueue.Enqueue(num);
	}
	int sum_cost = 0;
	int a, b;
	while (PQueue.getSize()>1) {
		PQueue.Dequeue(a);
		PQueue.Dequeue(b);
		PQueue.Enqueue(a + b);
		sum_cost += a + b;
	}
	//将前两个最小的相加，并且入队，在加到总费用上去
	std::cout << sum_cost;
	return 0;
}