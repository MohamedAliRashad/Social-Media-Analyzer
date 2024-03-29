﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Graph_Visualization
{
    public partial class Form1 : Form
    {
        string Adj_mat_file_path, algorithms_dir;

        public Form1()
        {
            InitializeComponent();
            algorithms_dir = @"./centerality_algorithms/";
            Adj_mat_file_path = @"./example_adjacency_matrix.txt";
        }



        private void Button1_Click(object sender, EventArgs e)
        {
            string graphVizString;


            string adj_mat_string = File.ReadAllText(@Adj_mat_file_path);
            string centrality_string, algorithm_name;

            if (closeness_centrality.Checked)
                algorithm_name = "Closeness_Centrality.exe";
            else if (betweenness_centrality.Checked)
                algorithm_name = "Betweenness_Centrality.exe";
            else
                algorithm_name = "Degree_Centrality.exe";

            centrality_string = Process_Comm.Run(algorithms_dir + algorithm_name, adj_mat_string);

            graphVizString = FileDotEngine.Convert_to_dot(adj_mat_string, centrality_string);
            Bitmap bm = FileDotEngine.Run(graphVizString);
            graph.Image = bm;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Debug_Click(object sender, EventArgs e)
        {
            string stdin = System.IO.File.ReadAllText(@Adj_mat_file_path);
            string s = Process_Comm.Run(@"./Directed_Graph.exe", stdin);
            debug.Text = s;
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            var FD = new System.Windows.Forms.OpenFileDialog();
            if (FD.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                Adj_mat_file_path = FD.FileName;
            }
        }
    }
}
