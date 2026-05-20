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
    InitFastIO(nullptr);
    int t = 1;
    // cin >> t;
    while (t--)
    {
        Solve();
    }
    return 0;
}

inline void Solve(void)
{
    ll N;
    cin >> N;

    vector<pair<char, ll>> cows(N);
    for (ll i = 0; i < N; i++)
    {
        cows[i] = pair<char, ll>();
        cin >> cows[i].first >> cows[i].second;
    }

    ll honestCows = 1;
    ll dishonestCows = 0;
    auto lyingCondition = cows[0];

    for (ll i = 0; i < N; i++)
    {
        if (cows[i].second > lyingCondition.second && cows[i].first != lyingCondition.first)
        {
            dishonestCows++;
        }
        else
        {
            honestCows++;
        }

        if (honestCows >= dishonestCows)
        {
            ll temp = honestCows;
            honestCows = dishonestCows;
            dishonestCows = temp;

            lyingCondition = 
        }
        else
        {

        }
    }
}
