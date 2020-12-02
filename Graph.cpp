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
    fill(visit, visit + 200, unvisited);
    visit[startVertexKey] = visited;
    answer.push_back(startVertexKey);
    q.push(startVertexKey);
    while (!visit[endVertexKey] == visited)
    {//repeat endVertexKey
        int front = q.getfront();
        q.pop();
        Edge* temp = FindVertex(front)->GetHeadOfEdge();
        for (int i = 0; i < FindVertex(front)->Size(); i++)
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
    distance[startVertexKey] = 0;
    vector<int> path(this->Size(), -1);//Initialize path -1
    set<pair<int, int>> wk;//weight, key 
    wk.insert(make_pair(0, startVertexKey));

    while (!wk.empty())
    {
        pair<int, int> temp = *wk.begin();//make pair
        wk.erase(temp);
        Vertex* cur = this->FindVertex(temp.second);
        Edge* moveE = cur->GetHeadOfEdge();
        for (int i = 0; i < cur->Size(); i++)
        {
            if (distance[moveE->GetKey()] > distance[temp.second] + moveE->GetWeight())
            {//Renewal
                distance[moveE->GetKey()] = distance[temp.second] + moveE->GetWeight();//distance change
                wk.insert(make_pair(distance[moveE->GetKey()], moveE->GetKey()));//insert key, weight
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
            {//Renewal
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

std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    vector<int> answer;
    vector<int> distance(this->Size(), IN_FINITY);//Initialize distance
    distance[startVertexKey] = 0;
    vector<int> path(this->Size(), -1);//Initialize path -1

    Vertex* moveV;
    Edge* moveE;
    for (int i = 0; i < Size(); i++)
    {
        for (int j = 0; j < Size(); j++)
        {
            moveV = FindVertex(j);
            moveE = moveV->GetHeadOfEdge();
            while (moveE)
            {
                if (distance[moveV->GetKey()] != IN_FINITY && distance[moveE->GetKey()] > distance[moveV->GetKey()] + moveE->GetWeight())
                {//Renewal
                    distance[moveE->GetKey()] = distance[moveV->GetKey()] + moveE->GetWeight();//change distance
                    path[moveE->GetKey()] = moveV->GetKey();//change path
                    if (i == Size() - 1)
                    {//Negative cycle exists
                        distance.resize(0);
                        return distance;
                    }
                }
                moveE = moveE->GetNext();
            }
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

std::vector<vector<int>> Graph::FindShortestPathFloyd()
{
    vector<vector<int>> answer(Size(), vector<int>(Size(), IN_FINITY));
    Vertex* moveV = m_pVHead;
    for (int i = 0; i < Size(); i++)
    {//Initialization
        Edge* moveE = moveV->GetHeadOfEdge();
        for (int j = 0; j < Size(); j++)
        {
            if (i == j)
                answer[i][j] = 0;//from i to j is 0
            if (!moveE)
                break;
            if (moveE->GetKey() == j)
            {
                answer[i][j] = moveE->GetWeight();
                moveE = moveE->GetNext();
            }
        }
        if(moveV->GetNext())
            moveV = moveV->GetNext();
    }
    for (int k = 0; k < Size(); k++)
    {//Floyd
        for (int i = 0; i < Size(); i++)
        {
            for (int j = 0; j < Size(); j++)
            {//Renewal
                answer[i][j] = min(answer[i][j], answer[i][k] + answer[k][j]);
            }
        }
    }
    for (int i = 0; i < Size(); i++)
    {
        if (answer[i][i] < 0)
        {//Negative cycle exists
            answer.resize(0);
            return answer;
        }
    }
    return answer;
}
