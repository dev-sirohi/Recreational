namespace Credis;

public class Server
{
    public enum ServerStatus
    {
        INITIALIZING,
        ACTIVE,
        SHUTTING_DOWN,
        FAULTED,
        CANCELLED,
    }

    public class ServerConfig
    {

    }

    /*
        1. Server accepts HTTP connections.
        2. Once connection is established, it is upgraded to a websocket.
        3. For each connections, it checks the amount of memory remaining for use, and if allowed, it initializes
            a new DataStructure instance for it.
    */

    private ServerStatus _serverStatus;
    private string _faultMsg = string.Empty;
    private CancellationToken _cnt;

    public Server(ServerConfig config)
    {
        /*
            Expand config into Server options. DO NOT use ServerConfig as a local variable.
        */
    }

    public async Task Start()
    {
        _serverStatus = ServerStatus.INITIALIZING;
        try
        {
            _cnt.ThrowIfCancellationRequested();
            await Task.Delay(10000);
        }
        catch (OperationCanceledException opEx)
        {
            _serverStatus = ServerStatus.CANCELLED;
            _faultMsg = "Operation cancelled by user";
        }
        catch (Exception ex)
        {
            _serverStatus = ServerStatus.FAULTED;
            _faultMsg = ex.Message;
        }
    }

    public async Task Shutdown()
    {

    }

    /* Functional Methods */

    public async Task AcceptTcp()
    {

    }

    private async Task UpgradeToWebSocket()
    {

    }

    private async Task CloseWebSocket()
    {

    }

    public async Task CloseTcp()
    {

    }

    /* Helper methods */

    public ServerStatus GetStatus()
    {
        return _serverStatus;
    }

    public string GetFaultMessage()
    {
        return _faultMsg;
    }
}
