#pragma once
template<class Type>
struct LinkNode {
	Type value;
	LinkNode<Type>* link;
	LinkNode(Type i, LinkNode<Type>* ptr = nullptr) :value(i), link(ptr) {};
	LinkNode(LinkNode<Type>* ptr = nullptr) :link(ptr) {};
};

template<class Type>
class Linklist {
	LinkNode<Type>* first;
public:
	Linklist(Type value,LinkNode<Type>*ptr=nullptr) {
		first = new LinkNode<Type>(ptr);
		first->value = value;
	}
	Linklist(LinkNode<Type>*ptr = nullptr) {
		first = new LinkNode<Type>(ptr);
	};
	~Linklist() { make_empty(); }
	void make_empty();
	LinkNode<Type>* getfirst() { return first; }
	LinkNode<Type>* locate(int i);
	LinkNode<Type>* Search(Type& x);
	bool Is_empty() { return first == nullptr; }
	bool Insert(int i, Type value);
	bool remove(int i, Type& x);
};

template<class Type>
void Linklist<Type>::make_empty() {
	if (Is_empty())return;
	else {
		LinkNode<Type>* temp = new LinkNode<Type>;
		while (first->link != nullptr) {
			temp=first->link;
			first = temp->link;
			delete temp;
		}
		return;
	}
}

template<class Type>
LinkNode<Type>* Linklist<Type>::locate(int i) {
	if (i < 0)return nullptr;
	else {
		LinkNode<Type>* current = first;
		int count = 0;
		while (count < i&&current != nullptr) {
			current = current->link;
			count++;
		}
		return current;
	}
}

template<class Type>
LinkNode<Type>*  Linklist<Type>::Search(Type& x) {
	LinkNode<Type>*current = first->link;
	while (current->value != x&&current != nullptr) {
		current = current->link;
	}
	return currrent;
}

template<class Type>
bool Linklist<Type>::Insert(int i, Type value) {                          //插入到第i个位置
	if (i < 0)return false;
	LinkNode<Type>* current = locate(i-1);               
	LinkNode<Type>* newNode = new LinkNode<Type>(value);
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

template<class Type>
bool Linklist<Type>::remove(int i, Type& x) {
	if (i <= 0)return false;
	LinkNode<Type>* preptr = locate(i - 1);
	LinkNode<Type>* temp = new LinkNode<Type>;
	temp = preptr->link;
	preptr->link = temp->link;
	x = temp->value;
	delete temp;
	return true;
}