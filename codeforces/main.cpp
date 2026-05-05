#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void init_fast_io(void);

template <typename T> class BinaryNode
{
    T value;
    BinaryNode *left;
    BinaryNode *right;
};
template <typename T> class TreeNode
{
    T value;
    vector<TreeNode *> children;
};
template <typename T> class ListNode
{
    T value;
    ListNode *next;
    ListNode *prev;
};
template <typename T> class SegmentTree
{
  private:
    vector<T> _source;
    vector<T> _input;

    void init_build()
    {
        
    }
  public:
    SegmentTree(vector<T> &input)
    {
        _input = input;
        _source = vector<T>(4 * input.size());
        init_build();
    }

    SegmentTree(T[] &input)
    {
        _input  = vector<T>(input);
        _source = vector<T>(4 * input.size());
        init_build();
    }
};

void solve(void)
{
    int recipes, min_count_for_recom, questions;
    cin >> recipes >> min_count_for_recom >> questions;

    unordered_map<int, int> umap;
    for (int i = 0; i < recipes; i++)
    {
        int low, high;
        cin >> low;
        cin >> high;
        for (int i = low; i <= high; i++)
        {
            if (umap.contains(i))
            {
                umap[i]++;
            }
            else
            {
                umap[i] = 1;
            }
        }
    }

    for (int i = 0; i < questions; i++)
    {
        int low, high;
        cin >> low;
        cin >> high;
        int main_count = 0;
        for (int j = low; j <= high; j++)
        {
            if (umap.contains(j) && umap[j] >= min_count_for_recom)
            {
                main_count++;
            }
        }
        cout << main_count << "\n";
    }
}

int main(void)
{
    init_fast_io();
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

void init_fast_io(void)
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
