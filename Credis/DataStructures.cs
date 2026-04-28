using System.Collections.Concurrent;

public class DataStructures
{
    private static readonly DataStructures _instance = new DataStructures();
    public static DataStructures Instance => _instance;

    private readonly ConcurrentDictionary<string, string> _store = new();
    private readonly ConcurrentDictionary<string, long> _storeForIncrementLong = new();

    private DataStructures() { }

    public string Set(string key, string value)
    {
        return _store.AddOrUpdate(key, value, (key, oldValue) =>
        {
            return value;
        });
    }

    public string? Get(string key)
    {
        _store.TryGetValue(key, out string? value);
        return value;
    }

    public long Increment(string key, long value)
    {
        return _storeForIncrementLong.AddOrUpdate(key, value, (key, oldValue) =>
        {
            return oldValue + 1;
        });
    }

    public long Decrement(string key, long value)
    {
        return _storeForIncrementLong.AddOrUpdate(key, value, (key, oldValue) =>
        {
            return oldValue - 1;
        });
    }
}