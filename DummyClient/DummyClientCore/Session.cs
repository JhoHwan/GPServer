using DummyClientWrapper;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace DummyClientCore
{
    public class Session : ManagedDummySession
    {
        private readonly CleintService _service;

        private bool _isExecute = false;

        public Session(CleintService service) : base() 
        {
            _service = service;
        }

        public void Connect(string ip, string port)
        {
            CreateSocket();

            _service.RegisterIOCP(this);

            _service.Connector.Connect(ip, ushort.Parse(port), this);
        }

        public void Execute(Scenario scenario)
        {
            _isExecute = true;

            scenario.Execute(this);
        }

        public void Stop()
        {
            if (_isExecute)
            {
                _isExecute = false;
            }
        }

        public override void OnConnected()
        {
            Console.WriteLine($"Session {GetSocket()} Connected");
        }

        public override void OnDisConnected()
        {
            Console.WriteLine($"Session {GetSocket()} Disconnected");
        }

        public override void OnRecv(uint sentBytes)
        {

        }
        public override void OnSend(uint sentBytes)
        {
            Console.WriteLine($"Send {sentBytes}");
        }
    }
}
