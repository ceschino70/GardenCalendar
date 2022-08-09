using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinFormsApp2.Structures
{
    public class DayJSON
    {
        public int day {get; set;}
        public CycleJSON? cycle1 {get; set;}
        public CycleJSON? cycle2 {get; set;}
        public CycleJSON? cycle3 {get; set;}
    }
}
