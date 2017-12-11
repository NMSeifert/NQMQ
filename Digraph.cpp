// Digraph.cpp -- directed graph class
// c. 2017 T. O'Neil
// Implementation
#include <climits>
#include <vector>
#include "Digraph.hpp"

unsigned int Digraph::noVertices()
{
    return numberOfVertices;
}

unsigned int Digraph::noEdges()
{
    return numberOfEdges;
}

void Digraph::resetEdges()
{
    for(int i = 0; i < vertex.size(); i++) {
        for(int j = 0; j < vertex.size(); j++) {
            if(i == j) {
                //Set the distance of a city to itself to be 0
                distMatrix[i][j] = 0;
            }
            else {
                //Set unknown distances to INT_MAX
                distMatrix[i][j] = INT_MAX;
            }
        }
    }
}

void Digraph::addEdge(int source, int dest, int wt)
{
    distMatrix[source][dest] = wt;
    distMatrix[dest][source] = wt;
    numberOfEdges++;
}

void Digraph::delEdge(int source, int dest)
{
    distMatrix[source][dest] = INT_MAX;
    distMatrix[dest][source] = INT_MAX;
    numberOfEdges--;
}

int Digraph::isEdge(int source, int dest)
{
    return distMatrix[source][dest];
}

int Digraph::dijkstra(int source, int dest)
{
    //Initialize a vector to hold the distance to each city
    //An unknown distance is held as INT_MAX
    std::vector<int> Distances;
    for (int i = 0; i < vertex.size(); i++) {
        Distances.push_back(INT_MAX);
    }

    //A city's distance to itself is 0
    Distances[source] = 0;


    int v;
    for (int j = 0; j < vertex.size(); j++) {

        //Find the smallest distance in the distance vector that has not been visited and store it in v
        v = 0;
        for (int i = 0; i < vertex.size(); i++) {
            if ((Distances[i] < Distances[v]) && (vertex[i]->getStatus() != VISITED)) {
                v = i;
            }
        }

        vertex[v]->setStatus(VISITED);

        //Reevaluate distances based upon the newly added vertex
        for (int i = 0; i < vertex.size(); i++) {
            if ((Distances[i] > (Distances[v] + distMatrix[v][i])) && (distMatrix[v][i] != INT_MAX)) {
                Distances[i] = Distances[v] + distMatrix[v][i];
            }
        }
    }

    //Reset the vector of vertices so all cities are unvisited again
    for (int i = 0; i < vertex.size(); i++) {
        vertex[i]->setStatus(NOT_VISITED);
    }

    return Distances[dest];
}
