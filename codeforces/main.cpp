#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#define push_back pb

typedef long long ll;

void InitFastIO(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    FILE *outval;
    outval = freopen("input.in", "r", stdin);
    if (outval == nullptr)
    {
        throw runtime_error("Filename does not exist");
    }
    outval = freopen("output.out", "w", stdout);
    if (outval == nullptr)
    {
        throw runtime_error("Filename does not exist");
    }
#endif
}

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

        void _Update(size_t node, size_t segmentLeft, size_t segmentRight, const size_t rangeLeft, const size_t rangeRight, const T value)
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

        T _Query(size_t node, size_t segmentLeft, size_t segmentRight, const size_t rangeLeft, const size_t rangeRight)
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

            T leftSum = _Query(nodeLeft, segmentLeft, mid, rangeLeft, rangeRight);
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
                _sourceArr[i]    = arr[i];
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

void Solve(void);

int main(void)
{
    InitFastIO();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        Solve();
    }
    return 0;
}

const int MAXN = 200000 + 5;
const vector<ll> temps(MAXN, 0);

void Solve()
{
    SegmentTree<ll> sgtree(temps);

    size_t recipes, k, q;
    cin >> recipes >> k >> q;

    for (size_t i = 0; i < recipes; i++)
    {
        size_t l, r;
        cin >> l >> r;
        sgtree.Update(l, r, 1);
    }

    vector<ll> good(MAXN, 0);

    for (size_t i = 1; i < MAXN; i++)
    {
        if (sgtree.Query(i, i) >= k)
            good[i] = 1;
    }

    for (size_t i = 1; i < MAXN; i++)
        good[i] += good[i - 1];

    for (size_t i = 0; i < q; i++)
    {
        size_t l, r;
        cin >> l >> r;
        cout << good[r] - good[l - 1] << "\n";
    }
}
