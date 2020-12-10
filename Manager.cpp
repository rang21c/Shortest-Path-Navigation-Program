#include "Manager.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <chrono>
#include "MinHeap.h"
using namespace std;
vector<int> temp(999999, 0);

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();
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
            char* file = strtok(NULL, " ");
            if (file == NULL)
            {
                PrintErrorName(tmp, "VertexKeyNotExist");
                PrintError(VertexKeyNotExist);
            }
            else
            {
                if (Load(file) == LoadFileNotExist)
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
        }
        else if (strcmp(tmp, "UPDATE") == 0)
        {
            if (Update() == FaildtoUpdatePath)
            {
                PrintErrorName(tmp, "FaildtoUpdatePath");
                fout << "=================" << endl;
                fout << "Error code: 005" << endl;
                fout << "=================" << endl << endl;
                cout << "=================" << endl;
                cout << "Error code: 005" << endl;
                cout << "=================" << endl << endl;
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
            char* start = strtok(NULL, " ");
            char* end = strtok(NULL, " ");
            if (start == NULL || end == NULL)
            {
                PrintErrorName(tmp, "VertexKeyNotExist");
                PrintError(VertexKeyNotExist);
            }
            else
            {
                auto code = FindShortestPathBellmanFord(atoi(start), atoi(end));
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
                else if (code == 204)
                {
                    PrintErrorName(tmp, "NegativeCycleDetected");
                    PrintError(NegativeCycleDetected);
                }
                else
                {
                    PrintError(Success);
                }
            }
        }
        else if (strcmp(tmp, "FLOYD") == 0)
        {
            auto code = FindShortestPathFloyd();
            if (code == 202)
            {
                PrintErrorName(tmp, "GraphNotExist");
                PrintError(GraphNotExist);
            }
            else if (code == 204)
            {
                PrintErrorName(tmp, "NegativeCycleDetected");
                PrintError(NegativeCycleDetected);
            }
            else
            {
                PrintError(Success);
            }
        }
        else if (strcmp(tmp, "CONFIG") == 0)
        {
            char* option = strtok(NULL, " ");
            char* SortSel = strtok(NULL, " ");
            if (strcmp(option, "-sort") != 0)
            {
                PrintErrorName(tmp, "InvalidOptionName");
                fout << "=================" << endl;
                fout << "Error code: 003" << endl;
                fout << "=================" << endl << endl;
                cout << "=================" << endl;
                cout << "Error code: 003" << endl;
                cout << "=================" << endl << endl;
            }
            else
            {
                if (strcmp(SortSel, "quick") == 0)
                {
                    PrintErrorName((char*)"CONFIG LOG", "Sorted by : Quick Sorting");
                    PrintError(Success);
                    sel = 1;
                }
                else if (strcmp(SortSel, "insert") == 0)
                {
                    PrintErrorName((char*)"CONFIG LOG", "Sorted by : Insert Sorting");
                    PrintError(Success);
                    sel = 2;
                }
                else if (strcmp(SortSel, "merge") == 0)
                {
                    PrintErrorName((char*)"CONFIG LOG", "Sorted by : Merge Sorting");
                    PrintError(Success);
                    sel = 3;
                }
                else if (strcmp(SortSel, "heap") == 0)
                {
                    PrintErrorName((char*)"CONFIG LOG", "Sorted by : Heap Sorting");
                    PrintError(Success);
                    sel = 4;
                }
                else if (strcmp(SortSel, "bubble") == 0)
                {
                    PrintErrorName((char*)"CONFIG LOG", "Sorted by : Bubble Sorting");
                    PrintError(Success);
                    sel = 5;
                }
                else if (strcmp(SortSel, "counting") == 0)
                {
                    PrintErrorName((char*)"CONFIG LOG", "Sorted by : Counting Sorting");
                    PrintError(Success);
                    sel = 6;
                }
                else
                {
                    PrintErrorName(tmp, "InvalidAlgorithmName");
                    fout << "=================" << endl;
                    fout << "Error code: 001" << endl;
                    fout << "=================" << endl << endl;
                    cout << "=================" << endl;
                    cout << "Error code: 001" << endl;
                    cout << "=================" << endl << endl;
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
        string StoreName = strtok((char*)temp.c_str(), " ");//person name
        while (1)
        {
            string name1 = strtok(NULL, " ");
            if (name1 == "" || strcmp((char*)name1.c_str(),"/") == 0) 
                break;
            StoreName = StoreName + " " + name1;//Make full name
        }
        m_graph.AddVertex(VertexCount, (char*)StoreName.c_str());//add Vertex
        for (int i = 0; i < m_graph.Size(); i++)
        {//add Edge loop
            char* weight = strtok(NULL, " ");//get weight
            if (weight == NULL) break;
            if(atoi(weight) != 0)
                m_graph.AddEdge(VertexCount, i, atoi(weight));//add Edge
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
            string people1 = strtok(temp1, "'");//person name
            char* trash1 = strtok(NULL, " ");//trash value "s"
            while (1)
            {
                char* shopnametemp = strtok(NULL, " ");
                if (shopnametemp == NULL) break;
                tempstr = tempstr + shopnametemp + ' ';
            }
            strcpy(temp2, m_graph.FindVertex(moveE->GetKey())->GetName());
            string people2 = strtok(temp2, "'");//person name
            char* trash2 = strtok(NULL, " ");//trash value "s"
            char* shopname2 = strtok(NULL, " ");
            v.push_back(shopname2);
            while (1)
            {
                shopname2 = strtok(NULL, " ");
                if (shopname2 == NULL) break;
                v.push_back(shopname2);//store shopname
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
                                for (int i = 0; i < v.size(); i++)
                                {
                                    if (RabinKarpCompare(tempstr, v[i]) == Success)
                                    {//store name same
                                        moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.8));//20% drop in costs
                                        break;
                                    }
                                }
                                break;
                            }
                            else if(RabinKarpCompare(people1, cut) != Success && i == people2.size() - 10)
                            {//owner name not same 10
                                for (int i = 0; i < v.size(); i++)
                                {
                                    if (RabinKarpCompare(tempstr, v[i]) == Success)
                                    {//store name same
                                        moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.8));//20% drop in costs
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                    else if (RabinKarpCompare(people1, cut) == Success && (people1.size() < 10 || people2.size() < 10))
                    {//owner name same 5 && name size lower than 10
                        moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.9));//10% drop in costs
                        for (int i = 0; i < v.size(); i++)
                        {
                            if (RabinKarpCompare(tempstr, v[i]) == Success)
                            {//store name same
                                moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.8));//20% drop in costs
                                break;
                            }
                        }
                        break;
                    }
                    else
                    {
                        for (int i = 0; i < v.size(); i++)
                        {
                            if (RabinKarpCompare(tempstr, v[i]) == Success)
                            {//store name same
                                moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.8));//20% drop in costs
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < v.size(); i++)
                {
                    if (RabinKarpCompare(tempstr, v[i]) == Success)
                    {//store name same
                        moveE = m_graph.ChangeEdge(moveV, moveE, ceil(double(moveE->GetWeight()) * 0.8));//20% drop in costs
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
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
        return InvalidVertexKey;//Vertex entered as a factor is not in the island's distance information data
    //std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();//chrono Library
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
    fout << endl << "sorted nodes: ";
    cout << endl << "sorted nodes: ";
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
    else if (sel == 6)
        CountingSort(sorted);
    //std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();//chrono Library
    //std::chrono::nanoseconds nano = EndTime - StartTime;//chrono Library
    for (int i = 0; i < sorted.size(); i++)
    {
        fout << sorted[i] << " ";
        cout << sorted[i] << " ";
    }
    int length = 0;
    auto vertex = m_graph.FindVertex(v[0]);
    for (int i = 1; i < v.size(); i++)
    {
        auto edge = vertex->GetHeadOfEdge();
        while (edge->GetKey() != v[i])
        {
            edge = edge->GetNext();
        }
        length += edge->GetWeight();//length +
        vertex = m_graph.FindVertex(edge->GetKey());
    }
    for (int i = 0; i < sorted.size(); i++)
    {
        auto vertex = m_graph.FindVertex(sorted[i]);
        course += vertex->GetName();//course save
        course += ' ';
    }
    fout << endl << "path length: " << length << endl;
    cout << endl << "path length: " << length << endl;
    //rabincarp Compression
    course = Compression(course);
    fout << "Course : " << course << endl;
    cout << "Course : " << course << endl;
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    //cout << "BFS Time taken (nano seconds) : " << nano.count() << " nanoseconds" << endl << endl;//chrono Library
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
        return InvalidVertexKey;//Vertex entered as a factor is not in the island's distance information data
    if (m_graph.IsNegativeEdge())
        return InvalidAlgorithm;//Negative Weight exists in the island's distance information data.
    //std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();
    vector<int> v = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);//Dijkstra
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
    fout << endl << "sorted nodes: ";
    cout << endl << "sorted nodes: ";
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
    else if (sel == 6)
        CountingSort(sorted);
    //std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();
    //std::chrono::nanoseconds nano = EndTime - StartTime;
    for (int i = 0; i < sorted.size(); i++)
    {
        fout << sorted[i] << " ";
        cout << sorted[i] << " ";
    }
    int length = 0;
    auto vertex = m_graph.FindVertex(v[0]);
    for (int i = 1; i < v.size(); i++)
    {
        auto edge = vertex->GetHeadOfEdge();
        while (edge->GetKey() != v[i])
        {
            edge = edge->GetNext();
        }
        length += edge->GetWeight();//length +
        vertex = m_graph.FindVertex(edge->GetKey());
    }
    for (int i = 0; i < sorted.size(); i++)
    {
        auto vertex = m_graph.FindVertex(sorted[i]);
        course += vertex->GetName();//course save
        course += ' ';
    }
    fout << endl << "path length: " << length << endl;
    cout << endl << "path length: " << length << endl;
    //rabincarp Compression
    course = Compression(course);
    fout << "Course : " << course << endl;
    cout << "Course : " << course << endl;
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    //cout << "DIJKSTRA Time taken (nano seconds) " << nano.count() << " nanoseconds" << endl << endl;
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
        return InvalidVertexKey;//Vertex entered as a factor is not in the island's distance information data
    if (m_graph.IsNegativeEdge())
        return InvalidAlgorithm;//Negative Weight exists in the island's distance information data.
    //std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();
    vector<int> v = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);//DIJKSTRAMIN
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
    fout << endl << "sorted nodes: ";
    cout << endl << "sorted nodes: ";
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
    else if (sel == 6)
        CountingSort(sorted);
    //std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();
    //std::chrono::nanoseconds nano = EndTime - StartTime;
    for (int i = 0; i < sorted.size(); i++)
    {
        fout << sorted[i] << " ";
        cout << sorted[i] << " ";
    }
    int length = 0;
    auto vertex = m_graph.FindVertex(v[0]);
    for (int i = 1; i < v.size(); i++)
    {
        auto edge = vertex->GetHeadOfEdge();
        while (edge->GetKey() != v[i])
        {
            edge = edge->GetNext();
        }
        length += edge->GetWeight();//length +
        vertex = m_graph.FindVertex(edge->GetKey());
    }
    for (int i = 0; i < sorted.size(); i++)
    {
        auto vertex = m_graph.FindVertex(sorted[i]);
        course += vertex->GetName();//course save
        course += ' ';
    }
    fout << endl << "path length: " << length << endl;
    cout << endl << "path length: " << length << endl;
    //rabincarp Compression
    course = Compression(course);
    fout << "Course : " << course << endl;
    cout << "Course : " << course << endl;
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    //cout << "DIJKSTRAMIN Time taken (nano seconds) : " << nano.count() << " nanoseconds" << endl << endl;
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    if (m_graph.FindVertex(startVertexKey) == NULL || m_graph.FindVertex(endVertexKey) == NULL)
        return InvalidVertexKey;//Vertex entered as a factor is not in the island's distance information data
    //std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();
    vector<int> v = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);//BELLMANFORD
    if(v.size() == 0)
        return NegativeCycleDetected;//Negative cycle exists in the island's distance information data.
    vector<int> sorted = v;//sorted path
    string course;
    fout << "======BELLMANFORD======" << endl;
    cout << "======BELLMANFORD======" << endl;
    fout << "shortest path: ";
    cout << "shortest path: ";
    for (int i = 0; i < v.size(); i++)
    {
        fout << v[i] << " ";
        cout << v[i] << " ";
    }
    fout << endl << "sorted nodes: ";
    cout << endl << "sorted nodes: ";
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
    else if (sel == 6)
        CountingSort(sorted);
    //std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();
    //std::chrono::nanoseconds nano = EndTime - StartTime;
    for (int i = 0; i < sorted.size(); i++)
    {
        fout << sorted[i] << " ";
        cout << sorted[i] << " ";
    }
    int length = 0;
    auto vertex = m_graph.FindVertex(v[0]);
    for (int i = 1; i < v.size(); i++)
    {
        auto edge = vertex->GetHeadOfEdge();
        while (edge->GetKey() != v[i])
        {
            edge = edge->GetNext();
        }
        length += edge->GetWeight();//length +
        vertex = m_graph.FindVertex(edge->GetKey());
    }
    for (int i = 0; i < sorted.size(); i++)
    {
        auto vertex = m_graph.FindVertex(sorted[i]);
        course += vertex->GetName();//course save
        course += ' ';
    }
    fout << endl << "path length: " << length << endl;
    cout << endl << "path length: " << length << endl;
    //rabincarp Compression
    course = Compression(course);
    fout << "Course : " << course << endl;
    cout << "Course : " << course << endl;
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    //cout << "BELLMANFORD Time taken (nano seconds) : " << nano.count() << " nanoseconds" << endl << endl;
    return Success;
}

