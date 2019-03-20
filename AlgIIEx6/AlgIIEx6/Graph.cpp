#include "pch.h"
#include <iostream>
#include "Graph.h"

AdjacencyList::AdjacencyList(char vertexId)
{
	this->vertexId = vertexId;
}

AdjacencyList::~AdjacencyList()
{
}

char AdjacencyList::getVertexId() const
{
	return this->vertexId;
}

void AdjacencyList::addAdjanced(char vertex)
{
	this->adjancedVertices.push_back(vertex);
}

bool AdjacencyList::hasAdjanced(char vertex)
{
	for (int i = 0; i < this->adjancedVertices.size(); i++)
	{
		if (this->adjancedVertices[i] == vertex) {
			return true;
		}
	}

	return false;
}

std::vector<char> AdjacencyList::getAdjanced() const
{
	return this->adjancedVertices;
}

void AdjacencyList::printList()
{
	for (int i = 0; i < this->adjancedVertices.size(); i++)
	{
		std::cout << this->adjancedVertices[i] << " ";
	}
}

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addVertex(char vertexId)
{
	AdjacencyList vertex = AdjacencyList(vertexId);
	this->adjacencyList.push_back(vertex);
}

void Graph::addEdge(char from, char to)
{
	for (int i = 0; i < this->adjacencyList.size(); i++) {
		if (this->adjacencyList[i].getVertexId() == from) {
			this->adjacencyList[i].addAdjanced(to);
		}

		if (this->adjacencyList[i].getVertexId() == to) {
			this->adjacencyList[i].addAdjanced(from);
		}
	}
}

void Graph::printGraph()
{
	for (int i = 0; i < this->adjacencyList.size(); i++)
	{
		std::cout << this->adjacencyList[i].getVertexId() << ": ";
		this->adjacencyList[i].printList();
		std::cout << std::endl;
	}
}

void Graph::printBFS(char startVertex)
{
	// TODO: Implement BFS
}

void Graph::printDFS(char startVertex)
{
	// TODO: Implement DFS
}
