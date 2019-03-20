// AlgIIEx6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Graph.h"

int main()
{
	Graph graph;

	graph.addVertex('A');
	graph.addVertex('B');
	graph.addVertex('C');
	graph.addVertex('D');
	graph.addVertex('E');
	graph.addVertex('F');
	graph.addVertex('G');
	graph.addVertex('H');
	graph.addVertex('I');
	graph.addVertex('J');

	graph.addEdge('A', 'B');
	graph.addEdge('A', 'E');
	graph.addEdge('A', 'G');
	graph.addEdge('B', 'C');
	graph.addEdge('B', 'E');
	graph.addEdge('E', 'F');
	graph.addEdge('E', 'H');
	graph.addEdge('E', 'G');
	graph.addEdge('G', 'H');
	graph.addEdge('C', 'D');
	graph.addEdge('C', 'F');
	graph.addEdge('F', 'D');
	graph.addEdge('F', 'I');
	graph.addEdge('H', 'I');
	graph.addEdge('I', 'J');
	graph.addEdge('D', 'J');

	std::cout << "Graph: " << std::endl;

	graph.printGraph();

	// EX1: Implement BFS traversal, print edges in order, they were visited
	std::cout << std::endl;
	std::cout << "BFS traversal: " << std::endl;
	graph.printBFS('A');

	// EX2: Implement DFS traversal, print edges in order, they were visited
	std::cout << std::endl;
	std::cout << "DFS traversal: " << std::endl;
	graph.printDFS('A');
}