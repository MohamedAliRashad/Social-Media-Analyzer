using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Graph_Visualization
{
    public static class FileDotEngine
    {
        public static Bitmap Run(string dot)
        {
            string executable = @".\external\dot.exe";
            string output = @".\external\tempgraph";
            File.WriteAllText(output, dot);

            System.Diagnostics.Process process = new System.Diagnostics.Process();

            // Stop the process from opening a new window
            process.StartInfo.RedirectStandardOutput = true;
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.CreateNoWindow = true;

            // Setup executable and parameters
            process.StartInfo.FileName = executable;
            process.StartInfo.Arguments = string.Format(@"{0} -Tjpg -O", output);

            // Go
            process.Start();
            // and wait dot.exe to complete and exit
            process.WaitForExit();
            Bitmap bitmap = null; ;
            using (Stream bmpStream = System.IO.File.Open(output + ".jpg", System.IO.FileMode.Open))
            {
                Image image = Image.FromStream(bmpStream);
                bitmap = new Bitmap(image);
            }
            //File.Delete(output);
            //File.Delete(output + ".jpg");
            return bitmap;
        }

        public static string Convert_to_dot(string ADJ_mat_string, string centralities_string)
        {
            string[] lines = Regex.Split(centralities_string, "\r\n|\r|\n");
            int num_vertices = Int32.Parse(ADJ_mat_string.Split(' ')[0]);
            float[] centralities = new float[100];
            float max_centrality = 0;
            float scale = 2;
            string graphVizString = @"graph g{";

            //read centralities and get max centrality
            for (int i = 0; i < num_vertices; i++)
            {
                float x;
                if (!float.TryParse(lines[i], out x)) //this line might contain no value
                    continue;
                
                centralities[i] = x;
                if (x > max_centrality) max_centrality = x;
            }

            
            graphVizString += "{";
            graphVizString += "node[margin=0 fixedsize=true]";

            //declare the nodes names and their sizes depending on their centralities
            for (int i = 0; i < num_vertices; i++)
            {
                float size = (centralities[i] / max_centrality) * scale;
                size = size < 0.4f ? 0.4f : size;
                graphVizString += i + "[width=" + size + " height=" + size + "] ";
            }
            graphVizString += "}";
            
            //lines = System.IO.File.ReadAllLines(ADJ_path);
            lines = Regex.Split(ADJ_mat_string, "\r\n|\r|\n");

            //declare the connections between the nodes
            for (int i = 1; i < lines.Length; i++)
            {
                string[] nums = lines[i].Split(' ');
                graphVizString += nums[0] + "--" + nums[1] + "[label=" + nums[2] + "]; ";
            }

            graphVizString += "}";
            return graphVizString;
        }
    }
}
