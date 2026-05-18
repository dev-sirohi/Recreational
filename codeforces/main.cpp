#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <climits>
#include <iostream>
#include <optional>
#include <queue>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define pb push_back
#define all(v) v.begin(), v.end()
#define spc " "
#define newl "\n"

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

inline void Solve(void);

int main(void)
{
    InitFastIO("pails");
    int t = 1;
    // cin >> t;
    while (t--)
    {
        Solve();
    }
    return 0;
}

vector<ll> cache;

inline ll Recursion(const ll &N, const ll &K, const vector<ll> &diamonds, ll curr)
{
    if (curr == N)
    {
        return 0;
    }


}

inline void Solve(void)
{
    ll N, K;
    cin >> N >> K;

    vector<ll> diamonds(N);
    for (ll i = 0; i < N; i++)
    {
        cin >> diamonds[i];
    }


}
