#include "Manager.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "MinHeap.h"
using namespace std;
vector<int> temp(999999, 0);

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();
    //if (ferr.is_open())
       //ferr.close();
}

void Manager::Run(const char* filepath)//filepath is command.txt
{
    fstream fin;
    fin.open(filepath);
    fout.open(RESULT_LOG_PATH);//log.txt open
    if (!fin)
    {
        fout << "====== SYSTEM ======" << endl;
        fout << "CommandFileNotExist" << endl;
        fout << "====================" << endl;
        cout << "====== SYSTEM ======" << endl;
        cout << "CommandFileNotExist" << endl;
        cout << "====================" << endl;
        PrintError(CommandFileNotExist);
    }
    char cmd[100];
    while (!fin.eof())
    {
        fin.getline(cmd, 100);//read line
        char* tmp = strtok(cmd, " ");//word cutting
        if (tmp == NULL) break;
        if (tmp[0] == '/' && tmp[1] == '/') 
            continue;
        if (strcmp(tmp, "LOAD") == 0)
        {
            if (Load("mapdata.txt") == LoadFileNotExist)
            {//LoadFileNotExist if file is not exist.
                PrintErrorName(tmp, "LoadFileNotExist");
                PrintError(LoadFileNotExist);
            }
            else
            {//load is successful.
                PrintErrorName(tmp, "Success");
                PrintError(Success);
            }
        }
        else if (strcmp(tmp, "UPDATE") == 0)
        {
            if (Update() == FaildtoUpdatePath)
            {
                PrintErrorName(tmp, "FaildtoUpdatePath");
                PrintError(FaildtoUpdatePath);
            }
            else
            {//UPDATE is successful.
                PrintErrorName(tmp, "Success");
                PrintError(Success);
            }
        }
        else if (strcmp(tmp, "PRINT") == 0)
        {
            if (Print() == GraphNotExist)
            {
                PrintErrorName(tmp, "GraphNotExist");
                PrintError(GraphNotExist);
            }
            else
            {//PRINT is successful.
                PrintError(Success);
            }
        }
        else if (strcmp(tmp, "BFS") == 0)
        {
            char* start = strtok(NULL, " ");
            char* end = strtok(NULL, " ");
            if (start == NULL || end == NULL)
            {
                PrintErrorName(tmp, "VertexKeyNotExist");
                PrintError(VertexKeyNotExist);
            }
            else 
            {
                auto code = FindPathBfs(atoi(start), atoi(end));
                if (code == 201)
                {
                    PrintErrorName(tmp, "InvalidVertexKey");
                    PrintError(InvalidVertexKey);
                }
                else if (code == 202)
                {
                    PrintErrorName(tmp, "GraphNotExist");
                    PrintError(GraphNotExist);
                }
                else
                {
                    PrintError(Success);
                }
            }
        }
        else if (strcmp(tmp, "DIJKSTRA") == 0)
        {
            char* start = strtok(NULL, " ");
            char* end = strtok(NULL, " ");
            if (start == NULL || end == NULL)
            {
                PrintErrorName(tmp, "VertexKeyNotExist");
                PrintError(VertexKeyNotExist);
            }
            else
            {
                auto code = FindShortestPathDijkstraUsingSet(atoi(start), atoi(end));
                if (code == 201)
                {
                    PrintErrorName(tmp, "InvalidVertexKey");
                    PrintError(InvalidVertexKey);
                }
                else if (code == 202)
                {
                    PrintErrorName(tmp, "GraphNotExist");
                    PrintError(GraphNotExist);
                }
                else if (code == 203)
                {
                    PrintErrorName(tmp, "InvalidAlgorithm");
                    PrintError(InvalidAlgorithm);
                }
                else
                {
                    PrintError(Success);
                }
            }
        }
        else if (strcmp(tmp, "DIJKSTRAMIN") == 0)
        {
            char* start = strtok(NULL, " ");
            char* end = strtok(NULL, " ");
            if (start == NULL || end == NULL)
            {
                PrintErrorName(tmp, "VertexKeyNotExist");
                PrintError(VertexKeyNotExist);
            }
            else
            {
                auto code = FindShortestPathDijkstraUsingMinHeap(atoi(start), atoi(end));
                if (code == 201)
                {
                    PrintErrorName(tmp, "InvalidVertexKey");
                    PrintError(InvalidVertexKey);
                }
                else if (code == 202)
                {
                    PrintErrorName(tmp, "GraphNotExist");
                    PrintError(GraphNotExist);
                }
                else if (code == 203)
                {
                    PrintErrorName(tmp, "InvalidAlgorithm");
                    PrintError(InvalidAlgorithm);
                }
                else
                {
                    PrintError(Success);
                }
            }
        }
        else if (strcmp(tmp, "BELLMANFORD") == 0)
        {

        }
        else if (strcmp(tmp, "FLOYD") == 0)
        {

        }
        else if (strcmp(tmp, "CONFIG") == 0)
        {
            char* option = strtok(NULL, " ");
            char* SortSel = strtok(NULL, " ");
            if (strcmp(option, "-sort") != 0)
            {
                PrintErrorName(tmp, "InvalidOptionName");
                PrintError(InvalidOptionName);
            }
            else
            {
                if (strcmp(SortSel, "quick") == 0)
                    sel = 1;
                else if (strcmp(SortSel, "insert") == 0)
                    sel = 2;
                else if (strcmp(SortSel, "merge") == 0)
                    sel = 3;
                else if (strcmp(SortSel, "heap") == 0)
                    sel = 4;
                else if (strcmp(SortSel, "bubble") == 0)
                    sel = 5;
                else
                {
                    PrintErrorName(tmp, "InvalidAlgorithmName");
                    PrintError(InvalidAlgorithmName);
                }
            }
        }
        else
        {
            PrintErrorName(tmp, "NonDefinedCommand");
            PrintError(NonDefinedCommand);
        }
    }
}
void Manager::PrintError(Result result)//Error code print
{
    fout << "=================" << endl;
    fout << "Error code: " << result << endl;
    fout << "=================" << endl << endl;
    cout << "=================" << endl;
    cout << "Error code: " << result << endl;
    cout << "=================" << endl << endl;
}
void Manager::PrintErrorName(char* command, string name)//Error code print
{
    fout << "====== " << command << " ======" << endl;
    fout << name << endl;
    fout << "====================" << endl << endl;
    cout << "====== " << command << " ======" << endl;
    cout << name << endl;
    cout << "====================" << endl << endl;
}
/// <summary>
/// make a graph
/// </summary>
Result Manager::Load(const char* filepath)
{
    fstream map;
    map.open(filepath);
    if (!map)
        return LoadFileNotExist;
    string temp;
    int VertexCount = 0;
    getline(map, temp);//read line
    char* GraphSize = strtok((char*)temp.c_str(), " ");
    m_graph.SetSize(atoi(GraphSize));
    while (!map.eof())
    {
        getline(map, temp);//read line
        if (temp == "") break;
        string StoreName = strtok((char*)temp.c_str(), " ");
        //m_graph.AddVertex(VertexCount);
        while (1)
        {
            string name1 = strtok(NULL, " ");
            if (name1 == "" || strcmp((char*)name1.c_str(),"/") == 0) break;
            StoreName = StoreName + " " + name1;
        }
        m_graph.AddVertex(VertexCount, (char*)StoreName.c_str());
        for (int i = 0; i < m_graph.Size(); i++)
        {
            char* weight = strtok(NULL, " ");
            if (weight == NULL) break;
            if(atoi(weight) != 0)
                m_graph.AddEdge(VertexCount, i, atoi(weight));
        }
        VertexCount++;
    }
    return Success;
}
Result Manager::Update()
{
    if (m_graph.Size() == 0)
        return FaildtoUpdatePath;
    Vertex* moveV = m_graph.GetHead();
    string tempstr;
    vector<char*> v;
    char* temp1 = new char[100];
    char* temp2 = new char[100];
    for (int i = 0; i < m_graph.Size(); i++)
    {
        Edge* moveE = moveV->GetHeadOfEdge();
        for (int j = 0; j < m_graph.FindVertex(moveV->GetKey())->Size(); j++)
        {
            strcpy(temp1, moveV->GetName());
            string people1 = strtok(temp1, "'");
            char* trash1 = strtok(NULL, " ");
            //char* shopname1 = strtok(NULL, " ");
            while (1)
            {
                char* shopnametemp = strtok(NULL, " ");
                if (shopnametemp == NULL) break;
                tempstr = tempstr + shopnametemp + ' ';
            }
            strcpy(temp2, m_graph.FindVertex(moveE->GetKey())->GetName());
            string people2 = strtok(temp2, "'");
            char* trash2 = strtok(NULL, " ");
            char* shopname2 = strtok(NULL, " ");
            v.push_back(shopname2);
            while (1)
            {
                shopname2 = strtok(NULL, " ");
                if (shopname2 == NULL) break;
                v.push_back(shopname2);
            }
            if (people1.size() >= 5 && people2.size() >= 5)
            {
                for (int i = 0; i <= people2.size()-5; i++)
                {
                    string cut = people2.substr(i, 5);
                    if (RabinKarpCompare(people1, cut) == Success && people1.size() >= 10 && people2.size() >= 10)
                    {//owner name same 5 && name size bigger same than 10
                        moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.9));//10% drop in costs
                        for (int i = 0; i <= people2.size() - 10; i++)
                        {
                            string cut = people2.substr(i, 10);
                            if (RabinKarpCompare(people1, cut) == Success)
                            {//owner name same 10
                                moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.9));//10% drop in costs
                                for (int i = 0; i <= v.size() - 10; i++)
                                {
                                    if (RabinKarpCompare(tempstr, v[i]) == Success)
                                    {//store name same
                                        moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.8));//10% drop in costs
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                    else if (RabinKarpCompare(people1, cut) == Success && people2.size() < 10)
                    {//owner name same 5 && name size lower than 10
                        moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.9));//10% drop in costs
                        break;
                    }
                }
            }
            moveE = moveE->GetNext();//Edge move
            tempstr = "";
            v.clear();
        }
        moveV = moveV->GetNext();//Vertex move
    }
    return Success;
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
Result Manager::Print()
{
    if (m_graph.Size() == 0)
        return GraphNotExist;//GraphNotExist if there is no graph
    m_graph.Print(fout);
    return Success;//Success if the printing is successful
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with BFS (stack and queue)
/// </summary>
Result Manager::FindPathBfs(int startVertexKey, int endVertexKey)
{
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
        return InvalidVertexKey;//Vertex entered as a factor is not in the island's distance information data
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    vector<int> v = m_graph.FindPathBfs(startVertexKey, endVertexKey);//BFS
    vector<int> sorted = v;//sorted path
    string course;
    fout << "======BFS======" << endl;
    cout << "======BFS======" << endl;
    fout << "shortest path: ";
    cout << "shortest path: ";
    for (int i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";
        cout << v[i] << " ";
    }
    fout << endl << "sorted path: ";
    cout << endl << "sorted path: ";
    //SORT select
    if (sel == 1)
        QuickSort(sorted, 0, sorted.size() - 1);
    else if (sel == 2)
        InsertSort(sorted);
    else if (sel == 3)
        MergeSort(sorted, 0, sorted.size() - 1);
    else if (sel == 4)
        HeapSort(sorted);
    else if (sel == 5)
        BubbleSort(sorted);
    for (int i = 0; i < sorted.size(); i++)
    {
        fout << sorted[i] << " ";
        cout << sorted[i] << " ";
    }
    int length = 0;
    auto vertex = m_graph.FindVertex(v[0]);
    course += vertex->GetName();//course save
    course += ' ';
    for (int i = 1; i < v.size(); i++)
    {
        auto edge = vertex->GetHeadOfEdge();
        while (edge->GetKey() != v[i])
        {
            edge = edge->GetNext();
        }
        length += edge->GetWeight();
        course += m_graph.FindVertex(edge->GetKey())->GetName();//course save
        course += ' ';
        vertex = m_graph.FindVertex(edge->GetKey());
    }
    fout << endl << "path length: " << length << endl;
    cout << endl << "path length: " << length << endl;
    //rabincarp
    fout << "Course : " << course << endl;
    cout << "Course : " << course << endl;
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
        return InvalidVertexKey;//Vertex entered as a factor is not in the island's distance information data
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    if (m_graph.IsNegativeEdge())
        return InvalidAlgorithm;//Negative Weight exists in the island's distance information data.
    vector<int> v = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);//BFS
    vector<int> sorted = v;//sorted path
    string course;
    fout << "======DIJKSTRA======" << endl;
    cout << "======DIJKSTRA======" << endl;
    fout << "shortest path: ";
    cout << "shortest path: ";
    for (int i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";
        cout << v[i] << " ";
    }
    fout << endl << "sorted path: ";
    cout << endl << "sorted path: ";
    //SORT select
    if (sel == 1)
        QuickSort(sorted, 0, sorted.size() - 1);
    else if (sel == 2)
        InsertSort(sorted);
    else if (sel == 3)
        MergeSort(sorted, 0, sorted.size() - 1);
    else if (sel == 4)
        HeapSort(sorted);
    else if (sel == 5)
        BubbleSort(sorted);
    for (int i = 0; i < sorted.size(); i++)
    {
        fout << sorted[i] << " ";
        cout << sorted[i] << " ";
    }
    int length = 0;
    auto vertex = m_graph.FindVertex(v[0]);
    course += vertex->GetName();//course save
    course += ' ';
    for (int i = 1; i < v.size(); i++)
    {
        auto edge = vertex->GetHeadOfEdge();
        while (edge->GetKey() != v[i])
        {
            edge = edge->GetNext();
        }
        length += edge->GetWeight();
        course += m_graph.FindVertex(edge->GetKey())->GetName();//course save
        course += ' ';
        vertex = m_graph.FindVertex(edge->GetKey());
    }
    fout << endl << "path length: " << length << endl;
    cout << endl << "path length: " << length << endl;
    //rabincarp
    fout << "Course : " << course << endl;
    cout << "Course : " << course << endl;
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
        return InvalidVertexKey;//Vertex entered as a factor is not in the island's distance information data
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    if (m_graph.IsNegativeEdge())
        return InvalidAlgorithm;//Negative Weight exists in the island's distance information data.
    vector<int> v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);//BFS
    vector<int> sorted = v;//sorted path
    string course;
    fout << "======DIJKSTRAMIN======" << endl;
    cout << "======DIJKSTRAMIN======" << endl;
    fout << "shortest path: ";
    cout << "shortest path: ";
    for (int i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";
        cout << v[i] << " ";
    }
    fout << endl << "sorted path: ";
    cout << endl << "sorted path: ";
    //SORT select
    if (sel == 1)
        QuickSort(sorted, 0, sorted.size() - 1);
    else if (sel == 2)
        InsertSort(sorted);
    else if (sel == 3)
        MergeSort(sorted, 0, sorted.size() - 1);
    else if (sel == 4)
        HeapSort(sorted);
    else if (sel == 5)
        BubbleSort(sorted);
    for (int i = 0; i < sorted.size(); i++)
    {
        fout << sorted[i] << " ";
        cout << sorted[i] << " ";
    }
    int length = 0;
    auto vertex = m_graph.FindVertex(v[0]);
    course += vertex->GetName();//course save
    course += ' ';
    for (int i = 1; i < v.size(); i++)
    {
        auto edge = vertex->GetHeadOfEdge();
        while (edge->GetKey() != v[i])
        {
            edge = edge->GetNext();
        }
        length += edge->GetWeight();
        course += m_graph.FindVertex(edge->GetKey())->GetName();//course save
        course += ' ';
        vertex = m_graph.FindVertex(edge->GetKey());
    }
    fout << endl << "path length: " << length << endl;
    cout << endl << "path length: " << length << endl;
    //rabincarp
    fout << "Course : " << course << endl;
    cout << "Course : " << course << endl;
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    return Success;
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    // TODO: implement
    return Success;
}

