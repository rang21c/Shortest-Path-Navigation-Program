#ifndef EDGE_H
#define EDGE_H

#ifndef NULL
#define NULL	0
#endif

class Edge
{
private:
    int m_key;//the key of this edge  
    int m_weight;//the weight of this edge
    Edge* m_pNext;//the next pointer for the linked list of the edges

public:
	/// constructor
    Edge() {
        m_key = 0;
        m_weight = 0;
        m_pNext = NULL;
    }
	/// copy constructor
    Edge(int key, int weight) {
        this->m_key = key;
        this->m_weight = weight;
        m_pNext = NULL;
    }
    /// set the next pointer of this edge
    void SetNext(Edge* pNext) { this->m_pNext = pNext; }
    /// get the key of this edge
    int GetKey() const { return m_key; }
    /// get the weight of this edge
    int GetWeight() const { return m_weight; }
    /// get the next pointer of this edge
    Edge* GetNext() const { return m_pNext; }
};

#endif