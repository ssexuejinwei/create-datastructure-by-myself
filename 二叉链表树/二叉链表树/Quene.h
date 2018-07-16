#pragma once
template<typename Type>
struct LinkNode {
	Type value;
	LinkNode<Type>* link;
	LinkNode(Type x, LinkNode<Type>*ptr = nullptr) :value(x), link(ptr) {};
	LinkNode(LinkNode<Type>*ptr = nullptr) : link(ptr) {};
};

template<typename Type>
class LinkedQueue{
	LinkNode<Type>* rear;
	LinkNode<Type>* front;
public:
	LinkedQueue():rear(nullptr),front(nullptr) {};
	~LinkedQueue() { make_empty(); }
	void make_empty();
	bool is_empty() { return front == nullptr; }
	bool Enqueue(const Type&x);
	bool Dequeue(Type& x);
	int getSize();
	LinkedQueue<Type>* getFront() { return front; }
};

template<typename Type>
void LinkedQueue<Type>::make_empty() {
	if (front == nullptr)return;
	LinkNode<Type>* p; //= new LinkNode<Type>;
	while (front != nullptr) {
		p = front;
		front = front->link;
		delete p;
	}
}

template<typename Type>
bool LinkedQueue<Type>::Enqueue(const Type&x) {
	LinkNode<Type>* newNode = new LinkNode<Type>(x);
	if (newNode == nullptr)return false;
	LinkNode<Type>* p = new LinkNode<Type>;
	if (front == nullptr) {
		front = rear = newNode;
	}
	else {
		rear->link = newNode;
		rear = newNode;
	}
	return true;
}

template<typename Type>
bool LinkedQueue<Type>::Dequeue(Type&x) {
	if (is_empty())return false;
	LinkNode<Type>* p;// = new LinkNode<Type>;
	p = front;
	x = p->value;
	front = front->link;
	delete p;
	return true;
}

template<typename Type>
int LinkedQueue<Type>::getSize() {
	if (is_empty())return 0;
	int count = 0;
	LinkNode<Type>*p = new LinkNode<Type>;
	p = front;
	while (p != nullptr) {
		p = p->link;
		count++;
	}
	return count;
}
