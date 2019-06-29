namespace Graph_Visualization
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.graph = new System.Windows.Forms.PictureBox();
            this.debug = new System.Windows.Forms.Label();
            this.degree_centrality = new System.Windows.Forms.RadioButton();
            this.betweenness_centrality = new System.Windows.Forms.RadioButton();
            this.closeness_centrality = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.graph)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 175);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Show";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(12, 17);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(97, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "Locate ADJ MAT";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.Button2_Click);
            // 
            // graph
            // 
            this.graph.Location = new System.Drawing.Point(143, 17);
            this.graph.Name = "graph";
            this.graph.Size = new System.Drawing.Size(556, 485);
            this.graph.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.graph.TabIndex = 2;
            this.graph.TabStop = false;
            // 
            // debug
            // 
            this.debug.AutoSize = true;
            this.debug.Location = new System.Drawing.Point(48, 248);
            this.debug.Name = "debug";
            this.debug.Size = new System.Drawing.Size(39, 13);
            this.debug.TabIndex = 3;
            this.debug.Text = "Debug";
            this.debug.Click += new System.EventHandler(this.Debug_Click);
            // 
            // degree_centrality
            // 
            this.degree_centrality.AutoSize = true;
            this.degree_centrality.Checked = true;
            this.degree_centrality.Location = new System.Drawing.Point(2, 89);
            this.degree_centrality.Name = "degree_centrality";
            this.degree_centrality.Size = new System.Drawing.Size(112, 17);
            this.degree_centrality.TabIndex = 4;
            this.degree_centrality.TabStop = true;
            this.degree_centrality.Text = "Degree Centerality";
            this.degree_centrality.UseVisualStyleBackColor = true;
            // 
            // betweenness_centrality
            // 
            this.betweenness_centrality.AutoSize = true;
            this.betweenness_centrality.Location = new System.Drawing.Point(2, 135);
            this.betweenness_centrality.Name = "betweenness_centrality";
            this.betweenness_centrality.Size = new System.Drawing.Size(135, 17);
            this.betweenness_centrality.TabIndex = 5;
            this.betweenness_centrality.TabStop = true;
            this.betweenness_centrality.Text = "Betweenness Centrality";
            this.betweenness_centrality.UseVisualStyleBackColor = true;
            // 
            // closeness_centrality
            // 
            this.closeness_centrality.AutoSize = true;
            this.closeness_centrality.Location = new System.Drawing.Point(2, 112);
            this.closeness_centrality.Name = "closeness_centrality";
            this.closeness_centrality.Size = new System.Drawing.Size(119, 17);
            this.closeness_centrality.TabIndex = 6;
            this.closeness_centrality.TabStop = true;
            this.closeness_centrality.Text = "Closeness Centrality";
            this.closeness_centrality.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(711, 514);
            this.Controls.Add(this.closeness_centrality);
            this.Controls.Add(this.betweenness_centrality);
            this.Controls.Add(this.degree_centrality);
            this.Controls.Add(this.debug);
            this.Controls.Add(this.graph);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Graph Visualizer";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.graph)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.PictureBox graph;
        private System.Windows.Forms.Label debug;
        private System.Windows.Forms.RadioButton degree_centrality;
        private System.Windows.Forms.RadioButton betweenness_centrality;
        private System.Windows.Forms.RadioButton closeness_centrality;
    }
}

