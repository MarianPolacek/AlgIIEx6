#include "pch.h"
#include <iostream>
#include "Graph.h"
#include <map>
#include <queue>
#include <stack>
#include <stdexcept>

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
	// Initialize variables
	std::map<char, int> state;
	std::map<char, int> d;
	std::map<char, char> pi;
	std::queue<char> queue;

	for (int i = 0; i < this->adjacencyList.size(); i++) {
		char vertex = this->adjacencyList[i].getVertexId();

		state[vertex] = -1; // -1 unknown
		d[vertex] = -1; // NOTE: Use -1 instead of infinity
		pi[vertex] = '/'; // NOTE: Use slash instead of real char
	}

	// Process start vertex
	state[startVertex] = 1;
	d[startVertex] = 0;
	pi[startVertex] = '/';
	queue.push(startVertex);

	// Execute BFS
	while (!queue.empty()) {
		// NOTE: This is how we write pop with std
		char vertexId = queue.front();
		queue.pop();

		AdjacencyList vertex = this->find(vertexId);
		std::vector<char> adjancedVertexes = vertex.getAdjanced();

		for (int i = 0; i < adjancedVertexes.size(); i++) {
			char adjanced = adjancedVertexes[i];
			bool unknown = state[adjanced] == -1;
			if (unknown) {
				state[adjanced] = 1;
				d[adjanced] = d[vertexId] + 1;
				pi[adjanced] = vertexId;
				queue.push(adjanced);
			}
		}

		std::cout << vertexId << " ";
	}
}

void Graph::printDFS(char startVertex)
{
	// Initialize variables
	std::map<char, int> state; // unknown -1, discovered 0, current 1, finished 2
	std::map<char, int> d;
	std::map<char, int> f;
	std::map<char, char> pi;
	std::stack<char> stack;
	int time = 0;

	for (int i = 0; i < this->adjacencyList.size(); i++) {
		char vertex = this->adjacencyList[i].getVertexId();

		state[vertex] = -1;
		d[vertex] = -1; // NOTE: Use -1 instead of infinity
		f[vertex] = -1; // NOTE: Use -1 instead of infinity
		pi[vertex] = '/'; // NOTE: Use slash instead of real char
	}

	// Prepare start vertex
	state[startVertex] = 0;
	stack.push(startVertex);

	// run processing of tree
	while (!stack.empty()) {
		char vertexId = stack.top();

		// discovered
		if (state[vertexId] == 0) {

			state[vertexId] = 1;
			time += 1;
			d[vertexId] = time;

			AdjacencyList vertex = this->find(vertexId);
			std::vector<char> adjancedVertexes = vertex.getAdjanced();

			for (int i = 0; i < adjancedVertexes.size(); i++) {
				char adjanced = adjancedVertexes[i];

				if (state[adjanced] == -1) {
					state[adjanced] = 0; 
					pi[adjanced] = vertexId;
					stack.push(adjanced);
				}
			}
		}
		// current
		else if (state[vertexId] == 1) {
			state[vertexId] = 2;
			time += 1;
			f[vertexId] = time;
			stack.pop();
		}
	}

	for (int i = 0; i < this->adjacencyList.size(); i++) {
		char vertex = this->adjacencyList[i].getVertexId();

		std::cout << vertex << ": d=" << d[vertex] << ", f=" << f[vertex] << ", pi=" << pi[vertex] << std::endl;
	}
}

AdjacencyList Graph::find(char vertex)
{
	for (int i = 0; i < this->adjacencyList.size(); i++) {
		if (this->adjacencyList[i].getVertexId() == vertex) {
			return this->adjacencyList[i];
		}
	}

	throw std::runtime_error("Could not find vertex");
}
