using DummyClientWrapper;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace DummyClientCore
{
    public class CleintService
    {
        // Thread
        private readonly int _threadCount;
        private readonly List<Thread> _threadPool;
        private bool _isRun;

        // IOCP
        private readonly ManagedIOCPCore _iocpCore;
        private readonly ManagedConnector _connector;
        public ManagedConnector Connector { get => _connector; }

        // Scenario
        private readonly Dictionary<string, int> _scenarios;
        public int ScenariosCount => _scenarios.Count;

        // Session
        private readonly List<Session> _sessions; 

        public CleintService(int threadCount)
        {
            _threadCount = threadCount;
            _threadPool = new List<Thread>();

            _iocpCore = new ManagedIOCPCore();
            _connector = new ManagedConnector();

            _scenarios = new Dictionary<string, int>();

            _sessions = new List<Session>();
        }

        /// <summary>
        /// 테스트 리스트에 사용할 시나리오 종류와 세션 개수를 추가한다.
        /// </summary>
        /// <param name="scenarioName">사용할 이름</param>
        /// <param name="sessionCount">세션 개수</param>
        public void AddScenario(string scenarioName, int sessionCount)
        {
            if (_scenarios.ContainsKey(scenarioName))
            {
                _scenarios[scenarioName] += sessionCount;
                return;
            }

            _scenarios.Add(scenarioName, sessionCount);
        }

        /// <summary>
        /// 테스트 리스트에서 시나리오를 삭제한다.
        /// </summary>
        /// <param name="scenarioName">삭제할 시나리오 이름</param>
        /// <exception cref="KeyNotFoundException"></exception>
        public void RemoveScenario(string scenarioName)
        {
            if (!_scenarios.ContainsKey(scenarioName))
                throw new KeyNotFoundException($"Scenario '{scenarioName}' not found.");

            _scenarios.Remove(scenarioName);
        }

        /// <summary>
        /// 시나리오 테스트를 시작한다.
        /// </summary>
        public List<Task> StartTest()
        {
            _isRun = true;

            for (int i = 0; i < _threadCount; i++)
            {
                Thread thread = new Thread(new ThreadStart(Dispatch));
                thread.IsBackground = true;
                _threadPool.Add(thread);

                thread.Start();
                Console.WriteLine($"Thread {i} Start!");
            }

            foreach (var data in _scenarios)
            {
                for (int i = 0; i < data.Value; i++)
                {
                    Session session = CreateSession();

                    _sessions.Add(session);
                    //session.SetScenario(data.Key);
                }
            }

            List<Task> tasks = new List<Task>();

            foreach (var session in _sessions)
            {
                Task task = new Task(() =>
                {
                    session.Execute(scenario: new TestScenario());
                });
                tasks.Add(task);
            }

            tasks.ForEach(task => task.Start());

            return tasks;
        }

        private Session CreateSession()
        {
            Session session = new Session(this);

            return session;
        }

        public void DisconnectAll()
        {
            _isRun = false;
            _threadPool.ForEach(thread => thread.Join());
            _threadPool.Clear();

            foreach (ManagedDummySession session in _sessions)
            {
                session.Disconnect();
                session.Dispose();
            }

            _sessions.Clear();
        }

        private void Dispatch()
        {
            while (_isRun)
            {
                _iocpCore.Dispatch(100);
            }

            Console.WriteLine("Thread End!");
        }

        public void RegisterIOCP(ManagedDummySession session)
        {
            _iocpCore.RegisterSocket(session.GetSocket());
        }

    }
}
