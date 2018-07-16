#pragma once
#include<assert.h>

template<typename Type>
struct LinkNode {
	Type value;
	LinkNode<Type>* link;
	LinkNode(Type x, LinkNode<Type>*ptr = nullptr) :value(x), link(ptr) {};
	LinkNode(LinkNode<Type>*ptr = nullptr) : link(ptr) {};
};

template<typename Type>
class LinkedStack {
	LinkNode<Type>* top;
public:
	LinkedStack() :top(nullptr) {};
	~LinkedStack() { make_empty(); }
	void make_empty();
	int getSize()const;
	bool Isempty() { return top == nullptr; }
	void Push(const Type& x);                           //进栈
	bool Pop(Type& x);                            //出栈        
	bool getTop(Type& x);                              //获取栈顶元素
};

template<typename Type>
void LinkedStack<Type>::make_empty() {
	if (top == nullptr)return;
	LinkNode<Type>* p = new LinkNode<Type>;
	while (top != nullptr) {
		p = top;
		top = top->link;
		delete p;
	}
}

template<typename Type>
int LinkedStack<Type>::getSize()const {
	int count = 0;
	LinkNode<Type>* p = new LinkNode<Type>(top);
	while (p->link != nullptr) {
		p = p->link;
		count++;
	}
	return count;
}

template<typename Type>
void LinkedStack<Type>::Push(const Type& x) {
	top = new LinkNode<Type>(x,top);
	assert(top != NULL);
}

template<typename Type>
bool LinkedStack<Type>::Pop(Type& x) {
	if (Isempty())return false;
	LinkNode<Type>* p = new LinkNode<Type>;
	p = top;
	x = p->value;
	top = top->link;
	delete p;
	return true;
}

template<typename Type>
bool LinkedStack<Type>::getTop(Type& x) {
	if (Isempty())return false;
	x = top->value;
	return true;
}






