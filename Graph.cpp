#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include "MinHeap.h"
#include <set>
#include <algorithm>

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
                visit[temp->GetKey()] = visited;//visit
                answer.push_back(temp->GetKey());//path insert
            }
            temp = temp->GetNext();//move next edge
        }
    }
    return answer;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    vector<int> answer;
    vector<int> distance(this->Size(), IN_FINITY);//Initialize distance 
    vector<int> path(this->Size(), -1);//Initialize path -1
    distance[startVertexKey] = 0;
    set<pair<int, int>> kw;//key, weight
    kw.insert(make_pair(startVertexKey, 0));
    answer.push_back(startVertexKey);

    while (!kw.empty())
    {
        pair<int, int> temp = *kw.begin();//make pair
        kw.erase(temp);
        Vertex* cur = this->FindVertex(temp.first);
        Edge* moveE = cur->GetHeadOfEdge();
        for (int i = 0; i < cur->Size(); i++)
        {
            if (distance[moveE->GetKey()] > distance[temp.first] + moveE->GetWeight())
            {//find min
                kw.erase(make_pair(moveE->GetKey(), distance[moveE->GetKey()]));//erase key, weight
                distance[moveE->GetKey()] = distance[temp.first] + moveE->GetWeight();//distance change
                kw.insert(make_pair(moveE->GetKey(), distance[moveE->GetKey()]));//insert key, weight
                path[moveE->GetKey()] = temp.first;//path remember
            }
            moveE = moveE->GetNext();
        }
    }
    vector<int> temp;
    int tempkey = endVertexKey;
    while (1)
    {//make path
        temp.push_back(tempkey);
        if (tempkey == startVertexKey)
            break;
        tempkey = path[tempkey];
    }
    reverse(temp.begin(), temp.end());//reverse path
    answer = temp;
    return answer;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    vector<int> answer;
    vector<int> distance(this->Size(), IN_FINITY);//Initialize distance
    distance[startVertexKey] = 0;
    vector<int> path(this->Size(), -1);//Initialize path -1
    MinHeap<int, int> heap;
    heap.Push(0, startVertexKey);

    while (!heap.IsEmpty())
    {
        pair<int, int> temp = heap.Top();//make pair
        heap.Pop();
        Vertex* cur = this->FindVertex(temp.second);
        Edge* moveE = cur->GetHeadOfEdge();
        for (int i = 0; i < cur->Size(); i++)
        {
            if (distance[moveE->GetKey()] > distance[temp.second] + moveE->GetWeight())
            {
                distance[moveE->GetKey()] = distance[temp.second] + moveE->GetWeight();
                heap.Push(distance[moveE->GetKey()], moveE->GetKey());
                path[moveE->GetKey()] = temp.second;//path remember
            }
            moveE = moveE->GetNext();
        }
    }
    vector<int> temp;
    int tempkey = endVertexKey;
    while (1)
    {//make path
        temp.push_back(tempkey);
        if (tempkey == startVertexKey)
            break;
        tempkey = path[tempkey];
    }
    reverse(temp.begin(), temp.end());//reverse path
    answer = temp;
    return answer;
}
