#include "PriorityQueue.h"
#include <stack>

PriorityQueue::PriorityQueue() {
    // Default constructor
    size = 0;
    nodeList = map<Graph::SubReddit*, HeapNode*>();
    root = NULL;
}

PriorityQueue::PriorityQueue(Graph::SubReddit* first, vector<Graph::SubReddit*> rest) {
    root = new HeapNode();
    root->subreddit = first;
    root->weight = 0;
    nodeList[first] = root;
    size = 1;
    for (Graph::SubReddit* s : rest) {
        push(s, -1);
    }
}
int PriorityQueue::getSize() const {
    return size;

}

PriorityQueue::~PriorityQueue() {
    // Destructor
    while (!isEmpty()) {
        popMin();
    }
}

Graph::SubReddit* PriorityQueue::peakMin() const {
    return root->subreddit;
}

double PriorityQueue::peakMinValue() const {
    return root->weight;
}

void PriorityQueue::popMin() {
    if (size == 1) {
        size--;
        delete root;
        return;
    }
    HeapNode* lastNode = getithNode(size);
    swap(lastNode, root);
    
    HeapNode* lastNodeParent = getithNode(size/2);
    if (size % 2 == 1) {
        delete lastNodeParent->rightChild;
        lastNodeParent->rightChild = NULL;
    } else {
        delete lastNodeParent->leftChild;
        lastNodeParent->leftChild = NULL;
    }
    size--;
    heapifyDown(root);
}

void PriorityQueue::push(Graph::SubReddit* subreddit, double weight) {
    size++;
    if (size == 1) {
        root = new HeapNode();
        root->parent = NULL;
        root->subreddit = subreddit;
        root->weight = weight;
        nodeList[subreddit] = root;
        return;
    }
    int parentNode = size / 2;
    HeapNode* n = getithNode(parentNode);
    if (size % 2 == 0) {
        n->leftChild = new HeapNode();
        n->leftChild->parent = n;
        n->leftChild->subreddit = subreddit;
        n->leftChild->weight = weight;
        nodeList[subreddit] = n->leftChild;
        if (weight != -1) {
            HeapNode* h = n->leftChild;
            heapifyUp(h);
            heapifyDown(h);
        }
    } else {
        n->rightChild = new HeapNode();
        n->rightChild->parent = n;
        n->rightChild->subreddit = subreddit;
        n->rightChild->weight = weight;
        nodeList[subreddit] = n->rightChild;
        if (weight != -1) {
            HeapNode* h = n->rightChild;
            heapifyUp(h);
            heapifyDown(h);
        }
    }
    
}

void PriorityQueue::changeWeight(Graph::SubReddit* sub, double newWeight) {
    HeapNode* n = nodeList[sub];
    n->weight = newWeight;
    heapifyUp(n);
    heapifyDown(n);
}


double PriorityQueue::getWeight(Graph::SubReddit* sub) const {
    HeapNode* n = nodeList.find(sub)->second;
    return n->weight;
}
bool PriorityQueue::isEmpty() const {
    if (size == 0) {
        return true;
    }
    return false;
}
void PriorityQueue::heapifyUp(HeapNode* node) {
    if (node == root) {
        return;
    }
    HeapNode* p = node->parent;
    if (p == NULL) {
        return;
    }
    if (lesser(node, p)) {
        swap(node, p);
        heapifyUp(node);
    }
}

void PriorityQueue::heapifyDown(HeapNode* node) {
    if (node == NULL) {
        return;
    }
    if (hasAChild(node) == false) {
        return;
    }

    HeapNode* l = node->leftChild;
    HeapNode* r = node->rightChild;
    if (l == NULL) { //Left NULL
        if (r == NULL) { //Both NULL
            return;
        }
        if (lesser(r, node)) {
            swap(node, r);
            heapifyDown(node);
            return;
        }
        return;
    }
    if (r == NULL) { //Right NULL
        if (lesser(l, node)) {
            swap(node, l);
            heapifyDown(node);
            return;
        }
        return;
    }
    if (lesser(r, node)|| lesser(l, node)) { //Both not NULL
        if (lesser(l, r)) {
            swap(node, l);
            heapifyDown(node);
            return;
        } else {
            swap(node, r);
            heapifyDown(node);
            return;
        }
    }
}

