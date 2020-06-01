using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using Microsoft.VisualBasic.Devices;
using System.Management;

namespace server
{
    class Program
    {
        static void sendStr(Socket handler, string disks)
        {
            byte[] disksBytes = Encoding.Unicode.GetBytes(disks);

            byte[] lengthBuffer = BitConverter.GetBytes((int)disksBytes.Length);
            handler.Send(lengthBuffer, 4, SocketFlags.None);

            handler.Send(disksBytes, disksBytes.Length, SocketFlags.None);

        }

        static void Main(string[] args)
        {

            Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, 8888);

            try
            {
                s.Bind(endPoint);
                s.Listen(32);

                while (true)
                {
                    Socket handler = s.Accept();

                    Task t = new Task(()=>{handleClient(handler);}
                    );
                    t.Start();

                    Console.WriteLine("New client connected");
                }

            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }

        static void handleClient(Socket s)
        {
            try
            {
                while (true)
                {
                    byte[] type = new byte[4];
                    s.Receive(type, type.Length, SocketFlags.None);

                    int typeInt = BitConverter.ToInt32(type, 0);

                    switch (typeInt)
                    {
                        case 1:
                            double mem = 0;
                            ManagementObjectSearcher ramMonitor = new ManagementObjectSearcher("SELECT TotalVisibleMemorySize,FreePhysicalMemory FROM Win32_OperatingSystem");
                            foreach (ManagementObject objram in ramMonitor.Get())
                            {
                                ulong totalRam = Convert.ToUInt64(objram["TotalVisibleMemorySize"]); 
                                ulong busyRam = totalRam - Convert.ToUInt64(objram["FreePhysicalMemory"]);    
                                mem = busyRam / (double)(1024* 1024);   
                            }

                            string str = Convert.ToString(mem);
                            sendStr(s, str);
                            break;
                        case 2:
                            s.Close();
                            Console.WriteLine("Client disconnected...");
                            return;
                        default:
                            continue;
                    }
                }
            }
            catch (Exception excep)
            {
                s.Close();
                Console.WriteLine("Client disconnected...");
                return;
            }
        }

    }
}
