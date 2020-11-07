#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>

#define DFS_FIRST_PATH

Graph::Graph()
{
    m_pVHead = NULL;// the head pointer for the linked list of the vertics
    m_vSize = 0;// the number of the vertics
}
Graph::~Graph()
{
    m_pVHead = NULL;// the head pointer for the linked list of the vertics
    m_vSize = 0;// the number of the vertics
}
void Graph::AddVertex(int vertexKey)
{
    Vertex* NewVertex = new Vertex(vertexKey);
    if (m_pVHead == NULL)
    {//first insert
        m_pVHead = NewVertex;
    }
    else
    {//not first insert
        Vertex* pCur = m_pVHead;
        while (pCur->GetNext() != NULL)
            pCur = pCur->GetNext();
        pCur->SetNext(NewVertex);
    }
}
void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
    Vertex* v = FindVertex(startVertexKey);
    v->AddEdge(endVertexKey, weight);
}

void Graph::Print(std::ofstream& fout)
{
    fout << "====== PRINT ======" << endl;
    cout << "====== PRINT ======" << endl;
    Vertex* moveV = m_pVHead;
    for (int i = 0; i < m_vSize; i++)
    {
        Edge* moveE = moveV->GetHeadOfEdge();
        for (int j = 0; j < m_vSize; j++)
        {
            if (moveE == NULL || j != moveE->GetKey())
            {
                fout << 0 << " ";
                cout << 0 << " ";
            }
            else
            {
                fout << moveE->GetWeight() << " ";
                cout << moveE->GetWeight() << " ";
                moveE = moveE->GetNext();//Edge move
            }
        }
        fout << endl;
        cout << endl;
        moveV = moveV->GetNext();//Vertex move
    }
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
}
