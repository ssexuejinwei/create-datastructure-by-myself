#pragma once
/*ͼ����ӱ��ʾ����*/
#include<iostream>
#include<vector>
#include"MinHeap.h"
#include"UFSets.h"
using namespace std;
const int DefaultVertices = 30;

template<class T,class E>
struct Edge {
	//�߽��Ķ���
	int dest;
	//�ߵ���һ���λ��
	E cost;
	//���ϵ�Ȩֵ
	Edge<T,E>* link;
	//��һ������ָ��
	Edge() {}
	Edge(int num,E weight):dest(num),cost(weight),link(nullptr){}
	bool operator!=(Edge<T,E>& R)const {
		//�жϱ߲���
		return (dest != R.dest) ? true : false;
	}
};

template<class T,class E>
struct Vertex {
	//����Ķ���
	T data;
	//���������
	Edge<T,E>* adj;
	//�������ͷָ��
};

template<class T, class E>
struct MSTEdgeNode {
	int tail, head;
	E key;
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
	bool operator<=(MSTEdgeNode<T, E>& R) { return key <= R.key; }
	bool operator<(MSTEdgeNode<T, E>& R) { return key < R.key; }
	bool operator>(MSTEdgeNode<T, E>& R) { return key < R.key; }
};

template<class T,class E>
class Graphlnk {
private:
	Vertex<T,E>* NodeTable;
	//��������������ͷ���
	int numEdges;
	//��ǰ����
	int numVertices;
	//��ǰ������
	int maxVertices;
	//ͼ����󶥵���
	
public:
	/*friend istream& operator >> (istream& in, Graphlnk<T>& G);
	//��������*/
	//friend ostream& operator<<(ostream& out, Graphlnk<T,E>& G);
	//�������
	Graphlnk(int sz = DefaultVertices); 
	~Graphlnk();
	int getVertexPos(const T vertex);
	//����������ͼ�е�λ��
	int NumberOfVertices() { return numVertices; }
	int NumberOfEdges() { return numEdges; }
	T getValue(int i) {
	//ȡλ��Ϊi�Ķ����е�ֵ
		return (i >= 0 && i < numVertices)? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);
	//���ر�(v1,v2)�ϵ�Ȩֵ
	bool insertVertex(const T& vertex);
	//��ͼ�в���һ������
	bool removeVertex(int v);
	//��ͼ��ɾ��һ������v
	bool insertEdge(int v1, int v2, E const);
	//��ͼ�в���һ����(v1,v2)
	bool removeEdge(int v1, int v2);
	//��ͼ��ɾ��һ����(v1,v2)
	int getFirstNeighbor(int v);
	//ȡ����v�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);
	//ȡv���ڽӶ���w����һ���ڽӶ���
	friend void Kruskal(Graphlnk<T, E>& G, vector < MSTEdgeNode<T, E>>& vec);
	friend void Prim(Graphlnk<T, E>& G, const T u0,vector < MSTEdgeNode<T, E>>& vec);
};

template<class T, class E>
ostream& operator<<(ostream& out, Graphlnk<T, E>& G) {
	int j, v, e;
	T e1, e2; E w;
	v = G.NumberOfVertices();
	e = G.NumberOfEdges();
	out << v << "," << e << endl;
	for (int i = 0; i < v; i++) {
		for (j = i + 1; j < v; j++) {
			w = G.getWeight(i, j);
			if (w > 0) {
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << e1 << "-(" << w << ") - "<< e2 << endl;
			}
		}
	}
	return out;
};


template<class T,class E>
int Graphlnk<T,E>::getVertexPos(const T vertex) {
	//��������vertex��ͼ�е�λ��
	for (int i = 0; i < numVertices; i++) {
		if (NodeTable[i].data== vertex)
			return i;
	}
	return -1;
}

template<class T, class E>
Graphlnk<T,E>::Graphlnk(int sz){
	//���캯������һ���յ��ڽӱ�
	maxVertices=sz;
	numVertices=0;
	numEdges=0;
	NodeTable=new Vertex<T,E>[maxVertices];
	//�������������
	if(NodeTable==nullptr)
	{
		cerr<<"�ڴ�������!"<<endl;
		exit(1);
	}
	for (int i = 0; i < maxVertices; i++)
		NodeTable[i].adj=nullptr;
};

template<class T, class E>
Graphlnk<T,E>::~Graphlnk(){
	//�������� ɾ��һ���ڽӱ�
	for(int i=0;i<numVertices;i++){
		Edge<T,E>* p=NodeTable[i].adj;
		//�ҵ����Ӧ��������׽��
		while(p!=nullptr){
			NodeTable[i].adj=p->link;
			delete p;
			p=NodeTable[i].adj;
		}
	}
	delete[] NodeTable;
};

template<class T, class E>
int Graphlnk<T,E>::getFirstNeighbor(int v){
	//��������λ��Ϊv�ĵ�һ���ڽӶ����λ�ã�����Ҳ�������������-1
	if(v!=-1){
		Edge<T,E>* p=NodeTable[v].adj;
		if(p!=nullptr)
			return p->dest;
	}
	return -1;
};

template<class T, class E>
int Graphlnk<T,E>::getNextNeighbor(int v,int w){
	//��������v�ĵ�һ���ڽӶ���w����һ���ڽӶ����λ��
	if(v!=-1){
		Edge<T,E>* p=NodeTable[v].adj;
		while(p!=nullptr&&p->dest!=w)
			p=p->link;
		if(p!=nullptr&&p->link!=nullptr)
			return p->link->dest;
	}
	return -1;
};

