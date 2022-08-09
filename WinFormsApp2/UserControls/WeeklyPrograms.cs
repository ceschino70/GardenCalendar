using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WinFormsApp2.Structures;

namespace WinFormsApp2
{
    public partial class WeeklyPrograms : UserControl
    {
        #region Public Variable
        public int firstDayToShow { set { _firstDayToShow = value; _daySelected = value; } }
        public List<DayJSON> dayList { get { return _daysProgramList; } set { _daysProgramList = value; } }
        #endregion

        #region Private Variables
        private int _firstDayToShow = 1;
        private List<DayJSON> _daysProgramList = new List<DayJSON>();
        private DayJSON _dayProgram = new DayJSON();
        private static int _daySelected;
        private DayJSON _dayJsonProgram = new();
        #endregion

        #region Public method
        public WeeklyPrograms()
        {
            InitializeComponent();
        }

        public void UpdatePage()
        {
            CyclesUpdate(_firstDayToShow);
            UpdateDayButtonColor(_firstDayToShow);
        }

        public DayJSON SaveWeeklyProgram()
        {

            CyclesSave(_daySelected);

            return _dayJsonProgram;
        }
        #endregion

        private void UpdateDayButtonColor(int dayToShow)
        {
            string buttonName = "btDay" + dayToShow;

            foreach (Control c in this.Controls)
            {
                foreach (Control cc in c.Controls)
                {
                    if (cc.Name == "panelDays")
                    {
                        foreach (Control cc2 in cc.Controls)
                        {
                            if (cc2.Name == buttonName)
                            {
                                cc2.BackColor = Color.Indigo;
                                cc2.ForeColor = Color.White;
                            }
                            else
                            {
                                cc2.BackColor = Color.DarkGray;
                                cc2.ForeColor = Color.White;
                            }
                        }
                    }
                }
            }
        }

        private void DynamicButton_Click(object sender, EventArgs e)
        {
            string daySelected = ((Button)sender).Text;
            int numberOfDay = Enum.DaysOfWeek.extractDayFromName(daySelected);
            CyclesUpdate(numberOfDay);

            UpdateDayButtonColor(numberOfDay);

            _daySelected = numberOfDay;
        }

        private void CyclesUpdate(int numberOfDay)
        {
            _dayProgram = _daysProgramList.Find(x => x.day == numberOfDay);

            cycleProgram1.cycleEnable = _dayProgram.cycle1.enable;
            cycleProgram1.onTime = CommonFunctions.convertStringToDateTime(_dayProgram.cycle1.on);
            cycleProgram1.offTime = CommonFunctions.convertStringToDateTime(_dayProgram.cycle1.off);
            cycleProgram1.rele1On = _dayProgram.cycle1.relé1;
            cycleProgram1.rele2On = _dayProgram.cycle1.relé2;
            cycleProgram1.rele3On = _dayProgram.cycle1.relé3;

            cycleProgram2.cycleEnable = _dayProgram.cycle2.enable;
            cycleProgram2.onTime = CommonFunctions.convertStringToDateTime(_dayProgram.cycle2.on);
            cycleProgram2.offTime = CommonFunctions.convertStringToDateTime(_dayProgram.cycle2.off);
            cycleProgram2.rele1On = _dayProgram.cycle2.relé1;
            cycleProgram2.rele2On = _dayProgram.cycle2.relé2;
            cycleProgram2.rele3On = _dayProgram.cycle2.relé3;

            cycleProgram3.cycleEnable = _dayProgram.cycle3.enable;
            cycleProgram3.onTime = CommonFunctions.convertStringToDateTime(_dayProgram.cycle3.on);
            cycleProgram3.offTime = CommonFunctions.convertStringToDateTime(_dayProgram.cycle3.off);
            cycleProgram3.rele1On = _dayProgram.cycle3.relé1;
            cycleProgram3.rele2On = _dayProgram.cycle3.relé2;
            cycleProgram3.rele3On = _dayProgram.cycle3.relé3;
        }

        private void CyclesSave(int numberOfDayToSave)
        {
            _dayJsonProgram.day = numberOfDayToSave;
            CycleJSON cycle1 = new CycleJSON();
            cycle1.enable = cycleProgram1.cycleEnable;
            cycle1.on = CommonFunctions.convertDateTimeToString(cycleProgram1.onTime);
            cycle1.off = CommonFunctions.convertDateTimeToString(cycleProgram1.offTime);
            cycle1.relé1 = cycleProgram1.rele1On;
            cycle1.relé2 = cycleProgram1.rele2On;
            cycle1.relé3 = cycleProgram1.rele3On;
            _dayJsonProgram.cycle1 = cycle1;

            CycleJSON cycle2 = new CycleJSON();
            cycle2.enable = cycleProgram2.cycleEnable;
            cycle2.on = CommonFunctions.convertDateTimeToString(cycleProgram2.onTime);
            cycle2.off = CommonFunctions.convertDateTimeToString(cycleProgram2.offTime);
            cycle2.relé1 = cycleProgram2.rele1On;
            cycle2.relé2 = cycleProgram2.rele2On;
            cycle2.relé3 = cycleProgram2.rele3On;
            _dayJsonProgram.cycle2 = cycle2;

            CycleJSON cycle3 = new CycleJSON();
            cycle3.enable = cycleProgram3.cycleEnable;
            cycle3.on = CommonFunctions.convertDateTimeToString(cycleProgram3.onTime);
            cycle3.off = CommonFunctions.convertDateTimeToString(cycleProgram3.offTime);
            cycle3.relé1 = cycleProgram3.rele1On;
            cycle3.relé2 = cycleProgram3.rele2On;
            cycle3.relé3 = cycleProgram3.rele3On;
            _dayJsonProgram.cycle3 = cycle3;
        }
    }
}
