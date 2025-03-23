using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace DummyClientCore
{
    public partial class MainForm : Form
    {
        public event EventHandler AddScenarioClicked;
        public event EventHandler RemoveScenarioClicked;
        public event EventHandler RunTestClicked;

        // 이벤트 트리거 메서드
        private void OnAddScenarioClicked() => AddScenarioClicked?.Invoke(this, EventArgs.Empty);
        private void OnRemoveScenarioClicked() => RemoveScenarioClicked?.Invoke(this, EventArgs.Empty);
        private void OnRunTestClicked() => RunTestClicked?.Invoke(this, EventArgs.Empty);

        public MainForm()
        {
            InitializeComponent();

            // 버튼 클릭 이벤트에 트리거 연결
            addScenarioButton.Click += (s, e) => OnAddScenarioClicked();
            removeButton.Click += (s, e) => OnRemoveScenarioClicked();
            runTestButton.Click += (s, e) => OnRunTestClicked();
        }

        public void UpdateScenarioList(IEnumerable<string> scenarios)
        {
            scenarioListBox.Items.Clear();
            foreach (var scenario in scenarios)
            {
                scenarioListBox.Items.Add(scenario);
            }
        }

        public string GetSelectedScenarioName() => scenarioListBox.SelectedItem?.ToString();
        public int GetSessionCount() => (int)sessionCountInput.Value;
        public string GetSelectedScenarioFromListView()
        {
            return scenarioSessionListView.SelectedItems.Count > 0
                ? scenarioSessionListView.SelectedItems[0].Text
                : null;
        }

        public void AddScenarioToListView(string scenarioName, int sessionCount)
        {
            foreach (ListViewItem item in scenarioSessionListView.Items)
            {
                if (item.Text == scenarioName)
                {
                    // 동일한 이름의 시나리오가 이미 존재하면 카운트 증가
                    int currentCount = int.Parse(item.SubItems[1].Text);
                    item.SubItems[1].Text = (currentCount + sessionCount).ToString();
                    return;
                }
            }

            // 동일한 이름이 없으면 새 항목 추가
            var newItem = new ListViewItem(new[] { scenarioName, sessionCount.ToString() });
            scenarioSessionListView.Items.Add(newItem);
        }

        public void RemoveScenarioFromListView(string scenarioName)
        {
            foreach (ListViewItem item in scenarioSessionListView.Items)
            {
                if (item.Text == scenarioName)
                {
                    scenarioSessionListView.Items.Remove(item);
                    break;
                }
            }
        }
        public void ShowMessage(string message)
        {
            MessageBox.Show(message, "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
