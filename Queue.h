#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif
const int MAX = 200;

template<class T> class Queue
{
public:
    int front;
    int rear;
    int size; //Free to define (recommand 100 or 200)
    T* val;

    Queue() {
        size = MAX;
        val = new T[size];
        front = 0;
        rear = 0;
    }
    ~Queue()
    {
        delete[] val;
    }

    void push(T value) {
        // input data
        rear = (rear + 1) % MAX;
        val[rear] = value;
    }

    void pop() {
        //Change Front
        front = (front + 1) % MAX;
    }

    bool empty() {
        //Check its empty or not
        if (front == rear)
            return true;
        else
            return false;
    }

    bool isFull() {
        //Check queue is full or not
        if (rear + 1 == size)
            return true;
        else
            return false;
    }

    T getfront() {
        return val[(front + 1) % MAX];
    }

    int qsize() {
        return (rear - front + MAX) % MAX;
    }
};


#endif