Result Manager::FindShortestPathFloyd()
{
    return Success;
}

Result Manager::RabinKarpCompare(string longstr, string shortstr)
{
    int Lsize = longstr.size();
    int Ssize = shortstr.size();
    int LHash = 0, SHash = 0, pow = 1;
    for (int i = 0; i < Lsize - Ssize; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < Ssize; j++)
            {//Repeat as long as partial string
                if ('A' <= longstr[Ssize - 1 - j] && longstr[Ssize - 1 - j] <= 'Z')
                    longstr[Ssize - 1 - j] = longstr[Ssize - 1 - j] + 32;
                if ('A' <= shortstr[Ssize - 1 - j] && shortstr[Ssize - 1 - j] <= 'Z')
                    shortstr[Ssize - 1 - j] = shortstr[Ssize - 1 - j] + 32;
                LHash = LHash + longstr[Ssize - 1 - j] * pow;
                SHash = SHash + shortstr[Ssize - 1 - j] * pow;
                if (j < Ssize - 1)
                    pow = pow * 2;//square number increment
            }
        }
        else//Remove the front one and add the back one.
            LHash = 2 * (LHash - longstr[i - 1] * pow) + longstr[Ssize - 1 + i];
        if (LHash == SHash)
        {//Check string matching if hash values are the same
            bool check = true;
            for (int j = 0; j < Ssize; j++)
            {
                if (longstr[i + j] != shortstr[j])//Mismatch!!
                    return Fail;
            }
            if (check == true)//Match!!
                return Success;
        }
    }
    return Fail;//Hash Mismatch!!
}

