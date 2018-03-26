//John Kang and Patrick Hanbury
//Algorithms
//Project5a

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <stack>
#include "d_except.h"
#include "d_matrix.h"

#include <boost/graph/adjacency_list.hpp>
using namespace boost;

//Type Definition of Graph
struct VertexProperties;
struct EdgeProperties;
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
	pair<int, int> cell; // maze cell (x,y) value
	Graph::vertex_descriptor pred; // predecessor node
	int weight;
	bool visited;
	bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
	int weight;
	bool visited;
	bool marked;
};
typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

//class maze variable declarations. 
class maze
{
public:

	//construcor that takes in a maze file
	maze(ifstream &fin);
	//functions that checks to see if node was visited to clear
	void clearVisited(Graph &g);
	//function to set the weights of the nodes
	void setNodeWeights(Graph &g, int w);
	//function to mark the cleared nodes
	void clearMarked(Graph &g);
	//function to check if a move can be done. 
	bool isLegal(int i, int j);

	//function to print the mazees 
	void print(int, int, int, int);

	//function that stores the maze in a graph to a graph
	void mapMazeToGraph(Graph &g);
	//function that prints the path
	void printPath(Graph::vertex_descriptor end,
		stack<Graph::vertex_descriptor> &s,
		Graph g);

	int numRows() { return rows; };
	int numCols() { return cols; };


private:
	//number of rows
	//number of columnms
	int rows;
	int cols;
	//matrix to store which node is contained in each cell. 
	matrix<Graph::vertex_descriptor> vertexCoords;
	matrix<bool> value;
};

#endif

