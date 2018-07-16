#pragma once
#include<iostream>
using namespace std;

const int defaultSize = 10;
template<class T>
class MinHeap {
	T* heap;
	int currentSize;
	int maxHeapSize;
	void shiftDown(int start, int m);
	//��start��m�»�����Ϊ��С��
	void shiftUp(int start);
	//��start��0�ϻ�������Ϊ��С��
public:
	MinHeap(int size = defaultSize) {
		maxHeapSize = (defaultSize < size) ? size : defaultSize;
		heap = new T[maxHeapSize];
		if (heap == nullptr) {
			cerr << "�ڴ�������";
			exit(1);
		}
		currentSize = 0;
	}
	MinHeap(T arr[], int n) {
		maxHeapSize = (defaultSize < n) ? n : defaultSize;
		heap = new Type[maxHeapSize];
		if (heap == nullptr) {
			cerr << "�ڴ�������";
			exit(1);
		}
		for (int i = 0; i < n; i++) {
			heap[i] = arr[i];
		}
		currentSize = n;
		int currentPos = (currentPos - 2) / 2;
		//����֧���
		while (currentPos>=0)
		{
			shiftDown(currentPos, currentSize - 1);
			currentPos--;
		}
	}
	~MinHeap() {
		if (heap != nullptr)
			delete []heap;
	}
	bool Insert(const T& x);
	bool RemoveMin(T& x);
	bool Isempty()const {
		return currentSize == 0;
	}
	bool Isfull()const {
		return currentSize == maxHeapSize;
	}
	void MakeEmpty() { currentSize = 0; }
};

template<class T>
void MinHeap<T>::shiftDown(int start, int m) {
	//һֱ���±Ƚ�
	int i = start, j = 2 * i + 1;
	//j��ʾ����Ů��λ��
	T temp = heap[i];
	while (j <= m) {
		if (j<m&&heap[j]>heap[j + 1])j++;
		if (temp < heap[j])break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * i + 1;
			//С����Ů���ƣ����Ҽ������µ���
		}
	}
	heap[i] = temp;
}

template<class T>
void MinHeap<T>::shiftUp(int start) {
	//�ӽ��start��ʼ�����0Ϊֹ�����¶��ϱȽ�
	int j = start, i = (j - 1) / 2;
	T temp = heap[j];
	while (j > 0) {
		if (heap[i] <= temp)break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (j - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<class T>
bool MinHeap<T>::Insert(const T& x) {
	if (Isfull())return false;
	heap[currentSize] = x;
	shiftUp(currentSize);
	currentSize++;
	return true;
}

template<class T>
bool MinHeap<T>::RemoveMin(T& x) {
	if (Isempty())return false;
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	shiftDown(0, currentSize - 1);
	return true;
}