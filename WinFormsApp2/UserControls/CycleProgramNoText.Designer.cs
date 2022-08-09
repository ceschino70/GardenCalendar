namespace WinFormsApp2.UserControls
{
    partial class CycleProgramNoText
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
            this.tbOn = new System.Windows.Forms.TextBox();
            this.tbOff = new System.Windows.Forms.TextBox();
            this.cbRele1On = new System.Windows.Forms.CheckBox();
            this.cbRele2On = new System.Windows.Forms.CheckBox();
            this.cbEnable = new System.Windows.Forms.CheckBox();
            this.cbRele3On = new System.Windows.Forms.CheckBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.panel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbOn
            // 
            this.tbOn.BackColor = System.Drawing.Color.DarkGray;
            this.tbOn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbOn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbOn.Location = new System.Drawing.Point(0, 0);
            this.tbOn.Name = "tbOn";
            this.tbOn.Size = new System.Drawing.Size(51, 23);
            this.tbOn.TabIndex = 0;
            this.tbOn.Text = "00:00";
            this.tbOn.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tbOn.TextChanged += new System.EventHandler(this.textBox_TextChanged);
            this.tbOn.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // tbOff
            // 
            this.tbOff.BackColor = System.Drawing.Color.DarkGray;
            this.tbOff.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbOff.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tbOff.Location = new System.Drawing.Point(0, 0);
            this.tbOff.Name = "tbOff";
            this.tbOff.Size = new System.Drawing.Size(51, 23);
            this.tbOff.TabIndex = 1;
            this.tbOff.Text = "00:00";
            this.tbOff.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tbOff.TextChanged += new System.EventHandler(this.textBox_TextChanged);
            this.tbOff.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // cbRele1On
            // 
            this.cbRele1On.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cbRele1On.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.cbRele1On.Location = new System.Drawing.Point(19, 3);
            this.cbRele1On.Name = "cbRele1On";
            this.cbRele1On.Size = new System.Drawing.Size(12, 64);
            this.cbRele1On.TabIndex = 0;
            this.cbRele1On.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.cbRele1On.UseVisualStyleBackColor = true;
            // 
            // cbRele2On
            // 
            this.cbRele2On.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cbRele2On.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.cbRele2On.Location = new System.Drawing.Point(19, 3);
            this.cbRele2On.Name = "cbRele2On";
            this.cbRele2On.Size = new System.Drawing.Size(12, 64);
            this.cbRele2On.TabIndex = 1;
            this.cbRele2On.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.cbRele2On.UseVisualStyleBackColor = true;
            // 
            // cbEnable
            // 
            this.cbEnable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cbEnable.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.cbEnable.Location = new System.Drawing.Point(0, 0);
            this.cbEnable.Name = "cbEnable";
            this.cbEnable.Size = new System.Drawing.Size(51, 21);
            this.cbEnable.TabIndex = 1;
            this.cbEnable.Text = "Enable";
            this.cbEnable.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.cbEnable.UseVisualStyleBackColor = true;
            this.cbEnable.CheckedChanged += new System.EventHandler(this.cbEnable_CheckedChanged);
            // 
            // cbRele3On
            // 
            this.cbRele3On.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cbRele3On.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.cbRele3On.Location = new System.Drawing.Point(20, 3);
            this.cbRele3On.Name = "cbRele3On";
            this.cbRele3On.Size = new System.Drawing.Size(12, 64);
            this.cbRele3On.TabIndex = 1;
            this.cbRele3On.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.cbRele3On.UseVisualStyleBackColor = true;
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
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel4, 5, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 3, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel3, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 4, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(343, 76);
            this.tableLayoutPanel1.TabIndex = 2;
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.ColumnCount = 3;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 18F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Controls.Add(this.cbRele3On, 1, 0);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(288, 3);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 1;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(52, 70);
            this.tableLayoutPanel4.TabIndex = 3;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.cbEnable);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(51, 21);
            this.panel1.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 3;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 18F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.cbRele1On, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(174, 3);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(51, 70);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.tbOn);
            this.panel2.Location = new System.Drawing.Point(60, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(51, 21);
            this.panel2.TabIndex = 1;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.tbOff);
            this.panel3.Location = new System.Drawing.Point(117, 3);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(51, 21);
            this.panel3.TabIndex = 2;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 3;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 18F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.cbRele2On, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(231, 3);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(51, 70);
            this.tableLayoutPanel3.TabIndex = 1;
            // 
            // CycleProgramNoText
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.WindowFrame;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "CycleProgramNoText";
            this.Size = new System.Drawing.Size(343, 76);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private TextBox tbOn;
        private TextBox tbOff;
        private CheckBox cbRele1On;
        private CheckBox cbRele2On;
        private CheckBox cbEnable;
        private CheckBox cbRele3On;
        private TableLayoutPanel tableLayoutPanel1;
        private TableLayoutPanel tableLayoutPanel4;
        private Panel panel1;
        private TableLayoutPanel tableLayoutPanel2;
        private Panel panel2;
        private Panel panel3;
        private TableLayoutPanel tableLayoutPanel3;
    }
}
