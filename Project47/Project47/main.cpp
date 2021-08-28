#include "Graph.h"
#include <iostream>
#include <random>

using namespace std;

//function decleration

bool random_bool_with_prob(double );
Graph build_random_graph(int , double );
int connectivity(Graph );
int diameter(Graph );
int is_isolated(Graph );

//random
std::knuth_b rand_engine;
std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);


void main() {
	Graph g = build_random_graph(10, 0.1);
	Graph g2 = build_random_graph(10, 0.25);
	g.print_graph();
	cout << endl << endl;
	g2.print_graph();
	
	cout << "Connectivity1: " << connectivity(g) << endl;
	cout << "Diameter1: " << diameter(g) << endl;
	cout << "Is isolated1: " << is_isolated(g) << endl;
	cout << "Connectivity2: " << connectivity(g2) << endl;
	cout << "Diameter2: " << diameter(g2) << endl;
	cout << "Is isolated2: " << is_isolated(g2) << endl;

}



//rand false/true for the prob
bool random_bool_with_prob(double prob)
{
	return uniform_zero_to_one(rand_engine) < prob;
}


//build random graph
Graph build_random_graph(int v, double p) {
	Graph g(v);
	for (int i = 0; i < v; i++)
	{
		for (int j = i + 1; j < v; j++)
		{
			if (random_bool_with_prob(p)) {
				//cout << "Adding Edge: (" << i << ", " << j << ")" << endl;
				g.addEdge(i, j);
			}
		}
	}
	return g;
}


//checks ig g is connected
int connectivity(Graph g) {
	int* distances = g.BFS(0);
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] == -1)
			return 0;
	}
	return 1;
}



//gind g diameter
int diameter(Graph g) {
	int* distances = g.BFS(0);
	int maxd = 0, farrestV = 0;
	// finding first end of the diameter
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] == -1)
			return -1; // Not connected Graph
		if (distances[i] > maxd) {
			maxd = distances[i];
			farrestV = i;
		}
	}
	cout << farrestV << "<->";
	distances = g.BFS(farrestV);
	maxd = 0;
	// finding second end of the diameter
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] > maxd) {
			maxd = distances[i];
			farrestV = i;
		}
	}

	cout << farrestV << endl;
	return maxd;
}


//checks if there is v without adj
int is_isolated(Graph g) {
	for (int i = 0; i < g.getV(); i++)
	{
		if (g.getAdjList(i).empty())
			return 1;
	}
	return 0;
}




