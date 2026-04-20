using System.Collections.Concurrent;

namespace Credis;

public class DataStructures
{
    private ConcurrentDictionary<string, Int64> _cd_str_int64 = new();
    private ConcurrentDictionary<Int64, Int64> _cd_int64_int64 = new();

    public DataStructures() { }
}
