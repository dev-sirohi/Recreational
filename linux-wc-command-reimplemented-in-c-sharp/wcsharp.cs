/*
    * This project was created to simulate the linux wc command which is used to extract information about file(s).
    * I am making this as part of the Coding Challenge website: https://codingchallenges.fyi/challenges/challenge-wc

    todo > Print bytes in a file (-c)
*/
namespace wcsharp;

internal sealed class GlobalSettings
{
    private string _majorVersion = "1";
    private string _minorVersion = "2";

    private GlobalSettings()
    {
        if (_isInitialized)
        {
            throw new InvalidOperationException("Cannot re-initialize Global Settings.");
        }
        _isInitialized = true;
    }

    private bool _isInitialized = false;
    public static GlobalSettings InitializeGlobalSettings()
    {
        return new GlobalSettings();
    }

    public string GetAppVersion()
    {
        return string.Join(".", _majorVersion, _minorVersion);
    }
}

internal sealed class Program
{
    public static async Task Main(string[] args)
    {
        var app = new App();
        if (args.Count() == 0)
        {
            app.PrintHelpText();
            return;
        }
        await app.Execute(args);
    }
}

internal class App
{
    private readonly GlobalSettings _global;
    private readonly WMPL.Parser _wmpl;

    public App()
    {
        _global = GlobalSettings.InitializeGlobalSettings();
        _wmpl = WMPL.Parser.InitializeWMPL(new WMPL.Parser.WMPLConfig
        {
            WindowCutoffFactor = 3,
        });
    }

    public void PrintHelpText()
    {
        var helpText = new List<List<string>>
        {
            new List<string> { "Name:", "wcsharp" },
            new List<string> { "Description:", "C# clone of the Linux command line tool <wc>" },
            new List<string> { "Version:", $"{_global.GetAppVersion()}" },
            new List<string> { },
            new List<string> { "Commands:-" },
            new List<string> { "\t", "-h|--help", "Help" },
            new List<string> { "\t", "-c", "Get bytes" },
        };
        Console.Write(_wmpl.WriteEqualSpaced(helpText));
    }

    public async Task Execute(string[] args)
    {
        for (int argInd = 0; argInd < args.Length; argInd++)
        {
            var arg = args[argInd];
            if (string.IsNullOrWhiteSpace(arg))
            {
                continue;
            }
            switch (arg)
            {
                case "-h":
                case "--help":
                    _help();
                    break;
                case "-c":
                    if (argInd == args.Length - 1)
                    {
                        throw new Exception("Invalid set of commands. -c requires filename.");
                    }
                    var nextArg = args[argInd + 1];
                    await _getBytes();
                    break;
            }
        }
    }

    private void _help()
    {
        PrintHelpText();
    }

    private async Task _getBytes()
    {

    }
}

internal class FileService
{
    public FileService()
    {

    }

    public bool ValidateFile()
    {
        return true;
    }

    public async Task<bool> OpenFile()
    {
        return true;
    }
}
