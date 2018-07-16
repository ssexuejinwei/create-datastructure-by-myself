#pragma once
template<typename t>
struct linkNode{
	linkNode<t>* rlink;
	linkNode<t>* llink;
	t value;
	linkNode(t i, linkNode<t>* lp = nullptr, linkNode<t>*rp = nullptr) :value(i), llink(lp), rlink(rp) {};
	linkNode(linkNode<t>* lp = nullptr, linkNode<t>*rp = nullptr) :llink(lp), rlink(rp) {};
};

template<class t>                   //双向循环链表
class dbllist {
	linkNode<t>* first;
	linkNode<t>* last;
public:
	dbllist(linkNode<t>* ptr = nullptr) {
		first = new linkNode<t>(0);
		last = new linkNode<t>;
		first->rlink = first;
		first->llink = first;
		last = first;
	}
	int length() {
		linkNode<t>* current = new linkNode<t>;
		current = first->rlink;
		int count(0);
		while (current != first) {
			current = current->rlink;
			count++;
		}
		delete current;
		return count;
	}
	linkNode<t>* locate(int i, int d) {
		if (first->rlink == first || i == 1)return first;
		linkNode<t>* current = new linkNode<t>;
		if (d != 0) {
			current = first;
			int count = 1;
			while (count < i) {
				//if (current == first)break;
				current = current->rlink;
				count++;
			}
			//if (current != first)
			return current;
			//else
			//	return nullptr;
		}
		else {
			current = first->llink;
			int count = 1;
			while (count < i) {
				//if (current == first)break;
				current = current->llink;
				count++;
			}
			//if (current != first)
			return current;
			//else
			//	return nullptr;
		}
	}
	bool Insert(int i, t value, int d) {            //d=0,按照前驱方向，d!=0按照后继方向
		linkNode<t>* current = new linkNode<t>;
		linkNode<t>* newNode = new linkNode<t>(value);
		current = locate(i, d);
		if (current == nullptr)return false;
		if (current == first) {
			first->value = value;
			return true;
		}
		if (d != 0) {
				newNode->rlink = current->rlink;
				current->rlink = newNode;
				newNode->rlink->llink = newNode;
				newNode->llink = current;
				return true;
			}
		else {
				newNode->llink = current->llink;
				current->llink = newNode;
				newNode->rlink = current;
				newNode->llink->rlink = newNode;
				return true;
			}
	}
	bool Remove(int i, int d,t&  value) {
		linkNode<t>* current = locate(i, d);
		if (current == nullptr)return false;
		current->llink->rlink = current->rlink;
		current->rlink->llink = current->llink;
		value = current->value;
		delete current;
	}
	bool exchage(int i, int d) { 
		linkNode<t>* current = locate(i, d);
		if (current == first)return false;
		if (d != 0) {
			linkNode<t>*next = current->rlink;
			linkNode<t>*p = current->llink;
			linkNode<t>*q = next->rlink;
			p->rlink = next;
			q->llink = current;
			next->llink = p;
			current->rlink = q;
			next->rlink = current;
			current->llink = next;
			return true;
		}
		else {
			linkNode<t>*next = current->llink;
			linkNode<t>*p = current->rlink;
			linkNode<t>*q = next->llink;
			p->llink = next;
			next->rlink = p;
			q->rlink = current;
			current->llink = q;
			current->rlink = next;
			next->llink = current;
			return true;
		}
	}//交换第i个和之后的一个值
};
