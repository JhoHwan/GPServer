using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Flatbuffer;
using Google.FlatBuffers;

namespace DummyClientCore
{
    internal static class Program
    {
        const int ThreadCount = 4;      

        [STAThread]
        static void Main()
        {
            FlatBufferBuilder builder = new FlatBufferBuilder(128);

            Offset<S_Test> pakcet = S_Test.CreateS_Test(builder, 12);

            var sendbuffer = PacketUtil.MakeSendBuffer(builder, PacketContent.S_Test, pakcet);

            Packet recv;

            try
            {
                recv = PacketUtil.MakePacket(sendbuffer);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return;
            }

            Console.WriteLine(recv.ContentAsS_Test().Id);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            MainForm form = new MainForm();
            CleintService manager = new CleintService(ThreadCount);
            MainController controller = new MainController(form, manager);

            Application.Run(form);
        }

    }
}