Result Manager::FindShortestPathFloyd()
{
    if (m_graph.GetHead() == NULL)
        return GraphNotExist;//Island distance information data does not exist
    vector<vector<int>> v = m_graph.FindShortestPathFloyd();
    if (v.size() == 0)
        return NegativeCycleDetected;//Negative cycle exists in the island's distance information data.
    fout << "======FLOYD======" << endl;
    cout << "======FLOYD======" << endl;
    for (int i = 0; i < v[0].size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
        {
            fout << v[i][j] << " ";
            cout << v[i][j] << " ";
        }
        fout << endl;
        cout << endl;
    }
    fout << "====================" << endl << endl;
    cout << "====================" << endl << endl;
    return Success;
}

Result Manager::RabinKarpCompare(string longstr, string shortstr)
{
    int Lsize = longstr.size();
    int Ssize = shortstr.size();
    int LHash = 0;
    int SHash = 0;
    int pow = 1;
    bool check = false;
    if (Lsize < Ssize)
        return Fail;
    else
    {
        for (int i = 0; i < Ssize; i++)
        {//Repeat as long as partial string
            if ('A' <= longstr[Ssize - 1 - i] && longstr[Ssize - 1 - i] <= 'Z')
                longstr[Ssize - 1 - i] = longstr[Ssize - 1 - i] + 32;
            if ('A' <= shortstr[Ssize - 1 - i] && shortstr[Ssize - 1 - i] <= 'Z')
                shortstr[Ssize - 1 - i] = shortstr[Ssize - 1 - i] + 32;
            LHash += longstr[Ssize - 1 - i] * pow;
            SHash += shortstr[Ssize - 1 - i] * pow;
            if (i < Ssize - 1)
                pow *= 2;//square number increment
        }
        if (LHash == SHash)
        {//Check string matching if hash values are the same
            check = true;
            for (int j = 0; j < Ssize; j++)
            {
                if (longstr[j] != shortstr[j])//Mismatch
                {
                    check = false;
                    break;
                }
            }
            if (check == true)
                return Success;
        }
        for (int i = 1; i <= Lsize - Ssize; i++)
        {//Remove the front one and add the back one
            if ('A' <= longstr[Ssize - 1 + i] && longstr[Ssize - 1 + i] <= 'Z')
                longstr[Ssize - 1 + i] = longstr[Ssize - 1 + i] + 32;
            LHash = 2 * (LHash - longstr[i - 1] * pow) + longstr[Ssize - 1 + i];
            if (LHash == SHash)
            {//Check string matching if hash values are the same
                check = true;
                for (int j = 0; j < Ssize; j++)
                {
                    if (longstr[i + j] != shortstr[j])//Mismatch
                    {
                        check = false;
                        break;
                    }
                }
                if (check == true)
                    return Success;
            }
        }
    }
    if (check == true)
        return Success;//Hash Match
    if (check == false)
        return Fail;//Hash Mismatch
    return Fail;//Hash Mismatch
}

