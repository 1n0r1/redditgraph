#pragma once

#include <vector>
#include "Graph.h"

using namespace std;

class PriorityQueue {
    public:
        struct HeapNode {
            Graph::SubReddit* subreddit;
            double weight;
            HeapNode* parent;
            HeapNode* leftChild;
            HeapNode* rightChild;
        };
        PriorityQueue();
        //Useful for initializing for dijkstra, where 1 node is initialy 0 and the rest is inf (-1)
        PriorityQueue(Graph::SubReddit* first, vector<Graph::SubReddit*> rest); 
        ~PriorityQueue();
        void push(Graph::SubReddit* subreddit, double weight);
        Graph::SubReddit* peakMin() const;
        double peakMinValue() const;
        double getWeight(Graph::SubReddit* sub) const;
        void popMin();
        void changeWeight(Graph::SubReddit* sub, double newWeight);
        bool isEmpty() const;
        int getSize() const;
    private:
        map<Graph::SubReddit*, HeapNode*> nodeList;
        HeapNode* root;
        int size;
        void heapifyUp(HeapNode* node);
        void heapifyDown(HeapNode* node);
        void swapParentChild(HeapNode* a, HeapNode* b);
        void swap(HeapNode* a, HeapNode* b);
        bool hasAChild(HeapNode* node) const;
        bool lesser(HeapNode* left, HeapNode* right) const;
        HeapNode* getithNode(int i) const;
};