void Manager::QuickSort(vector<int>& v, int left, int right)
{
    int i = left + 1;
    int j = right;
    int pivot = v[left];
    while (i < j)
    {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i < j)
        {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    swap(v[left], v[j]);

    if (left + 1 < j) QuickSort(v, left, j - 1);
    if (i < right) QuickSort(v, i, right);
}

void Manager::InsertSort(vector<int>& v)
{
    int i, j, key;
    for (i = 1; i < v.size(); i++)
    {
        key = v[i];//set key
        for (j = i - 1; j >= 0; j--)
        {
            if (v[j] > key)
                v[j + 1] = v[j];//Push
            else
                break;
        }
        v[j + 1] = key;//Insert key value
    }
}

void Manager::MergeSort(vector<int>& v, int left, int right)
{
    int mid;
    if (left >= right)
        return;
    mid = (left + right) / 2;//Divide
    MergeSort(v, left, mid);//left Conquer
    MergeSort(v, mid + 1, right);//right Conquer
    //merge
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right)
    {
        if (v[i] <= v[j])
            temp[k++] = v[i++];
        else
            temp[k++] = v[j++];
    }
    if (i > mid)
        for (int l = j; l <= right; l++)
            temp[k++] = v[l];
    else
        for (int l = i; l <= right; l++)
            temp[k++] = v[l];
    for (int l = left; l <= right; l++)
        v[l] = temp[l];//array copy
}

void Manager::HeapSort(vector<int>& v)
{
    MinHeap<int, int> heap;
    for (int i = 0; i < v.size(); i++)
        heap.Push(v[i], 0);
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = heap.Top().first;
        heap.Pop();
    }
}

void Manager::BubbleSort(vector<int>& v)
{
    for (int i = 0; i < v.size()-1; i++)
    {
        for (int j = 0; j < v.size() - 1 - i; i++)
        {
            if (v[i] > v[i + 1])
                swap(v[i], v[i + 1]);
        }
    }
}
