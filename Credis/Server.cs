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
            _ = AcceptTcp();

        }
        catch (OperationCanceledException opEx)
        {
            _serverStatus = ServerStatus.CANCELLED;
            _faultMsg = opEx.Message;
        }
        catch (Exception ex)
        {
            _serverStatus = ServerStatus.FAULTED;
            _faultMsg = ex.Message;
        }
        finally
        {
            await Shutdown();
        }
    }

    public async Task Shutdown()
    {

    }

    /* Functional Methods */

    public async Task AcceptTcp()
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
