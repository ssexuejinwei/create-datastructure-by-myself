#pragma once
template<typename Type>
class Cirlist;

template<typename Type>
class LinkNode {
	friend class Cirlist<Type>;
public:
	Type data;
	LinkNode<Type>* link;
	LinkNode<Type>(LinkNode<Type>*ptr = nullptr) { link = ptr; }
	LinkNode<Type>(const Type& item, LinkNode<Type>*ptr = nullptr) {
		data = item;
		link = ptr;
	}
};

template<typename Type>
class Cirlist {
	LinkNode<Type>* first;
	LinkNode<Type>* last;
public:
	Cirlist(){
		first = new LinkNode<Type>;
		first->link = first;
		last = first;
	}
	~Cirlist() {if (!IsEmpty()) makeEmpty();}
	void makeEmpty();
	int Length()const;
	bool IsEmpty() { return first->link == first ? true : false; }
	LinkNode<Type>* getHead()const { return first; };
	LinkNode<Type>* getRear()const { return last; }
	LinkNode<Type>* Search(Type x);
	LinkNode<Type>* locate(int i);
	Type* getData(int i);
	void setData(Type& x, int i);
	bool Insert(Type x, int i);
	bool Remove(Type& x, int i);
	bool Remove(Type& x, LinkNode<int>* ptr);
};

template<typename Type>
void Cirlist<Type>::makeEmpty() {
	LinkNode<Type>* temp;
	while (first->link != first) {
		temp = first->link;
		first->link = temp->link;
		delete temp;
	}
}

template<typename Type>
int Cirlist<Type>::Length()const {
	int i = 0;
	LinkNode<Type>* p;
	p = getHead();
	while (p->link != first) {
		i++;
		p = p->link;
	}
	return i;
}

template<typename Type>
LinkNode<Type>* Cirlist<Type>::locate(int i) {
	if (i < 0)return nullptr;
	if (0 == i)return first;
	LinkNode<Type>* current;
	current = getHead()->link;
	int count(1);
	while (count < i&&current->link!= first) {
		count++;
		current = current->link;
	}
	return current;
}

template<typename Type>
LinkNode<Type>* Cirlist<Type>::Search(Type x) {
	if (IsEmpty())return nullptr;
	LinkNode<Type>* current;
	current = getHead()->link;
	//if (current->data == x)return current;
	while (current->link != first) {
		if (current->data == x)break;
		current = current->link;
	}
	if (current->data != x)return nullptr;
	return current;
}

template<typename Type>
Type* Cirlist<Type>::getData(int i) {
	LinkNode<Type>* p = locate(i);
	return &(p->data);
}

template<typename Type>
void Cirlist<Type>::setData(Type& x, int i) {
	if (i < 0)return;
	LinkNode<Type>* current = locate(i);
	current->data = x;
}

template<typename Type>
bool Cirlist<Type>::Insert(Type x, int i) {
	if (i < 0)return false;
	LinkNode<Type>* current = locate(i-1);
	LinkNode<Type>* newNode = new LinkNode<Type>(x);
	if (newNode == nullptr) {
		std::cerr << "ÄÚ´æ·ÖÅä´íÎó";
		exit(0);
	}
	//if (current == nullptr)return false;
	newNode->link = current->link;
	current->link = newNode;
	last = locate(Length());
	return true;
}

template<typename Type>
bool Cirlist<Type>::Remove(Type& x, int i) {
	if (i <=0 )return false;
	if (IsEmpty())return false;
	else {
		LinkNode<Type>* current = locate(i - 1);
		LinkNode<Type>* temp;
		temp = current->link;
		x = temp->data;
		current->link = temp->link;
		delete temp;
		last = locate(Length());
		return true;
	}
}

template<typename Type>
bool Cirlist<Type>::Remove(Type& x, LinkNode<int>* ptr) {
	LinkNode<int>* pre=nullptr;
	if (IsEmpty())return false;
	if (ptr == getHead())return false;
	for (int i = 0; i <= Length(); i++) {
		if (ptr == locate(i)) {
			pre = locate(i - 1);
			break;
		}
	}
	LinkNode<Type>* temp;
	if (ptr == nullptr)return false;
	temp = ptr;
	pre->link = temp->link;
	x = temp->data;
	delete temp;
	last = locate(Length());
	return true;
}
