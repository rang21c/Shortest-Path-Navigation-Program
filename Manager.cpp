#include "Manager.h"
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

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
    //ferr.open(ERROR_LOG_PATH);
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
    char* temp1;
    char* temp2;
    for (int i = 0; i < m_graph.Size(); i++)
    {
        Edge* moveE = moveV->GetHeadOfEdge();
        for (int j = 0; j < m_graph.FindVertex(moveV->GetKey())->Size(); j++)
        {
            temp1 = moveV->GetName();
            char* people1 = strtok(temp1, "'");
            temp2 = m_graph.FindVertex(moveE->GetKey())->GetName();
            char* people2 = strtok(temp2, "'");
            //RabinKarpCompare();
            char* trash1 = strtok(temp1, " ");
            char* trash2 = strtok(temp2, " ");
            moveE = moveE->GetNext();//Edge move
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
/// find the path from startVertexKey to endVertexKey with DFS (stack)
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
Result Manager::FindPathDfs(int startVertexKey, int endVertexKey)
{
    // TODO: implement
    return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
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
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    // TODO: implement
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
    // TODO: implement
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

Result Manager::RabinKarpCompare(const char* CompareString)
{

    return Success;
}