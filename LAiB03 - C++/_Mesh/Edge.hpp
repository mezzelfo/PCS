#ifndef EDGE_INC
#define EDGE_INC



class Edge
{
private:
	int index1, index2;
	Edge();
	Edge(int, int);
	int getIndex1() const {return index1;};
	int getIndex2() const {return index2;};

	friend bool operator==(const Edge& lhs, const Edge& rhs);

	
public:
	Edge(const Edge&);
	~Edge();

	friend class Mesh;

	
};

#endif
