//P Hanbury and J Kang
//Algorithms
//Project5a

#include "maze.h"

#include <boost/graph/adjacency_list.hpp>
using namespace boost;


maze::maze(std::ifstream &fin)
{
	fin >> rows;
	fin >> cols;
	char x;
	value.resize(rows, cols);
	vertexCoords.resize(rows, cols);
	for (int i = 0; i <= rows - 1; i++)
		for (int j = 0; j <= cols - 1; j++)
		{
			fin >> x;
			if (x == 'O')
				value[i][j] = true;
			else
				value[i][j] = false;
			vertexCoords[i][j] = -1;
		}

}

//Void funciton to print out a maze
void maze::print(int goalI, int goalJ, int currI, int currJ)
{
	if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
		throw rangeError("Bad value in maze::print");
	if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
		throw rangeError("Bad value in maze::print");
	for (int i = 0; i <= rows - 1; i++)
	{
		for (int j = 0; j <= cols - 1; j++)
		{
			if (i == goalI && j == goalJ)
				cout << "*";
			else
				if (i == currI && j == currJ)
					cout << "+";
				else
					if (value[i][j])
						cout << " ";
					else
						cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

//bool function to indicate whether if it is legal to into a cell
bool maze::isLegal(int i, int j)
{
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		return false;
	return value[i][j];
}

//void maze clearvisited
//Mark all nodes in g as not visited.
void maze::clearVisited(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].visited = false;
}

//void maze setNodeWeights
//Set all node weights to w.
void maze::setNodeWeights(Graph &g, int w) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].weight = w;
}

//void maze clearMarked
//Cleared the nodes as marked.
void maze::clearMarked(Graph &g) {
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		g[*vItr].marked = false;
}




//creates a graph with nodes representing possible locations to go on the maze,
//and edges representing the legal moves from the current node
void maze::mapMazeToGraph(Graph &g) {
	//variables to hold node descriptor and edge descriptor
	Graph::vertex_descriptor v;
	pair<Graph::edge_descriptor, bool> e;
	//iterate over entire maze matrix
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			//if the current cell is legal
			if (isLegal(i, j)) {
				//This function adds the current cell as a nodes and stores the vertex descript.
				v = add_vertex(g);
				//Stores the cell in the vertex prop. cell
				g[v].cell = std::pair<int, int>(i, j);
				//Stores the node number in the correct cell location
				vertexCoords[i][j] = v;
			}
		}
	}

	//iterate over the entire maze matrix
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			//if the current cell is legal
			if (isLegal(i, j)) {
				//Checks if the right cell is legal.
				//Adds edge from current to the right cell. 
				if (isLegal(i, j + 1))
					add_edge(vertexCoords[i][j], vertexCoords[i][j + 1], g);
				//checks if the underneath cell is legal
				//adds edge from current to the underneath cell
				if (isLegal(i + 1, j))
					add_edge(vertexCoords[i][j], vertexCoords[i + 1][j], g);
				//checks if the left cell is legal
				//adds edge from the current to the left cell 
				if (isLegal(i, j - 1))
					add_edge(vertexCoords[i][j], vertexCoords[i][j - 1], g);
				//checks if the top cell is legal. 
				//adds edge from the current to the top cell. 
				if (isLegal(i - 1, j))
					add_edge(vertexCoords[i][j], vertexCoords[i - 1][j], g);
			}
		}
	}
	//initialize properties of nodes
	setNodeWeights(g, 0);
	clearVisited(g);
	clearMarked(g);
}

//printPath function on a graph 
void maze::printPath(Graph::vertex_descriptor end,
	stack<Graph::vertex_descriptor> &s,
	Graph g) {
	//Contained in the stack
	Graph::vertex_descriptor currentNode;
	//if statement that checks to see if the stack is empty
	if (s.empty())
		//output statement that says it is empty
		std::cout << "Stack is empty";
	//else statement that checks otherwise
	else {
		//do loop
		do {
			//currentNode becomes the top of the stack 
			currentNode = s.top();
			//pops the top node off the stack
			s.pop();
			//calls the print function earlier used in the program
			print(g[end].cell.first, g[end].cell.second, g[currentNode].cell.first, g[currentNode].cell.second);
		}
		//while statement that acts as the stop operator if the stack is empty
		while (currentNode != end);
	}
}
