#pragma once

#include <vector>
#include <string>

// NOTE: Modified implementation of AdjacencyList graph
//		- use std::vector instead of array (makes implementation of some methods easier)
//		- use chars as identifiers of vertices - allows us to model same samples as in presentation materials

class AdjacencyList
{
public:
	AdjacencyList(char vertexId);
	~AdjacencyList();
	char getVertexId() const;
	void addAdjanced(char vertex);
	bool hasAdjanced(char vertex);
	std::vector<char> getAdjanced() const;
	void printList();
private:
	int vertexId;
	std::vector<char> adjancedVertices;
};

class Graph
{
public:
	Graph();
	~Graph();
	void addVertex(char vertexId);
	void addEdge(char from, char to);
	void printGraph();

	void printBFS();
	void printDFS();
private:
	std::vector<AdjacencyList> adjacencyList;
};