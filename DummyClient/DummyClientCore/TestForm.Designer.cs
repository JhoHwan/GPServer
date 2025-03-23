namespace DummyClientCore
{
    partial class TestForm
    {
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.logTextBox = new System.Windows.Forms.TextBox();
            this.labelLog = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // logTextBox
            // 
            this.logTextBox.Location = new System.Drawing.Point(20, 40);
            this.logTextBox.Multiline = true;
            this.logTextBox.Name = "logTextBox";
            this.logTextBox.ReadOnly = true;
            this.logTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.logTextBox.Size = new System.Drawing.Size(720, 300);
            this.logTextBox.TabIndex = 0;
            // 
            // labelLog
            // 
            this.labelLog.AutoSize = true;
            this.labelLog.Location = new System.Drawing.Point(20, 20);
            this.labelLog.Name = "labelLog";
            this.labelLog.Size = new System.Drawing.Size(33, 15);
            this.labelLog.TabIndex = 2;
            this.labelLog.Text = "Logs:";
            // 
            // TestForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(770, 370);
            this.Controls.Add(this.labelLog);
            this.Controls.Add(this.logTextBox);
            this.Name = "TestForm";
            this.Text = "Test Execution";
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        #endregion

        private System.Windows.Forms.TextBox logTextBox;
        private System.Windows.Forms.Label labelLog;
    }
}