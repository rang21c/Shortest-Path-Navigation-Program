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
    fout << "======" << command << "======" << endl;
    fout << name << endl;
    fout << "====================" << endl << endl;
    cout << "======" << command << "======" << endl;
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
        char* StoreName = strtok((char*)temp.c_str(), " ");
        if (StoreName == NULL) break;
        m_graph.AddVertex(VertexCount);
        while (1)
        {
            char* name1 = strtok(NULL, " ");
            if (name1 == NULL || strcmp(name1,"/") == 0) break;
            //StoreName = StoreName + " " + name1;
        }
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
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
    if (m_graph.Size() == 0)
        return GraphNotExist;
    m_graph.Print(fout);
    return Success;
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

Result Manager::RabinKarpCompare(const char* CompareString)
{
    // TODO: implement
    return Success;
}