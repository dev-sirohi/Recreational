namespace Credis;

public class Program
{
    public static async Task Main(string[] args)
    {
        Server? server = null;
        try
        {
            Console.WriteLine("===Credis Mini Server===");
            Console.Write("Initializing");
            server = new Server(new Server.ServerConfig
            {

            });
            var startTask = server.Start().GetAwaiter();
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
            server?.Shutdown();
        }
    }
}
