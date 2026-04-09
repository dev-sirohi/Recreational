using System;
using System.Collections.Concurrent;

namespace CredisMini
{
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
                Expand config into Server options. DO NOT use ServerConfig as a private variable.
            */
        }

        public async Task Start()
        {
            _serverStatus = ServerStatus.INITIALIZING;
            try
            {
                _cnt.ThrowIfCancellationRequested();
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

    public static class Parser
    {
        public static class ParserRules
        {

        }

        public async static Task Parse()
        {

        }
    }

    public class DataStructures
    {
        private ConcurrentDictionary<string, Int64> _cd_str_int64 = new();
        private ConcurrentDictionary<Int64, Int64> _cd_int64_int64 = new();

        public DataStructures() { }
    }
}
