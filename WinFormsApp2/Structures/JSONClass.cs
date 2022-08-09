using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace WinFormsApp2.Structures
{
    public class JSONClass
    {
        public int aa { get; set; }
        public DayJSON? day1 { get; set; }
        public DayJSON? day2 { get; set; }
        public DayJSON? day3 { get; set; }
        public DayJSON? day4 { get; set; }
        public DayJSON? day5 { get; set; }
        public DayJSON? day6 { get; set; }
        public DayJSON? day7 { get; set; }


        public bool ReadJsonFile(string filePath, out JSONClass jsonReturn)
        {
            bool returnStatusOk = false;
            JSONClass _tmp = new JSONClass();
            try
            {
                if (File.Exists(filePath))
                {
                    using (StreamReader reader = new StreamReader(filePath))
                    {
                        string json = reader.ReadToEnd();
                        _tmp = JsonConvert.DeserializeObject<JSONClass>(json);
                    }
                    returnStatusOk = true;
                }
                else
                {
                    MessageBox.Show("File not found!");
                    returnStatusOk =  false;
                }
            }
            catch(Exception e)
            {
                MessageBox.Show(e.Message);
                returnStatusOk = false;
            }
            jsonReturn = _tmp;

            return returnStatusOk;
        }

        public bool WriteJsonFile(JSONClass streamToWrite, DayJSON dj, string filePath)
        {
            bool returnStatusOk = false;

            try
            {
                aa = 55;

                if (streamToWrite.day1.day == dj.day)
                {
                    #region day 1
                    streamToWrite.day1.cycle1.enable = dj.cycle1.enable;
                    streamToWrite.day1.cycle1.on = dj.cycle1.on;
                    streamToWrite.day1.cycle1.off = dj.cycle1.off;
                    streamToWrite.day1.cycle1.relé1 = dj.cycle1.relé1;
                    streamToWrite.day1.cycle1.relé2 = dj.cycle1.relé2;
                    streamToWrite.day1.cycle1.relé3 = dj.cycle1.relé3;

                    streamToWrite.day1.cycle2.enable = dj.cycle2.enable;
                    streamToWrite.day1.cycle2.on = dj.cycle2.on;
                    streamToWrite.day1.cycle2.off = dj.cycle2.off;
                    streamToWrite.day1.cycle2.relé1 = dj.cycle2.relé1;
                    streamToWrite.day1.cycle2.relé2 = dj.cycle2.relé2;
                    streamToWrite.day1.cycle2.relé3 = dj.cycle2.relé3;

                    streamToWrite.day1.cycle3.enable = dj.cycle3.enable;
                    streamToWrite.day1.cycle3.on = dj.cycle3.on;
                    streamToWrite.day1.cycle3.off = dj.cycle3.off;
                    streamToWrite.day1.cycle3.relé1 = dj.cycle3.relé1;
                    streamToWrite.day1.cycle3.relé2 = dj.cycle3.relé2;
                    streamToWrite.day1.cycle3.relé3 = dj.cycle3.relé3;
                    #endregion
                }
                else if (streamToWrite.day2.day == dj.day)
                {
                    #region day 2
                    streamToWrite.day2.cycle1.enable = dj.cycle1.enable;
                    streamToWrite.day2.cycle1.on = dj.cycle1.on;
                    streamToWrite.day2.cycle1.off = dj.cycle1.off;
                    streamToWrite.day2.cycle1.relé1 = dj.cycle1.relé1;
                    streamToWrite.day2.cycle1.relé2 = dj.cycle1.relé2;
                    streamToWrite.day2.cycle1.relé3 = dj.cycle1.relé3;

                    streamToWrite.day2.cycle2.enable = dj.cycle2.enable;
                    streamToWrite.day2.cycle2.on = dj.cycle2.on;
                    streamToWrite.day2.cycle2.off = dj.cycle2.off;
                    streamToWrite.day2.cycle2.relé1 = dj.cycle2.relé1;
                    streamToWrite.day2.cycle2.relé2 = dj.cycle2.relé2;
                    streamToWrite.day2.cycle2.relé3 = dj.cycle2.relé3;

                    streamToWrite.day2.cycle3.enable = dj.cycle3.enable;
                    streamToWrite.day2.cycle3.on = dj.cycle3.on;
                    streamToWrite.day2.cycle3.off = dj.cycle3.off;
                    streamToWrite.day2.cycle3.relé1 = dj.cycle3.relé1;
                    streamToWrite.day2.cycle3.relé2 = dj.cycle3.relé2;
                    streamToWrite.day2.cycle3.relé3 = dj.cycle3.relé3;
                    #endregion
                }
                else if (streamToWrite.day3.day == dj.day)
                {
                    #region day 3
                    streamToWrite.day3.cycle1.enable = dj.cycle1.enable;
                    streamToWrite.day3.cycle1.on = dj.cycle1.on;
                    streamToWrite.day3.cycle1.off = dj.cycle1.off;
                    streamToWrite.day3.cycle1.relé1 = dj.cycle1.relé1;
                    streamToWrite.day3.cycle1.relé2 = dj.cycle1.relé2;
                    streamToWrite.day3.cycle1.relé3 = dj.cycle1.relé3;

                    streamToWrite.day3.cycle2.enable = dj.cycle2.enable;
                    streamToWrite.day3.cycle2.on = dj.cycle2.on;
                    streamToWrite.day3.cycle2.off = dj.cycle2.off;
                    streamToWrite.day3.cycle2.relé1 = dj.cycle2.relé1;
                    streamToWrite.day3.cycle2.relé2 = dj.cycle2.relé2;
                    streamToWrite.day3.cycle2.relé3 = dj.cycle2.relé3;

                    streamToWrite.day3.cycle3.enable = dj.cycle3.enable;
                    streamToWrite.day3.cycle3.on = dj.cycle3.on;
                    streamToWrite.day3.cycle3.off = dj.cycle3.off;
                    streamToWrite.day3.cycle3.relé1 = dj.cycle3.relé1;
                    streamToWrite.day3.cycle3.relé2 = dj.cycle3.relé2;
                    streamToWrite.day3.cycle3.relé3 = dj.cycle3.relé3;
                    #endregion
                }
                else if (streamToWrite.day4.day == dj.day)
                {
                    #region day 4
                    streamToWrite.day4.cycle1.enable = dj.cycle1.enable;
                    streamToWrite.day4.cycle1.on = dj.cycle1.on;
                    streamToWrite.day4.cycle1.off = dj.cycle1.off;
                    streamToWrite.day4.cycle1.relé1 = dj.cycle1.relé1;
                    streamToWrite.day4.cycle1.relé2 = dj.cycle1.relé2;
                    streamToWrite.day4.cycle1.relé3 = dj.cycle1.relé3;

                    streamToWrite.day4.cycle2.enable = dj.cycle2.enable;
                    streamToWrite.day4.cycle2.on = dj.cycle2.on;
                    streamToWrite.day4.cycle2.off = dj.cycle2.off;
                    streamToWrite.day4.cycle2.relé1 = dj.cycle2.relé1;
                    streamToWrite.day4.cycle2.relé2 = dj.cycle2.relé2;
                    streamToWrite.day4.cycle2.relé3 = dj.cycle2.relé3;

                    streamToWrite.day4.cycle3.enable = dj.cycle3.enable;
                    streamToWrite.day4.cycle3.on = dj.cycle3.on;
                    streamToWrite.day4.cycle3.off = dj.cycle3.off;
                    streamToWrite.day4.cycle3.relé1 = dj.cycle3.relé1;
                    streamToWrite.day4.cycle3.relé2 = dj.cycle3.relé2;
                    streamToWrite.day4.cycle3.relé3 = dj.cycle3.relé3;
                    #endregion
                }
                else if (streamToWrite.day5.day == dj.day)
                {
                    #region day 5
                    streamToWrite.day5.cycle1.enable = dj.cycle1.enable;
                    streamToWrite.day5.cycle1.on = dj.cycle1.on;
                    streamToWrite.day5.cycle1.off = dj.cycle1.off;
                    streamToWrite.day5.cycle1.relé1 = dj.cycle1.relé1;
                    streamToWrite.day5.cycle1.relé2 = dj.cycle1.relé2;
                    streamToWrite.day5.cycle1.relé3 = dj.cycle1.relé3;

                    streamToWrite.day5.cycle2.enable = dj.cycle2.enable;
                    streamToWrite.day5.cycle2.on = dj.cycle2.on;
                    streamToWrite.day5.cycle2.off = dj.cycle2.off;
                    streamToWrite.day5.cycle2.relé1 = dj.cycle2.relé1;
                    streamToWrite.day5.cycle2.relé2 = dj.cycle2.relé2;
                    streamToWrite.day5.cycle2.relé3 = dj.cycle2.relé3;

                    streamToWrite.day5.cycle3.enable = dj.cycle3.enable;
                    streamToWrite.day5.cycle3.on = dj.cycle3.on;
                    streamToWrite.day5.cycle3.off = dj.cycle3.off;
                    streamToWrite.day5.cycle3.relé1 = dj.cycle3.relé1;
                    streamToWrite.day5.cycle3.relé2 = dj.cycle3.relé2;
                    streamToWrite.day5.cycle3.relé3 = dj.cycle3.relé3;
                    #endregion
                }
                else if (streamToWrite.day6.day == dj.day)
                {
                    #region day 6
                    streamToWrite.day6.cycle1.enable = dj.cycle1.enable;
                    streamToWrite.day6.cycle1.on = dj.cycle1.on;
                    streamToWrite.day6.cycle1.off = dj.cycle1.off;
                    streamToWrite.day6.cycle1.relé1 = dj.cycle1.relé1;
                    streamToWrite.day6.cycle1.relé2 = dj.cycle1.relé2;
                    streamToWrite.day6.cycle1.relé3 = dj.cycle1.relé3;

                    streamToWrite.day6.cycle2.enable = dj.cycle2.enable;
                    streamToWrite.day6.cycle2.on = dj.cycle2.on;
                    streamToWrite.day6.cycle2.off = dj.cycle2.off;
                    streamToWrite.day6.cycle2.relé1 = dj.cycle2.relé1;
                    streamToWrite.day6.cycle2.relé2 = dj.cycle2.relé2;
                    streamToWrite.day6.cycle2.relé3 = dj.cycle2.relé3;

                    streamToWrite.day6.cycle3.enable = dj.cycle3.enable;
                    streamToWrite.day6.cycle3.on = dj.cycle3.on;
                    streamToWrite.day6.cycle3.off = dj.cycle3.off;
                    streamToWrite.day6.cycle3.relé1 = dj.cycle3.relé1;
                    streamToWrite.day6.cycle3.relé2 = dj.cycle3.relé2;
                    streamToWrite.day6.cycle3.relé3 = dj.cycle3.relé3;
                    #endregion
                }
                else if (streamToWrite.day7.day == dj.day)
                { 
                    #region day 7
                    streamToWrite.day7.cycle1.enable = dj.cycle1.enable;
                    streamToWrite.day7.cycle1.on = dj.cycle1.on;
                    streamToWrite.day7.cycle1.off = dj.cycle1.off;
                    streamToWrite.day7.cycle1.relé1 = dj.cycle1.relé1;
                    streamToWrite.day7.cycle1.relé2 = dj.cycle1.relé2;
                    streamToWrite.day7.cycle1.relé3 = dj.cycle1.relé3;

                    streamToWrite.day7.cycle2.enable = dj.cycle2.enable;
                    streamToWrite.day7.cycle2.on = dj.cycle2.on;
                    streamToWrite.day7.cycle2.off = dj.cycle2.off;
                    streamToWrite.day7.cycle2.relé1 = dj.cycle2.relé1;
                    streamToWrite.day7.cycle2.relé2 = dj.cycle2.relé2;
                    streamToWrite.day7.cycle2.relé3 = dj.cycle2.relé3;

                    streamToWrite.day7.cycle3.enable = dj.cycle3.enable;
                    streamToWrite.day7.cycle3.on = dj.cycle3.on;
                    streamToWrite.day7.cycle3.off = dj.cycle3.off;
                    streamToWrite.day7.cycle3.relé1 = dj.cycle3.relé1;
                    streamToWrite.day7.cycle3.relé2 = dj.cycle3.relé2;
                    streamToWrite.day7.cycle3.relé3 = dj.cycle3.relé3;
                    #endregion
                }

                string streamOutput = JsonConvert.SerializeObject(streamToWrite);
                File.WriteAllText(filePath, streamOutput);
                returnStatusOk = true;
            }
            catch (Exception e)
            {
                returnStatusOk = false;
            }

            return returnStatusOk;
        }
    }
}
