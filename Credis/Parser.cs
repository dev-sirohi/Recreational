using System.Buffers.Binary;
using System.Diagnostics;
using System.Net.Sockets;
using System.Text;

namespace Credis;

public class Parser
{
    public static class ParseRules
    {
        public enum CommandType
        {
            NONE,
            INVALID,
            SET,
            GET,
            INCREMENT,
            DECREMENT,
        }

        /*
            Payload format:
                [PayloadLength]
                    38\n
                [Payload]
                    cmd=set\n
                    key=1\n
                    value=alice\n
        */

        public static CommandType GetCommandType(string cmd = "")
        {
            switch (cmd.ToLower())
            {
                case "set":
                    return CommandType.SET;
                case "get":
                    return CommandType.SET;
                case "increment":
                    return CommandType.INCREMENT;
                case "decrement":
                    return CommandType.DECREMENT;
                default:
                    return CommandType.INVALID;
            }
        }
    }

    /*
        The reason I have chosen 2 << 12 (~8000) as MAX_BUFFER_SIZE is because an in-memory database is supposed to be FAST.
        It is not a file-system database that requires storing large amounts of data.
        If anybody using an in-memory database requires more than ~8000 characters of data to be cached, they need to reconsider their project requirements.
        But since I am no "Chris Sawyer", I accept this might be a mistake.
        Regardless, for now I will keep it as a hard-limit and maybe later add it as a configurable option.
    */

    private const int MAX_BUFFER_SIZE = 2 << 12;

    private int _edgePtr = 0;
    private int _ptr = 0;
    private int _expectedLength = 0;
    private byte[] _inputBuffer = new byte[0];
    private byte[] _outputBuffer = new byte[0];
    private bool _processingPreviousCommand = false;

    private ParseRules.CommandType _currentCommand = ParseRules.CommandType.NONE;

    private NetworkStream _stream;
    private Stopwatch _parserStopwatch;
    private CancellationToken _cnt;

    private DataStructures ds = DataStructures.Instance;

    public Parser(NetworkStream stream, CancellationToken cnt)
    {
        _cnt = cnt;
        _stream = stream;

        _inputBuffer = new byte[MAX_BUFFER_SIZE];
        _outputBuffer = new byte[MAX_BUFFER_SIZE];

        _parserStopwatch = new Stopwatch();
    }

    public async Task ParseAsync()
    {
        try
        {
            bool closeConnection = false;
            while (!closeConnection)
            {
                _cnt.ThrowIfCancellationRequested();

                int bytesRead = 0;
                if (_edgePtr < MAX_BUFFER_SIZE)
                {
                    bytesRead = await _stream.ReadAsync(_inputBuffer, _edgePtr, MAX_BUFFER_SIZE - _edgePtr, _cnt);
                    if (bytesRead == 0)
                    {
                        if (IsEOF(_ptr, _inputBuffer))
                        {
                            closeConnection = true;
                        }
                    }
                    _edgePtr += bytesRead;
                }

                if (_processingPreviousCommand)
                {
                    await ProcessCommandAsync();
                }
                else
                {
                    await ProcessNewCommandAsync();
                }

                if (!_processingPreviousCommand)
                {
                    _parserStopwatch.Stop();
                    long elapsedTime = _parserStopwatch.ElapsedMilliseconds;
                    string elapsedTimeStr = "Time Spent processing: " + elapsedTime.ToString();
                    WriteLine(ref elapsedTimeStr);
                    await _stream.WriteAsync(_outputBuffer, 0, GetBufferedContentLength(_outputBuffer), _cnt);
                    ClearBufferedContent(_outputBuffer, 0, GetBufferedContentLength(_outputBuffer));
                }
            }
        }
        catch (Exception ex)
        {

        }
    }

    private async Task ProcessNewCommandAsync()
    {
        _parserStopwatch.Start();
        if (_edgePtr < 4)
        {
            // Not enough data
            return;
        }
        _expectedLength = BinaryPrimitives.ReadInt32BigEndian(_inputBuffer.AsSpan(_ptr, 4));
        _ptr += 4;
        SkipEOL();
        _processingPreviousCommand = true;
        await ProcessCommandAsync();
    }

    private async Task ProcessCommandAsync()
    {
        if (_edgePtr < 4 + _expectedLength)
        {
            return;
        }
        if (_currentCommand == ParseRules.CommandType.NONE)
        {
            var cmdLineSb = new StringBuilder();
            if (!GetLine(cmdLineSb))
            {
                cmdLineSb.Clear();
                return;
            }
            string cmd = cmdLineSb.ToString(4, cmdLineSb.Length - 4);
            _currentCommand = ParseRules.GetCommandType(cmd);
        }
        if (_currentCommand == ParseRules.CommandType.INVALID)
        {
            throw new Exception("Unsupported command type");
        }
        switch (_currentCommand)
        {
            case ParseRules.CommandType.SET:
                await ProcessSetCommandAsync();
                break;
            case ParseRules.CommandType.GET:
                await ProcessGetCommandAsync();
                break;
        }
    }

    private async Task ProcessSetCommandAsync()
    {
        var keySb = new StringBuilder();
        var valueSb = new StringBuilder();
        if (!GetLine(keySb) || !GetLine(valueSb))
        {
            keySb.Clear();
            valueSb.Clear();
            return;
        }

        _processingPreviousCommand = false;

        string key = keySb.ToString();
        string value = valueSb.ToString();

        string setValue = ds.Set(key, value);
        WriteLine(ref setValue);
    }

    private async Task ProcessGetCommandAsync()
    {
        var keySb = new StringBuilder();
        if (!GetLine(keySb))
        {
            keySb.Clear();
            return;
        }

        _processingPreviousCommand = false;

        string key = keySb.ToString();

        string value = ds.Get(key) ?? "NULL";
        WriteLine(ref value);
    }

    private bool GetLine(StringBuilder line)
    {
        int _ptrTemp = _ptr;
        while (!IsEOF(_ptrTemp, _inputBuffer) && !IsEOL(_ptrTemp, _inputBuffer))
        {
            line.Append((char)_inputBuffer[_ptrTemp]);
            _ptrTemp++;
        }
        if (!IsEOF(_ptrTemp, _inputBuffer) && !IsEOL(_ptrTemp, _inputBuffer))
        {
            return false;
        }
        _ptr = _ptrTemp;
        SkipEOL();
        return true;
    }

    private void SkipEOL()
    {
        if (_inputBuffer[_ptr] == '\n')
        {
            _ptr++;
        }
    }

    private bool IsEOL(int _ptrTemp, byte[] buffer)
    {
        return buffer[_ptrTemp] == '\n';
    }

    public bool IsEOF(int _ptrTemp, byte[] buffer)
    {
        return buffer[_ptrTemp] == '\0' || _ptrTemp > _edgePtr;
    }

    public int GetBufferedContentLength(byte[] buffer)
    {
        int count = 0;
        int ptr = 0;
        while (!IsEOL(ptr, buffer) && !IsEOF(ptr, buffer))
        {
            count++;
            ptr++;
        }
        return count;
    }

    public void WriteLine(ref string outputLine)
    {
        int _outPtr = 0;
        foreach (char c in outputLine)
        {
            _outputBuffer[_outPtr] = (byte)c;
            _outPtr++;
        }
        _outputBuffer[_outPtr] = (byte)'\n';
    }

    private void ClearBufferedContent(byte[] buffer, int offset, int length)
    {
        for (int ptr = offset; ptr < length; ptr++)
        {
            buffer[ptr] = (byte)'\0';
        }
    }
}
