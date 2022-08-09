//using System.Text.Json;
using Newtonsoft.Json;
using WinFormsApp2.Structures;

namespace WinFormsApp2
{
    public partial class Form1 : Form
    {
        #region Constants
        const int numberOfCycles = 3;
        const int numberOfDay = 7;
        #endregion

        #region Variables
        private int firstDayOnOpening = 1;
        private static JSONClass jsonFiles = new JSONClass();
        private string fileName;
        #endregion
        public Form1()
        {
            InitializeComponent();

            UpdataTimeAndDate();

            timerClockUpdate.Enabled = true;
            string fileJSONLocation = "";
            fileName = Application.StartupPath + "WeeklyProgram.json";

            if (jsonFiles.ReadJsonFile(fileName, out jsonFiles))
            {
                List<DayJSON> dayJSONs = new List<DayJSON>();
                dayJSONs.Add(jsonFiles.day1);
                dayJSONs.Add(jsonFiles.day2);
                dayJSONs.Add(jsonFiles.day3);
                dayJSONs.Add(jsonFiles.day4);
                dayJSONs.Add(jsonFiles.day5);
                dayJSONs.Add(jsonFiles.day6);
                dayJSONs.Add(jsonFiles.day7);

                weeklyPrograms1.firstDayToShow = firstDayOnOpening;
                weeklyPrograms1.dayList = dayJSONs;
                weeklyPrograms1.UpdatePage();
            }
            else
            {
                MessageBox.Show("Reading file error!");
                weeklyPrograms1.Visible = false;
            }
        }

        #region
        private void UpdataTimeAndDate()
        {
            DateTime now = DateTime.Now;
            string strDate = ("Date: " + now.Day.ToString() + "/" + now.Month.ToString() + "/" + now.Year.ToString());
            lbDate.Text = strDate;
            string strTime = ("Time: " + now.Hour + CommonFunctions.separatorCharHoursMinutes + now.Minute.ToString("D2"));
            lbTime.Text = strTime;
        }
        #endregion

        #region Events
        private void btClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void timerClockUpdate_Tick(object sender, EventArgs e)
        {
            UpdataTimeAndDate();
        }

        private void btSave_Click(object sender, EventArgs e)
        {
            JSONClass aa = new JSONClass();
            DayJSON _programDayToSave = weeklyPrograms1.SaveWeeklyProgram();
            jsonFiles.WriteJsonFile(jsonFiles, _programDayToSave, fileName);
        }

        #endregion
    }
}