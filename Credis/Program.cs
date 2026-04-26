namespace Credis;

public class Program
{
    public static async Task Main(string[] args)
    {
        Server? server = null;
        CancellationTokenSource _cntSource = new CancellationTokenSource();
        CancellationToken _cnt = _cntSource.Token;
        try
        {
            Console.WriteLine("===Credis Mini Server===");
            server = new Server(new Server.ServerConfig
            {

            });
            var startTask = server.StartAsync().GetAwaiter();
            Console.WriteLine("Listening");
            while (!startTask.IsCompleted)
            {
                Console.Write(".");
                await Task.Delay(1000);
            }
            if (server.GetStatus() == Server.ServerStatus.FAULTED)
            {
                throw new Exception(server.GetFaultMessage());
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine();
            Console.WriteLine($"Server initialization failed::{ex.Message}");
        }
        finally
        {
            _cntSource.Cancel();
            _cntSource.Dispose();
        }
    }
}
