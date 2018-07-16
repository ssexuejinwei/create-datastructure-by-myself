#pragma once

const int DefaultSize = 10;

class UFSets {
	int *parent;
	int size;
public:
	UFSets(int sz = DefaultSize) {
		sz = (sz > DefaultSize) ? sz : DefaultSize;
		parent = new int[sz];
		for (int i = 0; i < sz; i++) {
			parent[i] = -1;
		}
	}
	~UFSets() { delete[] parent; }
	//UFSets& operator=(UFSets& R);
	void Union(int Root1, int Root2);
	int Find(int x);
	//搜寻X的根
	void WeightedUnion(int Root1, int Root2);
	//加权的合并算法
	int CollapsingFind(int i);
	//使用折叠规则压缩路径
};

int UFSets::Find(int x){
	while (parent[x] > 0) {
		x = parent[x];
	}
	return x;
}

void UFSets::Union(int Root1, int Root2) {
	parent[Root1] += parent[Root2];
	parent[Root2] = parent[Root1];
}

void UFSets::WeightedUnion(int Root1, int Root2) {
	int r1 = Find(Root1);
	int r2 = Find(Root2);
	int temp;
	if (r1 != r2) {
		temp = parent[r1] + parent[r2];
		if (parent[r1] < parent[r2]) {
			parent[r2] = r1;
			parent[r1] = temp;
		}
		else {
			parent[r1] = r2;
			parent[r2] = temp;
		}
	}
}

int UFSets::CollapsingFind(int i) {
	//在包含元素i的树中搜索跟，并将从J到根的路径上的所有结点都变成根的子女
	int j = i;
	for (; parent[j] > 0; j = parent[j]);
	//搜索根J
	while (i != j) {
		int temp = parent[i];
		parent[i] = j;
		i = temp;
	}
	return j;
	//返回根
}