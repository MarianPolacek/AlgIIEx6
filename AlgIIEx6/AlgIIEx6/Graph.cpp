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
	// 1) Define basic variables
	std::map<char, int> state; // -1 = white (unknown), 0 = gray (visited), 1 = black (finalized)
	std::map<char, int> d; // distances from start vertex
	std::map<char, char> pi; // parent vertex
	std::queue<char> queue; // queue, that holds gray vertices

	// 2) Initialize basic variables - assign default values for each vertex of graph
	for (int i = 0; i < this->adjacencyList.size(); i++) {
		char vertex = this->adjacencyList[i].getVertexId();

		state[vertex] = -1;
		d[vertex] = -1;
		pi[vertex] = '/';
	}

	// 3) Process start vertex 	
	state[startVertex] = 0; // mark it as gray (state = 1)
	d[startVertex] = 0; // set distance to 0 (e.g. distance from A to A = 0)
	pi[startVertex] = '/'; // start vertex does not have parent
	queue.push(startVertex); // add it to queue - so we can start loop

	// 4) process queued vertices (gray), untill queue is empty (end of BFS)
	while (!queue.empty()) {

		// 4.1) Take vertex from queue and process it
		char currentVertexId = queue.front();
		queue.pop();

		// 4.2) Check all adjanced vertices (neighbours) 
		AdjacencyList vertex = this->find(currentVertexId);
		std::vector<char> adjancedVertexes = vertex.getAdjanced();

		for (int i = 0; i < adjancedVertexes.size(); i++) {

			// 4.2.1) To see if adjanced vertex is unknown, check state variable
			char adjanced = adjancedVertexes[i];
			bool unknown = state[adjanced] == -1;

			// 4.2.2) If we found unknown vertex, update it's state, distance and parent. 
			//		Then push it to queue to be processed later.
			if (unknown) {
				state[adjanced] = 0;
				d[adjanced] = d[currentVertexId] + 1;
				pi[adjanced] = currentVertexId;
				queue.push(adjanced);
			}
		}

		// 4.3) Finally set vertex state to 1 (finalized / black), all neighbours were checked
		state[currentVertexId] = 1;
	}

	// Print variable state for each vertex
	for (int i = 0; i < this->adjacencyList.size(); i++) {
		char vertex = this->adjacencyList[i].getVertexId();

		std::cout << vertex << ": d=" << d[vertex] << ", pi=" << pi[vertex] << ", state=" << state[vertex] << std::endl;
	}
}

void Graph::printDFS(char startVertex)
{
	// 1) Define basic variables

	// values used in state:
	// -1 = unknown, 0 = discovered (but not processed), 
	//	1 = current (started processing), 2 - finished (all descendants processed)
	std::map<char, int> state;

	std::map<char, int> d; // timestamp for start of processing (time, when state of vertex was set to current)
	std::map<char, int> f; // timestamp for end of processing (time, when state of vertex was set to finished)
	std::map<char, char> pi; // parent vertex
	std::stack<char> stack; // stack, that holds vertices, that will be processed
	int time = 0; // current iteration / timestamp

	// 2) Initialize basic variables - assign default values for each vertex of graph
	for (int i = 0; i < this->adjacencyList.size(); i++) {
		char vertex = this->adjacencyList[i].getVertexId();

		state[vertex] = -1;
		d[vertex] = -1; // use -1 instead of infinity
		f[vertex] = -1; // use -1 instead of infinity
		pi[vertex] = '/'; // use slash instead NONE
	}

	// 3) Prepare start vertex
	state[startVertex] = 0; // mark start vertex as discovered
	stack.push(startVertex); // add it to stack

	// 4) Process all items in stack in a loop
	while (!stack.empty()) {

		// 4.1) Each vertex is processed 2 times. 
		//		- first processing (forward step), identifies undiscovered neighbours, update d[u] and set state to current
		//		- second processing (backward step), set state to finished and update f[u]
		//		- due to this, we can only pop vertex from stack, when we are in second processing
		char currentVertexId = stack.top(); 

		// 4.2) Process vertex, that is in discovered state (first processing)
		if (state[currentVertexId] == 0) {

			// 4.2.1) Update state, d of current vertex
			state[currentVertexId] = 1; // set state to current
			time += 1; // increase time
			d[currentVertexId] = time; // set start of processing to current time

			// 4.2.2) Mark all adjanced vertices as discovered + update parent
			AdjacencyList vertex = this->find(currentVertexId);
			std::vector<char> adjancedVertexes = vertex.getAdjanced();

			// iterate through all adjanced vertices, of currently processed vertex
			for (int i = 0; i < adjancedVertexes.size(); i++) {
				char adjanced = adjancedVertexes[i];

				// in case, adjanced vertex was not yet discovered, update all required variables and push it to stack
				if (state[adjanced] == -1) {
					state[adjanced] = 0; // set state to discovered
					pi[adjanced] = currentVertexId; // update parent variable
					stack.push(adjanced); // finally push adjanced vertex to stack
				}
			}
		}
		// 4.3) Process vertex in state current (second processing).
		//	We get here, when all descendants were processed already
		else if (state[currentVertexId] == 1) {
			state[currentVertexId] = 2; // state of processed vertex is set to finished
			time += 1; // increase time
			f[currentVertexId] = time; // update timestamp for end of processsing
			stack.pop(); // finally remove vertex from stack 
		}
	}

	// Print variable state for each vertex
	for (int i = 0; i < this->adjacencyList.size(); i++) {
		char vertex = this->adjacencyList[i].getVertexId();

		std::cout << vertex << ": d=" << d[vertex] << ", f=" << f[vertex] << ", pi=" << pi[vertex] << ", state=" << state[vertex] << std::endl;
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
