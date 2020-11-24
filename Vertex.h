#ifndef VERTEX_H
#define VERTEX_H

#ifndef NULL
#define NULL	0
#endif

#include "Edge.h"
#include <cstring>

class Vertex
{
private:
    int m_key;// the key of this vertex
    int m_size;// the number of the edges from this vertex to others
    char* m_storeName;
    Edge* m_pEHead;// the head pointer for the linked list of the edges
    Vertex* m_pNext;// the next pointer for the linked list of the vertics

public:
    Vertex() {
        m_key = 0;
        m_size = 0;
        m_storeName = new char[100];
        m_pEHead = NULL;
        m_pNext = NULL;
    }
    Vertex(int key, char* name) {
        m_key = key;
        m_size = 0;
        m_storeName = new char[100];
        strcpy(m_storeName, name);
        m_pEHead = NULL;
        m_pNext = NULL;
    }
    ~Vertex() {
        Clear();
    }

    /// set the next pointer of this vertex
    void SetNext(Vertex* pNext) { this->m_pNext = pNext; }
    void SetSize(int size) { this->m_size = size; }
    void SetHead(Edge* newhead) { this->m_pEHead = newhead; }
    /// get the key of this vertex
    int GetKey() const { return this->m_key; }
    // the next pointer of this vertex
    Vertex* GetNext() const { return this->m_pNext; }
    char* GetName() const { return this->m_storeName; }
    // the number of the edges
    int Size() const { return m_size; }
    // add edge with edgeNum at the end of the linked list for the edges
    void AddEdge(int edgeKey, int weight) // the key of the vertex for the edge// the weight of the edge
    {
        Edge* NewEdge = new Edge(edgeKey, weight);
        if (this->GetHeadOfEdge() == NULL)
        {
            this->m_pEHead = NewEdge;
        }
        else
        {
            Edge* pCur = this->m_pEHead;
            while (pCur->GetNext() != NULL)
                pCur = pCur->GetNext();
            pCur->SetNext(NewEdge);
        }
    }
    // get the head pointer of the edge
    Edge* GetHeadOfEdge() const { return this->m_pEHead; }
    /// <summary>
    /// memory free for edges
    /// </summary>
    void Clear()
    {
        Edge* moveE = this->m_pEHead;
        while (m_pEHead != NULL)
        {
            moveE = m_pEHead;
            m_pEHead = m_pEHead->GetNext();
            delete moveE;
        }
    }
};

#endif
