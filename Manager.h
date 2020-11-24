#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include "Result.h"
#include "Graph.h"
#include <fstream>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    // the file stream for the result log
    std::ofstream fout;
    // graph instance to manage the vertics.
    Graph m_graph;

public:
    ~Manager();
    void Run(const char* filepath);
    void PrintError(Result result);
    void PrintErrorName(char* command, string name);
    int sel;//sort selector
private:
    Result Load(const char* filepath);
    Result Update();
    Result Print();
    Result FindPathBfs(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);
    Result FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);
    Result FindShortestPathFloyd();
    Result RabinKarpCompare(string longstr, string shortstr);
    void QuickSort(vector<int>& v, int left, int right);
    int Partition(vector<int>& v, int left, int right);
    void InsertSort(vector<int>& v);
    void MergeSort(vector<int>& v, int left, int right);
    void Merge(vector<int>& v, int left, int mid, int right);
    void HeapSort(vector<int>& v);
    void BubbleSort(vector<int>& v);
};

#endif
