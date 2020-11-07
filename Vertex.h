#ifndef VERTEX_H
#define VERTEX_H

#ifndef NULL
#define NULL	0
#endif

#include "Edge.h"

class Vertex
{
private:
    int m_key;// the key of this vertex
    int m_size;// the number of the edges from this vertex to others
    Edge* m_pEHead;// the head pointer for the linked list of the edges
    Vertex* m_pNext;// the next pointer for the linked list of the vertics

public:
    Vertex() {
        m_key = 0;
        m_size = 0;
        m_pEHead = NULL;
        m_pNext = NULL;
    }
    Vertex(int key) {
        m_key = key;
        m_size = 0;
        m_pEHead = NULL;
        m_pNext = NULL;
    }
    ~Vertex() {
        m_key = 0;
        m_size = 0;
        m_pEHead = NULL;
        m_pNext = NULL;
    }

    /// <summary>
    /// set the next pointer of this vertex
    /// </summary>
    void SetNext(Vertex* pNext) {
        this->m_pNext = pNext;
    }
    /// <summary>
    /// get the key of this vertex
    /// </summary>
    int GetKey() const {
        return this->m_key;// the key of this vertex
    }
    /// <summary>
    /// get the next pointer of this vertex
    /// </summary>
    Vertex* GetNext() const {
        return this->m_pNext;// the next pointer of this vertex
    }
    /// <summary>
    /// get the number of the edges
    /// </summary>
    int Size() const {
        return m_size;// the number of the edges
    }

    /// <summary>
    /// add edge with edgeNum at the end of the linked list for the edges
    /// </summary>
    ///
    /// <param name="edgeKey">
    /// the key of the vertex for the edge
    /// </param>
    /// <param name="weight">
    /// the weight of the edge
    /// </param>
    void AddEdge(int edgeKey, int weight) {
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
    /// <summary>
    /// get the head pointer of the edge
    /// </summary>
    ///
    /// <returns>
    /// the ehad pointer of the edge
    /// </returns>
    Edge* GetHeadOfEdge() const {
        return this->m_pEHead;
    }
    /// <summary>
    /// memory free for edges
    /// </summary>
    void Clear();
};

#endif