void Manager::QuickSort(vector<int>& v, int left, int right)
{
    int i = left + 1;
    int j = right;
    int pivot = v[left];
    while (i <= j)
    {
        while (v[i] <= pivot && i < j) i++;//pointer ++
        while (v[j] > pivot && i <= j) j--;//potiter --
        if (i < j)
        {
            swap(v[i], v[j]);
        }
        else
            break;
    }
    swap(v[left], v[j]);
    if (left + 1 < j) QuickSort(v, left, j - 1);//recursive
    if (i < right) QuickSort(v, i, right);//recursive
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
            temp[k++] = v[i++];//pointer ++
        else
            temp[k++] = v[j++];//pointer ++
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
        heap.Push(v[i], 0);//push
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = heap.Top().first;//get heap Top
        heap.Pop();
    }
}

void Manager::BubbleSort(vector<int>& v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = 0; j < v.size() - 1 - i; i++)
        {
            if (v[i] > v[i + 1])
                swap(v[i], v[i + 1]);//swap
        }
    }
}

void Manager::CountingSort(vector<int>& v)
{
    vector<int> count(m_graph.Size(), 0);
    for (int i = 0; i < v.size(); i++)
        count[v[i]]++;//COUNTING
    v.clear();//CLEAR
    for (int i = 0; i < count.size(); i++)
    {
        if (count[i] != 0)
        {
            for (int j = 0; j < count[i]; j++)
            {
                v.push_back(i);//push
            }
        }
    }
}

