using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DummyClientCore
{
    public class MainController
    {
        private readonly MainForm _form;
        private readonly CleintService _service;

        public MainController(MainForm form, CleintService service) 
        { 
            _form = form;
            _service = service;

            // 이벤트 핸들러 등록
            _form.AddScenarioClicked += OnAddScenarioClicked;
            _form.RemoveScenarioClicked += OnRemoveScenarioClicked;
            _form.RunTestClicked += OnRunTestClicked;;

            LoadScenarios();
        }

        private void LoadScenarios()
        {
            //var scenarios = _model.LoadScenarios();
            List<string> scenarios = new List<string>();

            // Test Case
            scenarios.Add("Test Scenario 1");
            scenarios.Add("Test Scenario 2");
            scenarios.Add("Test Scenario 3");

            _form.UpdateScenarioList(scenarios);
        }

        private void OnAddScenarioClicked(object sender, EventArgs e)
        {
            var scenarioName = _form.GetSelectedScenarioName();
            var sessionCount = _form.GetSessionCount();

            if (string.IsNullOrEmpty(scenarioName))
            {
                _form.ShowMessage("Please select a scenario.");
                return;
            }

            _service.AddScenario(scenarioName, sessionCount);
            _form.AddScenarioToListView(scenarioName, sessionCount);
        }

        private async void OnRunTestClicked(object sender, EventArgs e)
        {
            if(_service.ScenariosCount == 0)
            {
                _form.ShowMessage("No registered scenarios.");
                return;
            }

            var tasks = _service.StartTest();

            await Task.WhenAll(tasks);

            _form.ShowMessage("Finish All Tasks");

            _service.DisconnectAll();
        }

        private void OnRemoveScenarioClicked(object sender, EventArgs e)
        {
            var scenarioName = _form.GetSelectedScenarioFromListView();

            if (string.IsNullOrEmpty(scenarioName))
            {
                _form.ShowMessage("Please select a scenario.");
                return;
            }

            _service.RemoveScenario(scenarioName);
            _form.RemoveScenarioFromListView(scenarioName);
        }
    }
}
