namespace DummyClientCore
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.scenarioListBox = new System.Windows.Forms.ListBox();
            this.sessionCountInput = new System.Windows.Forms.NumericUpDown();
            this.addScenarioButton = new System.Windows.Forms.Button();
            this.scenarioSessionListView = new System.Windows.Forms.ListView();
            this.columnScenarioName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnSessionCount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.removeButton = new System.Windows.Forms.Button();
            this.runTestButton = new System.Windows.Forms.Button();
            this.labelScenarioList = new System.Windows.Forms.Label();
            this.labelSessionCount = new System.Windows.Forms.Label();
            this.labelAddedScenarios = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.sessionCountInput)).BeginInit();
            this.SuspendLayout();
            // 
            // scenarioListBox
            // 
            this.scenarioListBox.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.scenarioListBox.FormattingEnabled = true;
            this.scenarioListBox.ItemHeight = 15;
            this.scenarioListBox.Location = new System.Drawing.Point(24, 46);
            this.scenarioListBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.scenarioListBox.Name = "scenarioListBox";
            this.scenarioListBox.Size = new System.Drawing.Size(440, 154);
            this.scenarioListBox.TabIndex = 0;
            // 
            // sessionCountInput
            // 
            this.sessionCountInput.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.sessionCountInput.Location = new System.Drawing.Point(480, 46);
            this.sessionCountInput.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.sessionCountInput.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.sessionCountInput.Name = "sessionCountInput";
            this.sessionCountInput.Size = new System.Drawing.Size(160, 22);
            this.sessionCountInput.TabIndex = 1;
            this.sessionCountInput.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // addScenarioButton
            // 
            this.addScenarioButton.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.addScenarioButton.Location = new System.Drawing.Point(480, 73);
            this.addScenarioButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.addScenarioButton.Name = "addScenarioButton";
            this.addScenarioButton.Size = new System.Drawing.Size(160, 32);
            this.addScenarioButton.TabIndex = 2;
            this.addScenarioButton.Text = "Add Scenario";
            this.addScenarioButton.UseVisualStyleBackColor = true;
            // 
            // scenarioSessionListView
            // 
            this.scenarioSessionListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnScenarioName,
            this.columnSessionCount});
            this.scenarioSessionListView.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.scenarioSessionListView.FullRowSelect = true;
            this.scenarioSessionListView.GridLines = true;
            this.scenarioSessionListView.HideSelection = false;
            this.scenarioSessionListView.Location = new System.Drawing.Point(24, 240);
            this.scenarioSessionListView.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.scenarioSessionListView.Name = "scenarioSessionListView";
            this.scenarioSessionListView.Size = new System.Drawing.Size(616, 161);
            this.scenarioSessionListView.TabIndex = 3;
            this.scenarioSessionListView.UseCompatibleStateImageBehavior = false;
            this.scenarioSessionListView.View = System.Windows.Forms.View.Details;
            // 
            // columnScenarioName
            // 
            this.columnScenarioName.Text = "Scenario Name";
            this.columnScenarioName.Width = 400;
            // 
            // columnSessionCount
            // 
            this.columnSessionCount.Text = "Session Count";
            this.columnSessionCount.Width = 200;
            // 
            // removeButton
            // 
            this.removeButton.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.removeButton.Location = new System.Drawing.Point(24, 410);
            this.removeButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.removeButton.Name = "removeButton";
            this.removeButton.Size = new System.Drawing.Size(240, 43);
            this.removeButton.TabIndex = 4;
            this.removeButton.Text = "Remove Session";
            this.removeButton.UseVisualStyleBackColor = true;
            // 
            // runTestButton
            // 
            this.runTestButton.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.runTestButton.Location = new System.Drawing.Point(400, 410);
            this.runTestButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.runTestButton.Name = "runTestButton";
            this.runTestButton.Size = new System.Drawing.Size(240, 43);
            this.runTestButton.TabIndex = 5;
            this.runTestButton.Text = "Run Test";
            this.runTestButton.UseVisualStyleBackColor = true;
            // 
            // labelScenarioList
            // 
            this.labelScenarioList.AutoSize = true;
            this.labelScenarioList.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.labelScenarioList.Location = new System.Drawing.Point(24, 24);
            this.labelScenarioList.Name = "labelScenarioList";
            this.labelScenarioList.Size = new System.Drawing.Size(103, 15);
            this.labelScenarioList.TabIndex = 6;
            this.labelScenarioList.Text = "Scenario List:";
            // 
            // labelSessionCount
            // 
            this.labelSessionCount.AutoSize = true;
            this.labelSessionCount.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.labelSessionCount.Location = new System.Drawing.Point(477, 24);
            this.labelSessionCount.Name = "labelSessionCount";
            this.labelSessionCount.Size = new System.Drawing.Size(111, 15);
            this.labelSessionCount.TabIndex = 7;
            this.labelSessionCount.Text = "Session Count";
            // 
            // labelAddedScenarios
            // 
            this.labelAddedScenarios.AutoSize = true;
            this.labelAddedScenarios.Font = new System.Drawing.Font("G마켓 산스 Medium", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.labelAddedScenarios.Location = new System.Drawing.Point(24, 219);
            this.labelAddedScenarios.Name = "labelAddedScenarios";
            this.labelAddedScenarios.Size = new System.Drawing.Size(133, 15);
            this.labelAddedScenarios.TabIndex = 8;
            this.labelAddedScenarios.Text = "Added Scenarios:";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(664, 464);
            this.Controls.Add(this.labelAddedScenarios);
            this.Controls.Add(this.labelSessionCount);
            this.Controls.Add(this.labelScenarioList);
            this.Controls.Add(this.runTestButton);
            this.Controls.Add(this.removeButton);
            this.Controls.Add(this.scenarioSessionListView);
            this.Controls.Add(this.addScenarioButton);
            this.Controls.Add(this.sessionCountInput);
            this.Controls.Add(this.scenarioListBox);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "MainForm";
            this.Text = "Server Tester";
            ((System.ComponentModel.ISupportInitialize)(this.sessionCountInput)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox scenarioListBox;
        private System.Windows.Forms.NumericUpDown sessionCountInput;
        private System.Windows.Forms.Button addScenarioButton;
        private System.Windows.Forms.ListView scenarioSessionListView;
        private System.Windows.Forms.ColumnHeader columnScenarioName;
        private System.Windows.Forms.ColumnHeader columnSessionCount;
        private System.Windows.Forms.Button removeButton;
        private System.Windows.Forms.Button runTestButton;
        private System.Windows.Forms.Label labelScenarioList;
        private System.Windows.Forms.Label labelSessionCount;
        private System.Windows.Forms.Label labelAddedScenarios;
    }
}

