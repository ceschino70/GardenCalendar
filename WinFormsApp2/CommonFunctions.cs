using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WinFormsApp2.Structures;

namespace WinFormsApp2
{
    public class CommonFunctions
    {
        public const char separatorCharHoursMinutes = ':';
        public static DateTime convertStringToDateTime(string timeInString)
        {
            DateTime _dateTime = new DateTime(0, 0);

            try
            {
                string[] hourAndMinute = timeInString.Split(separatorCharHoursMinutes);
                Double hoursToAdd = Double.Parse(hourAndMinute[0]);
                Double minutesToAdd = Double.Parse(hourAndMinute[1]);
                _dateTime = _dateTime.AddHours(hoursToAdd);
                _dateTime = _dateTime.AddMinutes(minutesToAdd);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                _dateTime = new DateTime(1, 1, 1, 0, 0, 0);
            }

            return _dateTime;
        }
        public static string convertDateTimeToString(DateTime stringToDateTime)
        {
            //We need the format HH:mm (HH 24 format)
            string _tmp = "";
            _tmp = stringToDateTime.Hour.ToString("00.##") + separatorCharHoursMinutes + stringToDateTime.Minute.ToString("00.##");
            return _tmp;
        }

        public static JSONClass modifyJsonDayToJsonClass (JSONClass jc, DayJSON dj)
        {
            JSONClass jsonlassOutput = new JSONClass();

            //if (dj.day == 1)
            //jc.

            return jsonlassOutput;
        }
    }
}
