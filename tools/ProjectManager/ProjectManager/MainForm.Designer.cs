namespace ProjectManager
{
    partial class ManForm
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
            this.textProjectName = new System.Windows.Forms.TextBox();
            this.textCompanyName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.projectHomeDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.buttonCreateProject = new System.Windows.Forms.Button();
            this.flag_CreateTorsionProj = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.labelTotal = new System.Windows.Forms.Label();
            this.textHomeFolder = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonSelectHomeFolder = new System.Windows.Forms.Button();
            this.projectRootDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.SuspendLayout();
            // 
            // textProjectName
            // 
            this.textProjectName.Location = new System.Drawing.Point(163, 6);
            this.textProjectName.Name = "textProjectName";
            this.textProjectName.Size = new System.Drawing.Size(240, 21);
            this.textProjectName.TabIndex = 0;
            this.textProjectName.TextChanged += new System.EventHandler(this.textProjectName_TextChanged);
            // 
            // textCompanyName
            // 
            this.textCompanyName.Location = new System.Drawing.Point(163, 46);
            this.textCompanyName.Name = "textCompanyName";
            this.textCompanyName.Size = new System.Drawing.Size(240, 21);
            this.textCompanyName.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(80, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "Project name";
            // 
            // buttonCreateProject
            // 
            this.buttonCreateProject.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonCreateProject.Location = new System.Drawing.Point(5, 352);
            this.buttonCreateProject.Name = "buttonCreateProject";
            this.buttonCreateProject.Size = new System.Drawing.Size(99, 21);
            this.buttonCreateProject.TabIndex = 7;
            this.buttonCreateProject.Text = "Create Project";
            this.buttonCreateProject.UseVisualStyleBackColor = true;
            this.buttonCreateProject.Click += new System.EventHandler(this.buttonCreateProject_Click);
            // 
            // flag_CreateTorsionProj
            // 
            this.flag_CreateTorsionProj.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.flag_CreateTorsionProj.AutoSize = true;
            this.flag_CreateTorsionProj.Checked = true;
            this.flag_CreateTorsionProj.CheckState = System.Windows.Forms.CheckState.Checked;
            this.flag_CreateTorsionProj.Location = new System.Drawing.Point(10, 331);
            this.flag_CreateTorsionProj.Name = "flag_CreateTorsionProj";
            this.flag_CreateTorsionProj.Size = new System.Drawing.Size(156, 16);
            this.flag_CreateTorsionProj.TabIndex = 6;
            this.flag_CreateTorsionProj.Text = "Create Torsion Project";
            this.flag_CreateTorsionProj.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(80, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "Bundle ID";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // labelTotal
            // 
            this.labelTotal.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelTotal.AutoSize = true;
            this.labelTotal.Location = new System.Drawing.Point(3, 375);
            this.labelTotal.Name = "labelTotal";
            this.labelTotal.Size = new System.Drawing.Size(41, 12);
            this.labelTotal.TabIndex = 6;
            this.labelTotal.Text = "label3";
            this.labelTotal.Visible = false;
            // 
            // textHomeFolder
            // 
            this.textHomeFolder.Location = new System.Drawing.Point(163, 235);
            this.textHomeFolder.Name = "textHomeFolder";
            this.textHomeFolder.Size = new System.Drawing.Size(240, 21);
            this.textHomeFolder.TabIndex = 4;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(81, 197);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(149, 12);
            this.label4.TabIndex = 11;
            this.label4.Text = "Your project home folder";
            // 
            // buttonSelectHomeFolder
            // 
            this.buttonSelectHomeFolder.Location = new System.Drawing.Point(83, 233);
            this.buttonSelectHomeFolder.Name = "buttonSelectHomeFolder";
            this.buttonSelectHomeFolder.Size = new System.Drawing.Size(75, 21);
            this.buttonSelectHomeFolder.TabIndex = 5;
            this.buttonSelectHomeFolder.Text = "Select folder";
            this.buttonSelectHomeFolder.UseVisualStyleBackColor = true;
            this.buttonSelectHomeFolder.Click += new System.EventHandler(this.buttonSelectHomeFolder_Click);
            // 
            // ManForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(523, 391);
            this.Controls.Add(this.buttonSelectHomeFolder);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textHomeFolder);
            this.Controls.Add(this.labelTotal);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.flag_CreateTorsionProj);
            this.Controls.Add(this.buttonCreateProject);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textCompanyName);
            this.Controls.Add(this.textProjectName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ManForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Project Manager for Torque 2D by yurembo";
            this.Load += new System.EventHandler(this.ManForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textProjectName;
        private System.Windows.Forms.TextBox textCompanyName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.FolderBrowserDialog projectHomeDialog;
        private System.Windows.Forms.Button buttonCreateProject;
        private System.Windows.Forms.CheckBox flag_CreateTorsionProj;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelTotal;
        private System.Windows.Forms.TextBox textHomeFolder;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonSelectHomeFolder;
        private System.Windows.Forms.FolderBrowserDialog projectRootDialog;
    }
}

