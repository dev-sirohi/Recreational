#pragma region SegmentTree

template <typename T> class SegmentTree
{
    static_assert(is_same_v<T, int> || is_same_v<T, long long>, "T must be int or long long");

  private:
    size_t _size;
    vector<T> _sourceArr;
    vector<T> _tree;
    vector<T> _lazy;

    void _Build(size_t node, size_t left, size_t right)
    {
        if (left == right)
        {
            _tree[node] = _sourceArr[left];
            return;
        }

        size_t mid       = left + (right - left) / 2;
        size_t leftNode  = node * 2;
        size_t rightNode = (node * 2) + 1;

        _Build(leftNode, left, mid);
        _Build(rightNode, mid + 1, right);

        _tree[node] = _tree[leftNode] + _tree[rightNode];
    }

    void _Update(size_t node, size_t segmentLeft, size_t segmentRight, const size_t rangeLeft,
                 const size_t rangeRight, const T value)
    {
        size_t nodeLeft  = node * 2;
        size_t nodeRight = (node * 2) + 1;

        // Apply pending updates
        if (_lazy[node] != T{})
        {
            _tree[node] += (segmentRight - segmentLeft + 1) * _lazy[node];
            if (segmentLeft != segmentRight)
            {
                _lazy[nodeLeft] += _lazy[node];
                _lazy[nodeRight] += _lazy[node];
            }
            _lazy[node] = T{};
        }

        // Skip invalid range
        if (rangeLeft > segmentRight || rangeRight < segmentLeft)
        {
            return;
        }

        // Handle full overlap
        if (rangeLeft <= segmentLeft && rangeRight >= segmentRight)
        {
            _tree[node] += (segmentRight - segmentLeft + 1) * value;
            if (segmentLeft != segmentRight)
            {
                _lazy[nodeLeft] += value;
                _lazy[nodeRight] += value;
            }
            return;
        }

        // Handle partial overlap
        size_t mid = segmentLeft + (segmentRight - segmentLeft) / 2;

        _Update(nodeLeft, segmentLeft, mid, rangeLeft, rangeRight, value);
        _Update(nodeRight, mid + 1, segmentRight, rangeLeft, rangeRight, value);

        _tree[node] = _tree[nodeLeft] + _tree[nodeRight];
    }

    T _Query(size_t node, size_t segmentLeft, size_t segmentRight, const size_t rangeLeft,
             const size_t rangeRight)
    {
        size_t nodeLeft  = node * 2;
        size_t nodeRight = (node * 2) + 1;

        // Resolve pending lazy updates
        if (_lazy[node] != T{})
        {
            _tree[node] += (segmentRight - segmentLeft + 1) * _lazy[node];
            if (segmentLeft != segmentRight)
            {
                _lazy[nodeLeft] += _lazy[node];
                _lazy[nodeRight] += _lazy[node];
            }
            _lazy[node] = T{};
        }

        // No overlap
        if (rangeLeft > segmentRight || rangeRight < segmentLeft)
        {
            return T{};
        }

        // Full overlap
        if (rangeLeft <= segmentLeft && rangeRight >= segmentRight)
        {
            return _tree[node];
        }

        // Partial overlap
        size_t mid = segmentLeft + (segmentRight - segmentLeft) / 2;

        T leftSum  = _Query(nodeLeft, segmentLeft, mid, rangeLeft, rangeRight);
        T rightSum = _Query(nodeRight, mid + 1, segmentRight, rangeLeft, rangeRight);

        return leftSum + rightSum;
    }

  public:
    SegmentTree(const vector<T> &arr)
    {
        _size = arr.size();
        _sourceArr.resize(_size);
        _tree.resize(_size * 4);
        _lazy.resize(_size * 4);

        for (size_t i = 0; i < _size; i++)
        {
            _sourceArr[i] = arr[i];
        }

        _Build(1, 0, _size - 1);
    }

    void Update(const size_t rangeLeft, const size_t rangeRight, const T value)
    {
        _Update(1, 0, _size - 1, rangeLeft, rangeRight, value);
    }

    T Query(const size_t rangeLeft, const size_t rangeRight)
    {
        return _Query(1, 0, _size - 1, rangeLeft, rangeRight);
    }
};

#pragma endregion

#pragma region BinaryHeap

template <typename T, typename Compare = less<T>> class BinaryHeap
{
  private:
    vector<T> _source;
    size_t _size = 0;

    Compare _compare;

    void _PercolateUp()
    {
        size_t index = _size;
        while (index > 1)
        {
            size_t parentIndex = index / 2;
            if (!_compare(_source[index], _source[parentIndex]))
            {
                break;
            }
            swap(_source[index], _source[parentIndex]);
            index = parentIndex;
        }
    }

    void _PercolateDown()
    {
        size_t index = 1;

        while (true)
        {
            size_t leftChildIndex  = index * 2;
            size_t rightChildIndex = index * 2 + 1;
            size_t bestIndex       = index;
            if (leftChildIndex <= _size && _compare(_source[leftChildIndex], _source[bestIndex]))
            {
                bestIndex = leftChildIndex;
            }
            if (rightChildIndex <= _size && _compare(_source[rightChildIndex], _source[bestIndex]))
            {
                bestIndex = rightChildIndex;
            }
            if (bestIndex == index)
            {
                break;
            }
            swap(_source[index], _source[bestIndex]);
            index = bestIndex;
        }
    }

  public:
    BinaryHeap()
    {
        _source = vector<T>(1);
    }

    void Insert(T value)
    {
        _size++;
        if (_size < _source.size())
        {
            _source[_size] = value;
        }
        else
        {
            _source.push_back(value);
        }
        _PercolateUp();
    }

    T Peek() const
    {
        if (_size == 0)
        {
            throw runtime_error("Invalid peek operation on empty heap");
        }
        return _source[1];
    }

    T Pop()
    {
        if (_size == 0)
        {
            throw runtime_error("Invalid pop operation on empty heap");
        }
        T topValue = _source[1];
        _source[1] = _source[_size];
        _size--;
        if (_size > 0)
        {
            _PercolateDown();
        }
        return topValue;
    }

    bool Empty() const
    {
        return _size == 0;
    }

    size_t Size() const
    {
        return _size;
    }
};

#pragma endregion
