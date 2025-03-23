using Flatbuffer;
using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DummyClientCore
{
    public interface IAction
    {
        void Execute(Session session);
    }

    public class ConnectAction : IAction
    {
        public string ServerIP { get; set; }
        public string ServerPort { get; set; }

        public void Execute(Session session)
        {
            session.Connect(ServerIP, ServerPort);
        }
    }

    public class DisconnectAction : IAction
    {
        public void Execute(Session session)
        {
            session.Disconnect();
        }
    }

    public class SendAction : IAction
    {
        public void Execute(Session session)
        {
            FlatBufferBuilder builder = new FlatBufferBuilder(128);
            var offset = S_Test.CreateS_Test(builder, 12);
            session.Send(PacketUtil.MakeSendBuffer(builder, PacketContent.S_Test, offset));
        }
    }

    public class SleepAction : IAction
    {
        public int SleepTime { get; set; }
        public void Execute(Session session)
        {
            System.Threading.Thread.Sleep(SleepTime);
        }
    }

    public class RepeatAction : IAction
    {
        public int RepeatCount { get; set; }
        public List<IAction> Actions { get; set; }

        public void Execute(Session session)
        {
            for (int i = 0; i < RepeatCount; i++)
            {
                foreach (var action in Actions)
                {
                    action.Execute(session);
                }
            }
        }
    }

}