bool PriorityQueue::hasAChild(HeapNode* node) const{
    if (node->leftChild != NULL || node->rightChild != NULL) {
        return true;
    }
    return false;
}

bool PriorityQueue::lesser(HeapNode* left, HeapNode* right) const{
    double wl = left->weight;
    double wr = right->weight;
    if (wl == -1) {
        return false;
    }
    if (wr == -1) {
        return true;
    }
    return (wl < wr);
}

PriorityQueue::HeapNode* PriorityQueue::getithNode(int i) const {
    HeapNode* n = root;
    if (i <= 1) {
        return n;
    }
    stack<int> reversedBinary;
    while (i > 0) {
        reversedBinary.push(i%2);
        i = i / 2;
    }
    reversedBinary.pop(); //Remove first bit
    while (!reversedBinary.empty()) {
        int a = reversedBinary.top();
        reversedBinary.pop();
        if (a == 0) {
            n = n->leftChild;
        } else {
            n = n->rightChild;
        }
    }
    return n;
}

void PriorityQueue::swap(HeapNode* a, HeapNode* b) {
    if (a == root) {
        root = b;
    } else {
        if (b == root) {
            root = a;
        }
    }

    if (a == b) {
        return;
    }
    if (a->parent == b || b->parent == a) {
        swapParentChild(a,b);
        return;
    }

    HeapNode* a_parent = a->parent;
    HeapNode* b_parent = b->parent;
    HeapNode* a_left = a->leftChild;
    HeapNode* b_left = b->leftChild;
    HeapNode* a_right = a->rightChild;
    HeapNode* b_right = b->rightChild;

    a->parent = b_parent;
    b->parent = a_parent;
    a->leftChild = b_left;
    a->rightChild = b_right;
    b->leftChild = a_left;
    b->rightChild = a_right;
    
    if (b_left != NULL) {
        b_left->parent = a;
    }
    if (b_right != NULL) {
        b_right->parent = a;
    }
    if (a_left != NULL) {
        a_left->parent = b;
    }
    if (a_right != NULL) {
        a_right->parent = b;
    }
    if (a_parent != NULL) {
        if (a_parent->leftChild == a) {
            a_parent->leftChild = b;
        } else {
            a_parent->rightChild = b;
        }
    }
    if (b_parent != NULL) {
        if (b_parent->leftChild == b) {
            b_parent->leftChild = a;
        } else {
            b_parent->rightChild = a;
        }
    }
    
}

void PriorityQueue::swapParentChild(HeapNode* a, HeapNode* b) {
    HeapNode* parent = a;
    HeapNode* child = b;
    if (parent->parent == child) {
        HeapNode* temp = child;
        child = parent;
        parent = temp;
    }
    if (parent->leftChild == child) {
        if (parent->parent != NULL) {
            if (parent->parent->leftChild == parent) {
                parent->parent->leftChild = child;
            } else {
                parent->parent->rightChild = child;
            }
        }
        child->parent = parent->parent;
        parent->parent = child;
        parent->leftChild = child->leftChild;
        child->leftChild = parent;
        if (parent->leftChild != NULL) {
            parent->leftChild->parent = parent;
        }
        HeapNode* temp = parent->rightChild;
        parent->rightChild = child->rightChild;
        if (parent->rightChild != NULL) {
            parent->rightChild->parent = parent;
        }
        child->rightChild = temp;
        if (child->rightChild != NULL) {
            child->rightChild->parent = child;
        }
    } else {
        if (parent->parent != NULL) {
            if (parent->parent->leftChild == parent) {
                parent->parent->leftChild = child;
            } else {
                parent->parent->rightChild = child;
            }
        }
        child->parent = parent->parent;
        parent->parent = child;
        parent->rightChild = child->rightChild;
        child->rightChild = parent;
        if (parent->rightChild != NULL) {
            parent->rightChild->parent = parent;
        }
        HeapNode* temp = parent->leftChild;
        parent->leftChild = child->leftChild;
        if (parent->leftChild != NULL) {
            parent->leftChild->parent = parent;
        }
        child->leftChild = temp;
        if (child->leftChild != NULL) {
            child->leftChild->parent = child;
        }
    }
}