#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;

public:
    MinHeap() 
    {
        m_vec.push_back(make_pair(-1, -1));//m_vec[0] not use
    }

    void Push(TKey key, TValue value)
    {
        m_vec.push_back(make_pair(key, value));
        Heapify(m_vec.size()-1);
    }

    void Pop()
    {
        Heapify(1);//delete m_vec[1]
    }

    std::pair<TKey, TValue> Top()
    {
        return m_vec[1];
    }

    std::pair<TKey, TValue> Get(TValue target)
    {
        for (int i = 0; i < m_vec.size(); i++)
        {
            if (m_vec[i].second == target)
                return m_vec[i];
        }
        return NULL;
    }

    bool IsEmpty()
    {
        return m_vec.empty();
    }
    /// <summary>
    /// change the key of the node which the value is the target.<para/>
    /// In general, the newKey should be smaller than the old key.<para/>
    /// </summary>
    void DecKey(TValue target, TKey newKey)
    {
        int i = 0;
        for (i = 0; i < m_vec.size(); i++)
            if (target == m_vec[i].second)
                m_vec[i].first = newKey; break;
        pair<TKey, TValue> temp = m_vec[i];
        int curnode = i;
        while (curnode != 1 && m_vec[curnode / 2].first > temp.first)
        {
            m_vec[curnode].first = m_vec[curnode / 2].first;
            m_vec[curnode].second = m_vec[curnode / 2].second;
            curnode = curnode / 2;//move parent
        }
        m_vec[curnode].first = temp.first;
        m_vec[curnode].second = temp.second;
    }

private:
    /// <summary>
    /// heap-sort, heapify.<para/>
    /// this function can be called recursively
    /// </summary>
    void Heapify(int index)
    {
        if (index == 1)//pop m_vec[1]
        {
            if (IsEmpty())
                return;
            pair<TKey, TValue> last = m_vec[m_vec.size()-1];
            m_vec.pop_back();
            int curnode = 1;//root
            int child = 2;//curnode child
            while (child <= m_vec.size())
            {
                if (child < m_vec.size() && m_vec[child] < m_vec[child + 1])
                    child++;
                if (last >= m_vec[child])
                    break;
                m_vec[curnode] = m_vec[child];
                curnode = child;
                child = child * 2;
            }
            m_vec[curnode] = last;
        }
        else//push
        {
            int curnode = index;//first position
            pair<TKey, TValue> temp = m_vec[index];
            while (curnode != 1 && m_vec[curnode / 2].first > temp.first)
            {
                m_vec[curnode].first = m_vec[curnode / 2].first;
                m_vec[curnode].second = m_vec[curnode / 2].second;
                curnode = curnode / 2;//move parent
            }
            m_vec[curnode].first = temp.first;
            m_vec[curnode].second = temp.second;
        }
    }
};

#endif
