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
	//��ѰX�ĸ�
	void WeightedUnion(int Root1, int Root2);
	//��Ȩ�ĺϲ��㷨
	int CollapsingFind(int i);
	//ʹ���۵�����ѹ��·��
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
	//�ڰ���Ԫ��i��������������������J������·���ϵ����н�㶼��ɸ�����Ů
	int j = i;
	for (; parent[j] > 0; j = parent[j]);
	//������J
	while (i != j) {
		int temp = parent[i];
		parent[i] = j;
		i = temp;
	}
	return j;
	//���ظ�
}