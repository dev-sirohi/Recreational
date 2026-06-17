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
        template <typename... Args>
        void Print(const std::string_view &separator, const Args &...args)
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
        template <typename T> int FindIndex(const std::vector<T> &v, const T &e)
        {
            for (int i = 0; i < v.size(); i++)
            {
                if (v.at(i) == e)
                {
                    return i;
                }
            }

            return -1;
        }
        template <typename T1, typename T2>
        int FindIndex(const std::vector<pair<T1, T2>> &v, const T1 &e)
        {
            for (int i = 0; i < v.size(); i++)
            {
                if (v.at(i).first == e)
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
        template <typename T> bool Contains(const std::vector<T> &v, const T &e)
        {
            return Helper::Vector::FindIndex(v, e) != -1;
        }
        template <typename T1, typename T2>
        bool Contains(const std::vector<pair<T1, T2>> &v, const T1 &e)
        {
            return Helper::Vector::FindIndex(v, e) != -1;
        }
    } // namespace Vector

    namespace UnorderedMap
    {
        template <typename T1, typename T2>
        bool Contains(const std::unordered_map<T1, T2> &map, const T1 &e)
        {
            return map.find(e) != map.end();
        }

        template <typename T1, typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
        void AddOrIncrement(std::unordered_map<T1, T2> &map, const T1 &e, const T2 &incr = 1)
        {
            map[e] += incr;
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
    InitFastIO("guess");
    int t = 1;
    // cin >> t;
    while (t--)
    {
        Solve();
    }
    return 0;
}

void Solve(void)
{
    ll N;
    cin >> N;

    unordered_map<string, ll> frequency;
    for (ll i = 0; i < N; i++)
    {
        string animalName;
        cin >> animalName;

        ll attributeCount;
        cin >> attributeCount;

        for (ll j = 0; j < attributeCount; j++)
        {
            string attr;
            cin >> attr;
            Helper::UnorderedMap::AddOrIncrement(frequency, attr);
        }
    }
}
