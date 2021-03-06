#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include "maze.h"

#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;


typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

// typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999

int main()
{
	try
	{
		ifstream fin;

		// Read the maze from the file.
		string fileName = "yourpath/maze1.txt";

		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << endl;
			exit(1);
		}

		maze m(fin);
		fin.close();

		m.print(m.numRows() - 1, m.numCols() - 1, 0, 0);

		Graph g;
		m.mapMazeToGraph(g);

		cout << "FOO" << endl;
	}

	catch(...){
		cout << "TRY Clause in main function failed" << endl;
		exit(0);
	}

}
