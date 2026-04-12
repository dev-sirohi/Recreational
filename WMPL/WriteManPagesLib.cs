using System;
using System.Text;

namespace WMPL;

public class Program
{
    public static void Main(string[] args)
    {

    }
}

public sealed class Parser
{
    public class WMPLConfig
    {
        public int WindowCutoffFactor { get; set; } = 3;
    }

    public const string NEWLINE = "\n";

    private readonly bool _isInitialized = false;
    private readonly int _windowCutoffFactor = -1;
    private readonly int _windowWidth = -1;

    private Parser(WMPLConfig config)
    {
        if (_isInitialized)
        {
            throw new Exception("This library can only be initialized once");
        }
        _isInitialized = true;
        _windowCutoffFactor = Math.Max(1, Math.Min(10, config.WindowCutoffFactor));
        _windowWidth = (int)Math.Round((double)(Console.WindowWidth / _windowCutoffFactor));
    }

    public static Parser InitializeWMPL(WMPLConfig config)
    {
        return new Parser(config);
    }

    public string WriteEqualSpaced(List<List<string>> grid)
    {
        var sb = new StringBuilder();
        var rowListsToProcess = new List<List<string>>();
        foreach (var rowList in grid)
        {
            if (rowList.Count == 0)
            {
                sb.Append(ProcessRowLists(rowListsToProcess));
                sb.Append("\n");
                rowListsToProcess = new List<List<string>>();
                continue;
            }
            rowListsToProcess.Add(rowList);
        }
        sb.Append(ProcessRowLists(rowListsToProcess));
        return sb.ToString();
    }

    private string ProcessRowLists(List<List<string>> rowListsToProcess)
    {
        int columnsCount = 0;
        int maxLineLength = 0;
        foreach (var rowList in rowListsToProcess)
        {
            columnsCount = Math.Max(columnsCount, rowList.Count);
            maxLineLength = Math.Max(maxLineLength, rowList.Max(r => r.Length));
        }

        /*
            todo: calculate cellWidth for each COLUMN, not the entire sub-grid.
        */

        int cellWidth = Math.Min((int)Math.Round((double)(_windowWidth / columnsCount)), maxLineLength + 2);
        var sb = new StringBuilder();
        for (int rowInd = 0; rowInd < rowListsToProcess.Count; rowInd++)
        {
            var rowList = rowListsToProcess[rowInd].Select(x => x).ToList();
            for (int sentenceInd = 0; sentenceInd < rowList.Count; sentenceInd++)
            {
                string sentence = new StringBuilder(rowList[sentenceInd]).ToString();
                if (!string.Equals(sentence, "\t"))
                {
                    if (sentence.Length > cellWidth)
                    {
                        int acceptableLength = cellWidth - 1;
                        string subSentence1 = sentence.Substring(0, acceptableLength) + "-";
                        string subSentence2 = "-" + sentence.Substring(acceptableLength, (sentence.Length - acceptableLength));
                        sentence = subSentence1;
                        var newRowList = new List<string>();
                        for (int _i = 0; _i < rowList.Count; _i++)
                        {
                            newRowList.Add("");
                        }
                        newRowList[sentenceInd] = subSentence2;
                        if (rowInd < rowListsToProcess.Count - 1)
                        {
                            rowListsToProcess.Insert(rowInd + 1, newRowList);
                        }
                        else
                        {
                            rowListsToProcess.Add(newRowList);
                        }
                    }
                    else
                    {
                        int paddingRequired = cellWidth - sentence.Length;
                        sentence += new string(' ', paddingRequired);
                    }
                }
                sb.Append(sentence);
            }
            sb.Append("\n");
        }
        return sb.ToString();
    }
}
