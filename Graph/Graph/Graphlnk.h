#pragma once
/*图的领接表表示方法*/
#include<iostream>
#include<vector>
#include"MinHeap.h"
#include"UFSets.h"
using namespace std;
const int DefaultVertices = 30;

template<class T,class E>
struct Edge {
	//边结点的定义
	int dest;
	//边的另一结点位置
	E cost;
	//边上的权值
	Edge<T,E>* link;
	//下一条边链指针
	Edge() {}
	Edge(int num,E weight):dest(num),cost(weight),link(nullptr){}
	bool operator!=(Edge<T,E>& R)const {
		//判断边不等
		return (dest != R.dest) ? true : false;
	}
};

template<class T,class E>
struct Vertex {
	//顶点的定义
	T data;
	//顶点的名字
	Edge<T,E>* adj;
	//边链表的头指针
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
	//顶点表，各边链表的头结点
	int numEdges;
	//当前边数
	int numVertices;
	//当前顶点数
	int maxVertices;
	//图中最大顶点数
	
public:
	/*friend istream& operator >> (istream& in, Graphlnk<T>& G);
	//重载输入*/
	//friend ostream& operator<<(ostream& out, Graphlnk<T,E>& G);
	//重载输出
	Graphlnk(int sz = DefaultVertices); 
	~Graphlnk();
	int getVertexPos(const T vertex);
	//给出顶点在图中的位置
	int NumberOfVertices() { return numVertices; }
	int NumberOfEdges() { return numEdges; }
	T getValue(int i) {
	//取位置为i的顶点中的值
		return (i >= 0 && i < numVertices)? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);
	//返回边(v1,v2)上的权值
	bool insertVertex(const T& vertex);
	//在图中插入一个顶点
	bool removeVertex(int v);
	//在图中删除一个顶点v
	bool insertEdge(int v1, int v2, E const);
	//在图中插入一条边(v1,v2)
	bool removeEdge(int v1, int v2);
	//在图中删除一条边(v1,v2)
	int getFirstNeighbor(int v);
	//取顶点v的第一个邻接顶点
	int getNextNeighbor(int v, int w);
	//取v的邻接顶点w的下一个邻接顶点
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
	//给出顶点vertex在图中的位置
	for (int i = 0; i < numVertices; i++) {
		if (NodeTable[i].data== vertex)
			return i;
	}
	return -1;
}

template<class T, class E>
Graphlnk<T,E>::Graphlnk(int sz){
	//构造函数建立一个空的邻接表
	maxVertices=sz;
	numVertices=0;
	numEdges=0;
	NodeTable=new Vertex<T,E>[maxVertices];
	//创建顶点表数组
	if(NodeTable==nullptr)
	{
		cerr<<"内存分配出错!"<<endl;
		exit(1);
	}
	for (int i = 0; i < maxVertices; i++)
		NodeTable[i].adj=nullptr;
};

template<class T, class E>
Graphlnk<T,E>::~Graphlnk(){
	//析构函数 删除一个邻接表
	for(int i=0;i<numVertices;i++){
		Edge<T,E>* p=NodeTable[i].adj;
		//找到其对应边链表的首结点
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
	//给出顶点位置为v的第一个邻接顶点的位置，如果找不到，则函数返回-1
	if(v!=-1){
		Edge<T,E>* p=NodeTable[v].adj;
		if(p!=nullptr)
			return p->dest;
	}
	return -1;
};

template<class T, class E>
int Graphlnk<T,E>::getNextNeighbor(int v,int w){
	//给出顶点v的第一个邻接顶点w的下一个邻接顶点的位置
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
	//函数返回边(v1,v2)上的权值，若改边不在图中，返回权值为0
	if(v1!=-1&&v2!=-1){
		Edge<T,E>* p = NodeTable[v1].adj;
		while(p!=nullptr&&p->dest!=v2)
			p=p->link;
		if(p!=nullptr)
			return p->cost;
		//找到此边，返回权值
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
	//在图中删除一个指定顶点v，v是顶点号。
	if (numVertices == 1 || v < 0 || v >= numVertices)
		return false;
	Edge<T,E>* p, *s, *t;
	int i, k;
	while (NodeTable[v].adj != nullptr) {
		p = NodeTable[v].adj;
		k = p->dest;
		//k表示邻接顶点
		s = NodeTable[k].adj;
		t = nullptr;
		//找对称存放的边节点
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
		//清除顶点v的边链表结点
		delete p;
		numEdges--;
	}
	numVertices--;
	NodeTable[v].data = NodeTable[numVertices].data;
	//将最后一个填补过来
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
	//在带权图中插入一条边(v1,v2)，若此边存在或参数不合理返回false
	if (v1 >= 0 && v1 < numVertices&&v2 >= 0 && v2 < numVertices) {
		//首先判断是否有v1,v2
		Edge<T,E>* q, *p = NodeTable[v1].adj;
		// v1对应的边链表表头指针
		while (p != nullptr&&p->dest != v2) {
			//寻找邻接顶点
			p = p->link;
		}
		if (p != nullptr)return false;
		//表明此边已存在
		p = new Edge<T,E>;
		q = new Edge<T,E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		//链入v1边链表
		NodeTable[v1].adj = p;
		q->dest = v1; q->cost = weight;
		q->link = NodeTable[v2].adj;
		//链入v2边链表
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}

template<class T, class E>
bool Graphlnk<T,E>::removeEdge(int v1, int v2) {
	//在图中删除一条边(v1,v2)
	if (v1 != -1 && v2 != -1) {
		Edge<T,E>* p = NodeTable[v1].adj, *q = nullptr, *s = p;
		while (p != nullptr&&p->dest != v2) {
			//v1对应边链表中找被删边
			q = p;
			p = p->link;
		}
		if (p != nullptr) {
			if (p == s)NodeTable[v1].adj = p->link;
			//该结点时边链表的首节点
			else q->link = p->link;
			delete p;
		}
		else
			return false;
		//没有找到被删结点
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
		//将边插入堆
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
		//逐个选点，将边存入数组
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
	//最小堆的边集合
	bool* Vmst = new bool[n];
	//最小生成树的顶点集合
	for (i = 0; i < n; i++)
		Vmst[i] = false;
	Vmst[u] = true;
	//将u加入生成树
	count = 1;
	do {
		v = G.getFirstNeighbor(u);
		while (v != -1) {
			//重复检测u的所有邻接顶点
			if (Vmst[v] == false) {
				//若v不在生成树,(u,v)加入堆
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (!H.Isempty() && count < n) {
			H.RemoveMin(ed);
			//从堆中退出具有最小权值的边
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






