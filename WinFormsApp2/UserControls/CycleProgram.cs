using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsApp2.UserControls
{
    public partial class CycleProgram : UserControl
    {
        #region Public Variable
        public bool cycleEnable { get { return cbEnable.Checked; } set { _cycleEnable = value; enableCycle(_cycleEnable); } }
        public DateTime onTime { get { return CommonFunctions.convertStringToDateTime(tbOn.Text); } set { _onTime = value; updateElements(); } }
        public DateTime offTime { get { return CommonFunctions.convertStringToDateTime(tbOff.Text); } set { _offTime = value; updateElements(); } }
        public bool rele1On { get { return cbRele1On.Checked; } set {_rele1On = value; updateElements(); } }
        public bool rele2On { get { return cbRele2On.Checked; } set { _rele2On = value; updateElements(); } }
        public bool rele3On { get { return cbRele3On.Checked; } set { _rele3On = value; updateElements(); } }
        #endregion

        #region Private Variable
        private bool _cycleEnable = false;
        private DateTime _onTime;
        private DateTime _offTime;
        private bool _rele1On = false;
        private bool _rele2On = false;
        private bool _rele3On = false;
        private string _previousText = string.Empty;

        #endregion

        public CycleProgram()
        {
            InitializeComponent();

            enableCycle(_cycleEnable);
            updateElements();
        }

        private void updateElements()
        {
            tbOn.Text = convertTimeToShow(_onTime);
            tbOff.Text = convertTimeToShow(_offTime);
            cbRele1On.Checked = _rele1On;
            cbRele2On.Checked = _rele2On;
            cbRele3On.Checked = _rele3On;
        }

        private string convertTimeToShow (DateTime time)
        {
            string stringToShow;

            try
            {
                stringToShow = time.Hour.ToString("00.##") + CommonFunctions.separatorCharHoursMinutes + time.Minute.ToString("00.##");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                stringToShow = "Err.";
            }

            return stringToShow;
        }

        private void enableCycle(bool enableCycle)
        {
            if (enableCycle)
            {
                cbEnable.Checked = true;
                tbOn.Enabled = true;
                tbOff.Enabled = true;
                cbRele1On.Enabled = true;
                cbRele2On.Enabled = true;
                cbRele3On.Enabled = true;
            }
            else
            {
                cbEnable.Checked = false;
                tbOn.Enabled = false;
                tbOff.Enabled = false;
                cbRele1On.Enabled = false;
                cbRele2On.Enabled = false;
                cbRele3On.Enabled = false;
            }
        }

        #region Events
        private void cbEnable_CheckedChanged(object sender, EventArgs e)
        {
            _cycleEnable = cbEnable.Checked;

            enableCycle(_cycleEnable);
        }

        private void textBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            bool letterOk = false;
            if (char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar) || (e.KeyChar == CommonFunctions.separatorCharHoursMinutes))
            {
                letterOk = true;
            }

            string tx = (sender as TextBox).Text;

            // only allow one decimal point
            if ((e.KeyChar == CommonFunctions.separatorCharHoursMinutes) && (tx.IndexOf(CommonFunctions.separatorCharHoursMinutes) > -1))
            {
                letterOk = false;
            }

            if (!letterOk)
                e.Handled = true;

            _previousText = tx;
        }
        #endregion

        private void textBox_TextChanged(object sender, EventArgs e)
        {
            TextBox tbSelected = (sender as TextBox);
            string tx = tbSelected.Text;
            string[] txSplited = tx.Split(CommonFunctions.separatorCharHoursMinutes);

            if (txSplited.Length == 2)
            {
                int hour;
                if (!Int32.TryParse(txSplited[0], out hour) || hour < 0 || hour > 23)
                    resetText(tbSelected);
                int min;
                if (!Int32.TryParse(txSplited[1], out min) || min < 0 || min > 59)
                    resetText(tbSelected);
            }
            else
                resetText(tbSelected);
        }

        private void resetText(TextBox tb)
        {
            tb.Text = _previousText;
            tb.SelectionStart = 0;
            tb.SelectionLength = 6;
        }
    }
}
