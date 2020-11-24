#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"

#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
#define IN_FINITY 999999
#define visited true
#define unvisited false

class Graph
{
private:
    Vertex* m_pVHead;// the head pointer for the linked list of the vertics
    int m_vSize;// the number of the vertics

public:
	Graph();/// constructor  
	~Graph();/// destructor

    Vertex* GetHead() { return m_pVHead; }
    void SetSize(int size) { this->m_vSize = size; }
    /// add vertex with vertexNum at the end of the linked list for the vertics
    void AddVertex(int vertexKey, char* storeName);
    /// add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
    void AddEdge(int startVertexKey, int endVertexKey, int weight);

    Edge* ChangeEdge(Vertex* v, Edge* origin, int ChangeWeight)
    {
        Edge* newEdge = new Edge(origin->GetKey(), ChangeWeight);
        if (origin == v->GetHeadOfEdge())
        {
            v->SetHead(newEdge);
            if(origin->GetNext())
                newEdge->SetNext(origin->GetNext());
            delete origin;
            return newEdge;
        }
        else
        {
            Edge* pCur = v->GetHeadOfEdge();
            while (origin != pCur->GetNext())
                pCur = pCur->GetNext();
            pCur->SetNext(newEdge);
            if (origin->GetNext())
                newEdge->SetNext(origin->GetNext());
            delete origin;
            return newEdge;
        }
    }

    /// get the vertex which the key is vertexNum
    Vertex* FindVertex(int key) 
    {
        Vertex* pCur = m_pVHead;
        while (pCur != NULL)
        {
            if (pCur->GetKey() == key)
                return pCur;
            pCur = pCur->GetNext();
        }
        return NULL;
    }
    /// get the number of the vertics
    int Size() const { return m_vSize; }
    /// memory free for the vertics
    void Clear() 
    { 
        delete m_pVHead;
        m_vSize = 0;
    }
    /// print out the graph as matrix form
    void Print(std::ofstream& fout);
    /// check whether the graph has negative edge or not.
    bool IsNegativeEdge();
    /// find the path from startVertexKey to endVertexKey with DFS (stack and queue)
	std::vector<int> FindPathBfs(int startVertexKey, int endVertexKey);

    /// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
    std::vector<int> FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);

    /// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
    std::vector<int> FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);

    /// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
    std::vector<int> FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);
    
    std::vector<vector<int> > FindShortestPathFloyd();
};

#endif
