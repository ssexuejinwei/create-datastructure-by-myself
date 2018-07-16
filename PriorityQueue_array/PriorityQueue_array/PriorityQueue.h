#pragma once
#include<iostream>
//using namespace std;

class PriorityQueue {
	int* queue;
	int count;
	int maxSize;
public:
	PriorityQueue(int i) :maxSize(i) {
		count = 0;
		queue = new int[maxSize];
		if (queue == nullptr) {
			std::cerr << "ÄÚ´æ·ÖÅä´íÎó";
			exit(0);
		}
	}
	~PriorityQueue() {
		if (queue != nullptr)
			delete[] queue;
	}
	int* getQueue() { return queue; }
	bool isEmpty() { return count == 0; }
	bool isFull() { return count == maxSize; }
	int getSize()const { return count; }
	void makeEmpty() { count = 0; }
	bool Enqueue(int x);
	bool Dequeue(int& x);
	void adjust();
};

void PriorityQueue::adjust() {
	int  temp;
	for (int i = 1; i < count; i++) {
		if (queue[i] <= queue[i-1]) {
			temp = queue[i];
			int tag = i;
			while (tag > 0 && queue[tag - 1] > temp) {
				queue[tag] = queue[tag - 1];
				tag--;
			}
			queue[tag] = temp;
		}
	}
	return;
}

bool PriorityQueue::Enqueue(int x) {
	if (count == maxSize)return false;
	queue[count] = x;
	count++;
	adjust();
	return true;
}

bool PriorityQueue::Dequeue(int& x) {
	x = queue[0];
	for (int i = 1; i < count; i++)
		queue[i - 1] = queue[i];
	count--;
	return true;
}

/*ostream& operator<<(ostream& os, PriorityQueue& q) {
	for (int i = 0; i < q.getSize(); i++)
	{
		os << q.getQueue()[i];
	}
	return os;
}*/



