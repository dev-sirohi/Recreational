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

#pragma region Helpers

namespace Helper
{
    namespace IO
    {
        template <typename... Args> void Print(const std::string_view &separator, const Args&... args)
        {
            (std::cout << ... << args) << separator;
        }

        template <typename... Args> void PrintLine(const Args &...args)
        {
            (std::cout << ... << args) << '\n';
        }
    } // namespace IO

    namespace Math
    {
        template <typename T> void UpdateMax(T &max_val, const T &contender)
        {
            max_val = std::max(max_val, contender);
        }
    } // namespace Math

    namespace Vector
    {
        template <typename T> void Print(const std::vector<T> &v, char separator)
        {
            for (size_t i = 0; i < v.size(); i++)
            {
                cout << v.at(i) << separator;
            }
        }
        template <typename T> size_t FindIndex(const std::vector<T> &v, const T &e)
        {
            for (size_t i = 0; i < v.size(); i++)
            {
                if (v.at(i) == e)
                {
                    return i;
                }
            }

            return -1;
        }
        template <typename T> T First(const std::vector<T> &v)
        {
            if (v.size() == 0)
            {
                throw runtime_error("Attempting to access first value of empty vector");
            }
            return v.at(0);
        }
        template <typename T> T FirstOrDefault(const std::vector<T> &v)
        {
            if (v.size() == 0)
            {
                return T{};
            }
            return v.at(0);
        }
        template <typename T> T Last(const std::vector<T> &v)
        {
            if (v.size() == 0)
            {
                throw runtime_error("Attempting to access last value of empty vector");
            }
            return v.at(v.size() - 1);
        }
        template <typename T> T LastOrDefault(const std::vector<T> &v)
        {
            if (v.size() == 0)
            {
                return T{};
            }
            return v.at(v.size() - 1);
        }
    } // namespace Vector

    namespace UnorderedMap
    {
        template <typename T1, typename T2>
        bool Contains(const std::unordered_map<T1, T2> &map, const T1 &e)
        {
            return map.find(e) != map.end();
        }
    } // namespace UnorderedMap

    namespace UnorderedSet
    {
        template <typename T> bool Contains(const std::unordered_set<T> &set, const T &e)
        {
            return set.find(e) != set.end();
        }
    } // namespace UnorderedSet

} // namespace Helper

#pragma endregion

void Solve(void);

int main(void)
{
    InitFastIO("lifeguards");
    int t = 1;
    // cin >> t;
    while (t--)
    {
        Solve();
    }
    return 0;
}

typedef struct
{
    ll Start;
    ll End;
} Shift;

void Solve(void)
{
    ll N;
    cin >> N;

    vector<Shift> lifeguards(N);
    for (ll i = 0; i < N; i++)
    {
        Shift s;
        cin >> s.Start;
        cin >> s.End;
        lifeguards[i] = s;
    }

    sort(lifeguards.begin(), lifeguards.end(),
         [](const Shift &a, const Shift &b)
         {
             return a.Start < b.Start;
         });

    vector<ll> totalTimeCoveredAtEachPoint(N);
    totalTimeCoveredAtEachPoint[0] = Helper::Vector::First(lifeguards).End;
    for (ll i = 1; i < N; i++)
    {
        totalTimeCoveredAtEachPoint[i] = lifeguards.at(i).End;
        if (lifeguards.at(i).Start > lifeguards.at(i - 1).End)
        {
            totalTimeCoveredAtEachPoint[i] -= lifeguards.at(i).Start - lifeguards.at(i - 1).End;
        }
    }

    ll maxTimeCovered =
        Helper::Vector::Last(totalTimeCoveredAtEachPoint) - Helper::Vector::First(lifeguards).End;

    for (ll i = 1; i < N; i++)
    {
        Helper::Math::UpdateMax(maxTimeCovered, Helper::Vector::Last(totalTimeCoveredAtEachPoint) -
                                                    totalTimeCoveredAtEachPoint.at(i) +
                                                    totalTimeCoveredAtEachPoint.at(i - 1));
    }

    Helper::IO::PrintLine(maxTimeCovered);
}