template<class T, class E>
E Graphlnk<T,E>::getWeight(int v1,int v2){
	//�������ر�(v1,v2)�ϵ�Ȩֵ�����ı߲���ͼ�У�����ȨֵΪ0
	if(v1!=-1&&v2!=-1){
		Edge<T,E>* p = NodeTable[v1].adj;
		while(p!=nullptr&&p->dest!=v2)
			p=p->link;
		if(p!=nullptr)
			return p->cost;
		//�ҵ��˱ߣ�����Ȩֵ
	}
	return 0;
};

template<class T, class E>
bool Graphlnk<T,E>::insertVertex(const T& vertex){
	if(numVertices==maxVertices)
		return false;
	NodeTable[numVertices].data=vertex;
	numVertices++;
	return true;
};

template<class T, class E>
bool Graphlnk<T,E>::removeVertex(int v) {
	//��ͼ��ɾ��һ��ָ������v��v�Ƕ���š�
	if (numVertices == 1 || v < 0 || v >= numVertices)
		return false;
	Edge<T,E>* p, *s, *t;
	int i, k;
	while (NodeTable[v].adj != nullptr) {
		p = NodeTable[v].adj;
		k = p->dest;
		//k��ʾ�ڽӶ���
		s = NodeTable[k].adj;
		t = nullptr;
		//�ҶԳƴ�ŵı߽ڵ�
		while (s != nullptr&&s->dest != v) {
			t = s;
			s = s->link;
		}
		if (s != nullptr) {
			if (t == nullptr)NodeTable[k].adj = s->link;
			else
				t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;
		//�������v�ı�������
		delete p;
		numEdges--;
	}
	numVertices--;
	NodeTable[v].data = NodeTable[numVertices].data;
	//�����һ�������
	p = NodeTable[v].adj = NodeTable[numVertices].adj;
	while (p != nullptr) {
		s = NodeTable[p->dest].adj;
		while (s != nullptr)
			if (s->dest == numVertices) {
				s->dest = v;
				break;
			}
			else
				s = s->link;
	}
	return true;
};

template<class T, class E>
bool Graphlnk<T,E>::insertEdge(int v1, int v2, E weight) {
	//�ڴ�Ȩͼ�в���һ����(v1,v2)�����˱ߴ��ڻ������������false
	if (v1 >= 0 && v1 < numVertices&&v2 >= 0 && v2 < numVertices) {
		//�����ж��Ƿ���v1,v2
		Edge<T,E>* q, *p = NodeTable[v1].adj;
		// v1��Ӧ�ı������ͷָ��
		while (p != nullptr&&p->dest != v2) {
			//Ѱ���ڽӶ���
			p = p->link;
		}
		if (p != nullptr)return false;
		//�����˱��Ѵ���
		p = new Edge<T,E>;
		q = new Edge<T,E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		//����v1������
		NodeTable[v1].adj = p;
		q->dest = v1; q->cost = weight;
		q->link = NodeTable[v2].adj;
		//����v2������
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}

template<class T, class E>
bool Graphlnk<T,E>::removeEdge(int v1, int v2) {
	//��ͼ��ɾ��һ����(v1,v2)
	if (v1 != -1 && v2 != -1) {
		Edge<T,E>* p = NodeTable[v1].adj, *q = nullptr, *s = p;
		while (p != nullptr&&p->dest != v2) {
			//v1��Ӧ���������ұ�ɾ��
			q = p;
			p = p->link;
		}
		if (p != nullptr) {
			if (p == s)NodeTable[v1].adj = p->link;
			//�ý��ʱ��������׽ڵ�
			else q->link = p->link;
			delete p;
		}
		else
			return false;
		//û���ҵ���ɾ���
		p = NodeTable[v2].adj;
		q = nullptr, s = p;
		while (p->dest != v1) {
			q = p; p = p->link;
		}
		if (p == s)NodeTable[v2].adj = p->link;
		else q->link = p->link;
		delete p;
		return true;
	}
	return false;
};

template<class T, class E>
void Kruskal(Graphlnk<T, E>& G, vector < MSTEdgeNode<T, E>>& vec) {
	MSTEdgeNode<T, E>ed;
	int u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfEdges();
	MinHeap< MSTEdgeNode<T, E> >H(m);
	UFSets F(n);
	for (u = 0; u < n; u++) {
		//���߲����
		for (v = u + 1; v < n; v++) {
			if (G.getWeight(u, v) != 0) {
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
		}
	}
	
	count = 1;
	while (count < n) {
		//���ѡ�㣬���ߴ�������
		H.RemoveMin(ed);
		u = F.Find(ed.tail);
		v = F.Find(ed.head);
		if (u != v) {
			F.Union(u, v);
			vec.push_back(ed);
			count++;
		}
	}
}

template<class T, class E>
void Prim(Graphlnk<T, E>& G, T u0, vector < MSTEdgeNode<T, E>>& vec) {
	MSTEdgeNode<T, E>ed;
	int i, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfEdges();
	int u = G.getVertexPos(u0);
	MinHeap<MSTEdgeNode<T, E>>H(m);
	//��С�ѵı߼���
	bool* Vmst = new bool[n];
	//��С�������Ķ��㼯��
	for (i = 0; i < n; i++)
		Vmst[i] = false;
	Vmst[u] = true;
	//��u����������
	count = 1;
	do {
		v = G.getFirstNeighbor(u);
		while (v != -1) {
			//�ظ����u�������ڽӶ���
			if (Vmst[v] == false) {
				//��v����������,(u,v)�����
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (!H.Isempty() && count < n) {
			H.RemoveMin(ed);
			//�Ӷ����˳�������СȨֵ�ı�
			if (Vmst[ed.head] == false) {
				vec.push_back(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	} while (count < n);
};






