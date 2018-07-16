#include"Graphlnk.h"
#include<string>
int main() {
	Graphlnk<string,int> gra(20);
	string c;
	for (int i = 0; i < 4; i++) {
		cin >> c;
		gra.insertVertex(c);
	}
	cout << "ÊäÈë±ß"<<endl;
	int i = 2;
	while (i) {
		string c1,c2;
		int is;
		int weight;
		cin >> c1;
		cin >> c2;
		cin >> weight;
		int a1 = gra.getVertexPos(c1);
		int a2 = gra.getVertexPos(c2);
		is=gra.insertEdge(a1,a2, weight);
		i++;
		if (i == 5)break;
	}
	return 0;
}