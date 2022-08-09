namespace WinFormsApp2
{
    partial class WeeklyPrograms
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panelDays = new System.Windows.Forms.TableLayoutPanel();
            this.btDay7 = new System.Windows.Forms.Button();
            this.btDay6 = new System.Windows.Forms.Button();
            this.btDay5 = new System.Windows.Forms.Button();
            this.btDay4 = new System.Windows.Forms.Button();
            this.btDay3 = new System.Windows.Forms.Button();
            this.btDay2 = new System.Windows.Forms.Button();
            this.btDay1 = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cycleProgram1 = new WinFormsApp2.UserControls.CycleProgramNoText();
            this.cycleProgram2 = new WinFormsApp2.UserControls.CycleProgramNoText();
            this.cycleProgram3 = new WinFormsApp2.UserControls.CycleProgramNoText();
            this.tableDayPanel = new System.Windows.Forms.TableLayoutPanel();
            this.panelDays.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableDayPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelDays
            // 
            this.panelDays.ColumnCount = 7;
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28571F));
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28572F));
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28572F));
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28572F));
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28572F));
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28572F));
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 14.28572F));
            this.panelDays.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.panelDays.Controls.Add(this.btDay7, 6, 0);
            this.panelDays.Controls.Add(this.btDay6, 5, 0);
            this.panelDays.Controls.Add(this.btDay5, 4, 0);
            this.panelDays.Controls.Add(this.btDay4, 3, 0);
            this.panelDays.Controls.Add(this.btDay3, 2, 0);
            this.panelDays.Controls.Add(this.btDay2, 1, 0);
            this.panelDays.Controls.Add(this.btDay1, 0, 0);
            this.panelDays.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelDays.Location = new System.Drawing.Point(3, 3);
            this.panelDays.Name = "panelDays";
            this.panelDays.RowCount = 1;
            this.panelDays.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.panelDays.Size = new System.Drawing.Size(438, 34);
            this.panelDays.TabIndex = 1;
            // 
            // btDay7
            // 
            this.btDay7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btDay7.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDay7.Location = new System.Drawing.Point(375, 3);
            this.btDay7.Name = "btDay7";
            this.btDay7.Size = new System.Drawing.Size(60, 28);
            this.btDay7.TabIndex = 7;
            this.btDay7.Text = "Sun";
            this.btDay7.UseVisualStyleBackColor = true;
            this.btDay7.Click += new System.EventHandler(this.DynamicButton_Click);
            // 
            // btDay6
            // 
            this.btDay6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btDay6.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDay6.Location = new System.Drawing.Point(313, 3);
            this.btDay6.Name = "btDay6";
            this.btDay6.Size = new System.Drawing.Size(56, 28);
            this.btDay6.TabIndex = 6;
            this.btDay6.Text = "Sat";
            this.btDay6.UseVisualStyleBackColor = true;
            this.btDay6.Click += new System.EventHandler(this.DynamicButton_Click);
            // 
            // btDay5
            // 
            this.btDay5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btDay5.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDay5.Location = new System.Drawing.Point(251, 3);
            this.btDay5.Name = "btDay5";
            this.btDay5.Size = new System.Drawing.Size(56, 28);
            this.btDay5.TabIndex = 5;
            this.btDay5.Text = "Fri";
            this.btDay5.UseVisualStyleBackColor = true;
            this.btDay5.Click += new System.EventHandler(this.DynamicButton_Click);
            // 
            // btDay4
            // 
            this.btDay4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btDay4.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDay4.Location = new System.Drawing.Point(189, 3);
            this.btDay4.Name = "btDay4";
            this.btDay4.Size = new System.Drawing.Size(56, 28);
            this.btDay4.TabIndex = 4;
            this.btDay4.Text = "Thu";
            this.btDay4.UseVisualStyleBackColor = true;
            this.btDay4.Click += new System.EventHandler(this.DynamicButton_Click);
            // 
            // btDay3
            // 
            this.btDay3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btDay3.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDay3.Location = new System.Drawing.Point(127, 3);
            this.btDay3.Name = "btDay3";
            this.btDay3.Size = new System.Drawing.Size(56, 28);
            this.btDay3.TabIndex = 3;
            this.btDay3.Text = "Wed";
            this.btDay3.UseVisualStyleBackColor = true;
            this.btDay3.Click += new System.EventHandler(this.DynamicButton_Click);
            // 
            // btDay2
            // 
            this.btDay2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btDay2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDay2.Location = new System.Drawing.Point(65, 3);
            this.btDay2.Name = "btDay2";
            this.btDay2.Size = new System.Drawing.Size(56, 28);
            this.btDay2.TabIndex = 2;
            this.btDay2.Text = "Tue";
            this.btDay2.UseVisualStyleBackColor = true;
            this.btDay2.Click += new System.EventHandler(this.DynamicButton_Click);
            // 
            // btDay1
            // 
            this.btDay1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btDay1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.btDay1.Location = new System.Drawing.Point(3, 3);
            this.btDay1.Name = "btDay1";
            this.btDay1.Size = new System.Drawing.Size(56, 28);
            this.btDay1.TabIndex = 1;
            this.btDay1.Text = "Mon";
            this.btDay1.UseVisualStyleBackColor = true;
            this.btDay1.Click += new System.EventHandler(this.DynamicButton_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 6;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.66667F));
            this.tableLayoutPanel1.Controls.Add(this.label6, 5, 0);
            this.tableLayoutPanel1.Controls.Add(this.label5, 4, 0);
            this.tableLayoutPanel1.Controls.Add(this.label4, 3, 0);
            this.tableLayoutPanel1.Controls.Add(this.label3, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.label2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 43);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(438, 19);
            this.tableLayoutPanel1.TabIndex = 5;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label6.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label6.Location = new System.Drawing.Point(368, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 19);
            this.label6.TabIndex = 5;
            this.label6.Text = "Relé 3";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label5.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label5.Location = new System.Drawing.Point(295, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 19);
            this.label5.TabIndex = 4;
            this.label5.Text = "Relé 2";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label4.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label4.Location = new System.Drawing.Point(222, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(67, 19);
            this.label4.TabIndex = 3;
            this.label4.Text = "Relé 1";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label3.Location = new System.Drawing.Point(149, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 19);
            this.label3.TabIndex = 2;
            this.label3.Text = "Time OFF";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label2.Location = new System.Drawing.Point(76, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(67, 19);
            this.label2.TabIndex = 1;
            this.label2.Text = "Time ON";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label1.Location = new System.Drawing.Point(3, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(67, 19);
            this.label1.TabIndex = 0;
            this.label1.Text = "Cycle";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // cycleProgram1
            // 
            this.cycleProgram1.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.cycleProgram1.cycleEnable = false;
            this.cycleProgram1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cycleProgram1.Location = new System.Drawing.Point(3, 68);
            this.cycleProgram1.Name = "cycleProgram1";
            this.cycleProgram1.offTime = new System.DateTime(((long)(0)));
            this.cycleProgram1.onTime = new System.DateTime(((long)(0)));
            this.cycleProgram1.rele1On = false;
            this.cycleProgram1.rele2On = false;
            this.cycleProgram1.rele3On = false;
            this.cycleProgram1.Size = new System.Drawing.Size(438, 40);
            this.cycleProgram1.TabIndex = 6;
            // 
            // cycleProgram2
            // 
            this.cycleProgram2.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.cycleProgram2.cycleEnable = false;
            this.cycleProgram2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cycleProgram2.Location = new System.Drawing.Point(3, 114);
            this.cycleProgram2.Name = "cycleProgram2";
            this.cycleProgram2.offTime = new System.DateTime(((long)(0)));
            this.cycleProgram2.onTime = new System.DateTime(((long)(0)));
            this.cycleProgram2.rele1On = false;
            this.cycleProgram2.rele2On = false;
            this.cycleProgram2.rele3On = false;
            this.cycleProgram2.Size = new System.Drawing.Size(438, 40);
            this.cycleProgram2.TabIndex = 7;
            // 
            // cycleProgram3
            // 
            this.cycleProgram3.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.cycleProgram3.cycleEnable = false;
            this.cycleProgram3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cycleProgram3.Location = new System.Drawing.Point(3, 160);
            this.cycleProgram3.Name = "cycleProgram3";
            this.cycleProgram3.offTime = new System.DateTime(((long)(0)));
            this.cycleProgram3.onTime = new System.DateTime(((long)(0)));
            this.cycleProgram3.rele1On = false;
            this.cycleProgram3.rele2On = false;
            this.cycleProgram3.rele3On = false;
            this.cycleProgram3.Size = new System.Drawing.Size(438, 41);
            this.cycleProgram3.TabIndex = 8;
            // 
            // tableDayPanel
            // 
            this.tableDayPanel.ColumnCount = 1;
            this.tableDayPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableDayPanel.Controls.Add(this.panelDays, 0, 0);
            this.tableDayPanel.Controls.Add(this.cycleProgram3, 0, 4);
            this.tableDayPanel.Controls.Add(this.tableLayoutPanel1, 0, 1);
            this.tableDayPanel.Controls.Add(this.cycleProgram2, 0, 3);
            this.tableDayPanel.Controls.Add(this.cycleProgram1, 0, 2);
            this.tableDayPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableDayPanel.Location = new System.Drawing.Point(0, 0);
            this.tableDayPanel.Name = "tableDayPanel";
            this.tableDayPanel.RowCount = 5;
            this.tableDayPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.tableDayPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableDayPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableDayPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableDayPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableDayPanel.Size = new System.Drawing.Size(444, 204);
            this.tableDayPanel.TabIndex = 9;
            // 
            // WeeklyPrograms
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.Controls.Add(this.tableDayPanel);
            this.Name = "WeeklyPrograms";
            this.Size = new System.Drawing.Size(444, 204);
            this.panelDays.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableDayPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private TableLayoutPanel panelDays;
        private Button btDay7;
        private Button btDay6;
        private Button btDay5;
        private Button btDay4;
        private Button btDay3;
        private Button btDay2;
        private Button btDay1;
        private TableLayoutPanel tableLayoutPanel1;
        private Label label6;
        private Label label5;
        private Label label4;
        private Label label3;
        private Label label2;
        private Label label1;
        private UserControls.CycleProgramNoText cycleProgram1;
        private UserControls.CycleProgramNoText cycleProgram2;
        private UserControls.CycleProgramNoText cycleProgram3;
        private TableLayoutPanel tableDayPanel;
    }
}
