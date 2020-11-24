#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include "MinHeap.h"
#include <set>

#define BFS_FIRST_PATH

Graph::Graph()
{
    m_pVHead = NULL;// the head pointer for the linked list of the vertics
    m_vSize = 0;// the number of the vertics
}
Graph::~Graph()
{
    Clear();
}
void Graph::AddVertex(int vertexKey, char* storeName)
{
    Vertex* NewVertex = new Vertex(vertexKey, storeName);
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
    v->SetSize(v->Size() + 1);
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

bool Graph::IsNegativeEdge()
{
    Vertex* moveV = m_pVHead;
    if (moveV == NULL)
        return false;
    else
    {
        while (moveV)
        {
            Edge* moveE = moveV->GetHeadOfEdge();
            while (moveE)
            {
                if (moveE->GetWeight() < 0)
                    return true;
                moveE = moveE->GetNext();//Edge move
            }
            moveV = moveV->GetNext();//Vertex move
        }
    }
    return false;
}

std::vector<int> Graph::FindPathBfs(int startVertexKey, int endVertexKey)
{
    vector<int> answer;
    Queue<int> q;
    bool *visit = new bool[200];
    fill(visit, visit + 200, false);
    visit[startVertexKey] = true;
    answer.push_back(startVertexKey);
    q.push(startVertexKey);
    while (!visit[endVertexKey] == visited)
    {//repeat endVertexKey
        int x = q.getfront();
        q.pop();
        Edge* temp = FindVertex(x)->GetHeadOfEdge();
        for (int i = 0; i < FindVertex(x)->Size(); i++)
        {
            if (!visit[temp->GetKey()])
            {
                q.push(temp->GetKey());
                visit[temp->GetKey()] = visited;
                answer.push_back(temp->GetKey());
            }
            temp = temp->GetNext();
        }
    }
    return answer;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    vector<int> answer;


    return answer;
}