string Manager::Compression(string s)
{
    string str1;
    string str2;
    string temp;
    string Shop = "";
    string Class = "";
    string Academy = "";
    int count = 0;
    int shop_count = 0;
    int class_count = 0;
    int academy_count = 0;
    for (int i = s.size() / 2; i > 0; i--)
    {
        for (int j = 0; j < s.size(); j++)
        {
            if (j + i < s.size())
            {
                str1 = s.substr(j, i);
                str2 = s.substr(j + i);
                if (RabinKarpCompare(str2, str1) == Success && str1.size() > 1)
                {          
                    for (int k = 0; k <= s.size() - i; k++)
                    {//RabinKarp Official Compression Law No. 2
                        temp = s.substr(k, i);
                        if (RabinKarpCompare(str1, temp) == Success)
                        {
                            if (count == 0)
                                s.insert(k+i, "*");//insert *
                            count++;
                        }
                        if (count > 1)
                        {
                            s.erase(k, i);//erase same
                            count = 1;
                        }
                    }
                    for (int k = 0; k <= s.size() - 4; k++)
                    {//Shop check
                        Shop = s.substr(k, 4);
                        if (RabinKarpCompare(Shop, "Shop") == Success)
                        {
                            shop_count++;
                        }
                        if (RabinKarpCompare(Shop, "Shop") == Success && shop_count > 1)
                        {
                            s.erase(k, 5);//erase same
                        }
                    }
                    for (int k = 0; k <= s.size() - 5; k++)
                    {//Class check
                        Class = s.substr(k, 5);
                        if (RabinKarpCompare(Class, "Class") == Success)
                        {
                            class_count++;
                        }
                        if (RabinKarpCompare(Class, "Class") == Success && class_count > 1)
                        {
                            s.erase(k, 6);//erase same
                        }
                    }
                    for (int k = 0; k <= s.size() - 7; k++)
                    {//Academy check
                        Academy = s.substr(k, 7);
                        if (RabinKarpCompare(Academy, "Academy") == Success)
                        {
                            academy_count++;
                        }
                        if (RabinKarpCompare(Academy, "Academy") == Success && academy_count > 1)
                        {
                            s.erase(k, 8);//erase same
                        }
                    }
                    return s;
                }
            }
        }
    }
    return s;
}
