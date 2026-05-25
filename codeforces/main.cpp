#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define pb push_back
#define all(v) v.begin(), v.end()
#define newl "\n"
#define spc " "
#define c_spc ' '

typedef long long ll;

#pragma region FastIO

void InitFastIO(const char *filename = nullptr)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    FILE *outval;

#ifdef LOCAL
    outval = freopen("input.in", "r", stdin);
    if (outval == nullptr)
    {
        throw runtime_error("input.in does not exist");
    }

    outval = freopen("output.out", "w", stdout);
    if (outval == nullptr)
    {
        throw runtime_error("output.out could not be opened");
    }
#else
    if (filename != nullptr)
    {
        string inputFile  = string(filename) + ".in";
        string outputFile = string(filename) + ".out";

        outval = freopen(inputFile.c_str(), "r", stdin);
        if (outval == nullptr)
        {
            throw runtime_error(inputFile + " does not exist");
        }

        outval = freopen(outputFile.c_str(), "w", stdout);
        if (outval == nullptr)
        {
            throw runtime_error(outputFile + " could not be opened");
        }
    }
#endif
}

#pragma endregion

namespace Helper
{
namespace Vector
{
template <typename T> void Print(const vector<T> &v, char separator)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << separator;
    }
}
template <typename T> size_t FindIndex(const vector<T> &v, const T &e)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v.at(i) == e)
        {
            return i;
        }
    }

    return 0;
}
} // namespace Vector
namespace UnorderedMap
{
template <typename T1, typename T2> bool Contains(const unordered_map<T1, T2> &map, const T1 &e)
{
    return map.find(e) != map.end();
}
} // namespace UnorderedMap
namespace UnorderedSet
{
template <typename T> bool Contains(const unordered_set<T> &set, const T &e)
{
    return set.find(e) != set.end();
}
} // namespace UnorderedSet
} // namespace Helper

void Solve(void);

int main(void)
{
    InitFastIO("cownomics");
    int t = 1;
    // cin >> t;
    while (t--)
    {
        Solve();
    }
    return 0;
}

vector<char> ALPHA{'A', 'C', 'G', 'T'};

inline void Solve(void)
{
    ll N, M;
    cin >> N >> M;

    unordered_set<char> spottySeq;
    for (ll i = 0; i < N; i++)
    {
        char c;
        cin >> c;
        spottySeq.insert(c);
    }
    vector<string> plainCows(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> plainCows[i];
    }

    ll finalCount = 0;
    for (ll i = 0; i < M; i++)
    {
        int alphaCount = 0;
        for (char alpha : ALPHA)
        {
            if (Helper::UnorderedSet::Contains(spottySeq, alpha))
            {
                alphaCount++;
            }
        }

        if (alphaCount == ALPHA.size())
        {
            continue;
        }

        ll uniques = 0;
        for (ll j = 0; j < N; j++)
        {
            if (!Helper::UnorderedSet::Contains(spottySeq, plainCows[j][i])) {
                uniques++;
            }
        }
        if (uniques == N) {
            finalCount++;
        }
    }

    cout << finalCount << newl;
}
