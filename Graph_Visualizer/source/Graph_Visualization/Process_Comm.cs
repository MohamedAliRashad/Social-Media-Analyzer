using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph_Visualization
{
    public static class Process_Comm
    {
        public static string Run(string executable, string stdin)
        {
            string retMessage = String.Empty;
            ProcessStartInfo startInfo = new ProcessStartInfo();
            Process p = new Process();

            startInfo.CreateNoWindow = true;
            startInfo.RedirectStandardOutput = true;
            startInfo.RedirectStandardInput = true;

            startInfo.UseShellExecute = false;
            //startInfo.Arguments = "1";
            startInfo.FileName = executable;

            p.StartInfo = startInfo;
            p.Start();

            p.StandardInput.WriteLine(stdin);

            return p.StandardOutput.ReadToEnd();

        }
    }
}
