#include "treenode.h"

#pragma once

enum PriorityQueueType
{
    MIN,
    MAX,
};

template <typename T>
class PriorityQueue
{
private:
    size_t _max_capacity;
    PriorityQueueType _type;
    TreeNode<T>* _head;

public:
    PriorityQueue(int max_capacty, int type)
    {
        this._max_capacity = max_capacty;
        this->_type        = type;
    }

    void add();

};
