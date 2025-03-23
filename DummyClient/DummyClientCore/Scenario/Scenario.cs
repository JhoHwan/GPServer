using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DummyClientCore
{
    [Serializable]
    public class Scenario
    {
        public string Name { get; set; }
        public List<IAction> Actions { get; set; }

        public void Execute(Session session)
        {
            foreach (var action in Actions)
            {
                action.Execute(session);
            }
        }
    }

    public class TestScenario : Scenario
    {
        public TestScenario()
        {
            Name = "TestScenario";
            Actions = new List<IAction>
            {
                new ConnectAction { ServerIP = "127.0.0.1", ServerPort = "7777" },
                new RepeatAction
                {
                    RepeatCount = 10,
                    Actions = new List<IAction>
                    {
                        new SendAction(),
                        new SleepAction { SleepTime = 1000 }
                    }
                },
                new SleepAction { SleepTime = 1000 },
                new DisconnectAction()
            };
        }
    }
}
