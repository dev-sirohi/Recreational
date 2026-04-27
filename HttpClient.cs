using System.Net.Sockets;
using System.Text;
using System.Buffers.Binary;

namespace HttpClient;

public class Client
{
    public const string LOCALHOST = "127.0.0.1";
    public const int PORT = 5050;

    public static async Task Main(string[] args)
    {
        using var client = new TcpClient(LOCALHOST, PORT);
        using var stream = client.GetStream();

        int i = 10;
        while (i-- > 0)
        {
            var payloadStr =
                "get\n" +
                "1\n";

            var payloadBytes = Encoding.UTF8.GetBytes(payloadStr);

            byte[] lenBytes = new byte[4];
            BinaryPrimitives.WriteInt32BigEndian(lenBytes, payloadBytes.Length);

            await stream.WriteAsync(lenBytes);
            await stream.WriteAsync(payloadBytes);
            Console.WriteLine("Sent");

            byte[] buffer = new byte[2 << 12];
            int bytesRead = await stream.ReadAsync(buffer);

            if (bytesRead > 0)
            {
                var response = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                Console.WriteLine("Response: " + response);
            }
        }
    }
}
