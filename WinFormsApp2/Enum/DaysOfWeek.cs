using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinFormsApp2.Enum
{
    internal class DaysOfWeek
    {
        public enum daysOfWeek : int
        {
            Mon = 1,
            Tue = 2,
            Wed = 3,
            Thu = 4,
            Fri = 5,
            Sat = 6,
            Sun = 7,
        }

        static public int extractDayFromName(string textDay)
        {
            int numberOfDay = 0;

            numberOfDay = (int)System.Enum.Parse(typeof(daysOfWeek), textDay);
            extractDayNameFromNuber(numberOfDay);
            return numberOfDay;
        }

        static public string extractDayNameFromNuber (int nameDay)
        {
            var tmp = (daysOfWeek)nameDay;
            string  _dayName = tmp.ToString();
            return _dayName;
        }
    }
}
