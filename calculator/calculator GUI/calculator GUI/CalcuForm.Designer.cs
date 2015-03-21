namespace calculator_GUI
{
    partial class CalcuForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.textbox = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.menuCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPaste = new System.Windows.Forms.ToolStripMenuItem();
            this.menuAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.menuAboutCal = new System.Windows.Forms.ToolStripMenuItem();
            this.btnBackspace = new System.Windows.Forms.Button();
            this.btnClean = new System.Windows.Forms.Button();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnNum7 = new System.Windows.Forms.Button();
            this.btnNum8 = new System.Windows.Forms.Button();
            this.btnNum9 = new System.Windows.Forms.Button();
            this.btnSub = new System.Windows.Forms.Button();
            this.btnNum4 = new System.Windows.Forms.Button();
            this.btnNum5 = new System.Windows.Forms.Button();
            this.btnNum2 = new System.Windows.Forms.Button();
            this.btnNum0 = new System.Windows.Forms.Button();
            this.btnNum1 = new System.Windows.Forms.Button();
            this.btnNum3 = new System.Windows.Forms.Button();
            this.btnNum6 = new System.Windows.Forms.Button();
            this.btnPoint = new System.Windows.Forms.Button();
            this.btnMultiply = new System.Windows.Forms.Button();
            this.btnDivde = new System.Windows.Forms.Button();
            this.btnPower = new System.Windows.Forms.Button();
            this.btnLeftBracket = new System.Windows.Forms.Button();
            this.bntRightBracket = new System.Windows.Forms.Button();
            this.btnFactorial = new System.Windows.Forms.Button();
            this.bntResult = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // textbox
            // 
            this.textbox.Font = new System.Drawing.Font("仿宋", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textbox.Location = new System.Drawing.Point(12, 32);
            this.textbox.Name = "textbox";
            this.textbox.Size = new System.Drawing.Size(249, 30);
            this.textbox.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuEdit,
            this.menuAbout});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(273, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuEdit
            // 
            this.menuEdit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuCopy,
            this.menuPaste});
            this.menuEdit.Name = "menuEdit";
            this.menuEdit.Size = new System.Drawing.Size(59, 21);
            this.menuEdit.Text = "编辑(E)";
            // 
            // menuCopy
            // 
            this.menuCopy.Name = "menuCopy";
            this.menuCopy.Size = new System.Drawing.Size(152, 22);
            this.menuCopy.Text = "复制(C)";
            this.menuCopy.Click += new System.EventHandler(this.menuCopy_Click);
            // 
            // menuPaste
            // 
            this.menuPaste.Name = "menuPaste";
            this.menuPaste.Size = new System.Drawing.Size(152, 22);
            this.menuPaste.Text = "粘贴(V)";
            this.menuPaste.Click += new System.EventHandler(this.menuPaste_Click);
            // 
            // menuAbout
            // 
            this.menuAbout.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuAboutCal});
            this.menuAbout.Name = "menuAbout";
            this.menuAbout.Size = new System.Drawing.Size(60, 21);
            this.menuAbout.Text = "关于(A)";
            // 
            // menuAboutCal
            // 
            this.menuAboutCal.Name = "menuAboutCal";
            this.menuAboutCal.Size = new System.Drawing.Size(152, 22);
            this.menuAboutCal.Text = "关于计算器";
            this.menuAboutCal.Click += new System.EventHandler(this.menuAboutCal_Click);
            // 
            // btnBackspace
            // 
            this.btnBackspace.Location = new System.Drawing.Point(12, 92);
            this.btnBackspace.Name = "btnBackspace";
            this.btnBackspace.Size = new System.Drawing.Size(45, 32);
            this.btnBackspace.TabIndex = 2;
            this.btnBackspace.Text = "←";
            this.btnBackspace.UseVisualStyleBackColor = true;
            this.btnBackspace.Click += new System.EventHandler(this.btnBackspace_Click);
            // 
            // btnClean
            // 
            this.btnClean.Location = new System.Drawing.Point(63, 92);
            this.btnClean.Name = "btnClean";
            this.btnClean.Size = new System.Drawing.Size(45, 32);
            this.btnClean.TabIndex = 4;
            this.btnClean.Text = "C";
            this.btnClean.UseVisualStyleBackColor = true;
            this.btnClean.Click += new System.EventHandler(this.btnClean_Click);
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(165, 130);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(45, 32);
            this.btnAdd.TabIndex = 5;
            this.btnAdd.Text = "+";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnNum7
            // 
            this.btnNum7.Location = new System.Drawing.Point(12, 130);
            this.btnNum7.Name = "btnNum7";
            this.btnNum7.Size = new System.Drawing.Size(45, 32);
            this.btnNum7.TabIndex = 6;
            this.btnNum7.Text = "7";
            this.btnNum7.UseVisualStyleBackColor = true;
            this.btnNum7.Click += new System.EventHandler(this.btnNum7_Click);
            // 
            // btnNum8
            // 
            this.btnNum8.Location = new System.Drawing.Point(63, 130);
            this.btnNum8.Name = "btnNum8";
            this.btnNum8.Size = new System.Drawing.Size(45, 32);
            this.btnNum8.TabIndex = 7;
            this.btnNum8.Text = "8";
            this.btnNum8.UseVisualStyleBackColor = true;
            this.btnNum8.Click += new System.EventHandler(this.btnNum8_Click);
            // 
            // btnNum9
            // 
            this.btnNum9.Location = new System.Drawing.Point(114, 130);
            this.btnNum9.Name = "btnNum9";
            this.btnNum9.Size = new System.Drawing.Size(45, 32);
            this.btnNum9.TabIndex = 8;
            this.btnNum9.Text = "9";
            this.btnNum9.UseVisualStyleBackColor = true;
            this.btnNum9.Click += new System.EventHandler(this.btnNum9_Click);
            // 
            // btnSub
            // 
            this.btnSub.Location = new System.Drawing.Point(216, 130);
            this.btnSub.Name = "btnSub";
            this.btnSub.Size = new System.Drawing.Size(45, 32);
            this.btnSub.TabIndex = 9;
            this.btnSub.Text = "-";
            this.btnSub.UseVisualStyleBackColor = true;
            this.btnSub.Click += new System.EventHandler(this.btnSub_Click);
            // 
            // btnNum4
            // 
            this.btnNum4.Location = new System.Drawing.Point(12, 168);
            this.btnNum4.Name = "btnNum4";
            this.btnNum4.Size = new System.Drawing.Size(45, 32);
            this.btnNum4.TabIndex = 10;
            this.btnNum4.Text = "4";
            this.btnNum4.UseVisualStyleBackColor = true;
            this.btnNum4.Click += new System.EventHandler(this.btnNum4_Click);
            // 
            // btnNum5
            // 
            this.btnNum5.Location = new System.Drawing.Point(63, 168);
            this.btnNum5.Name = "btnNum5";
            this.btnNum5.Size = new System.Drawing.Size(45, 32);
            this.btnNum5.TabIndex = 11;
            this.btnNum5.Text = "5";
            this.btnNum5.UseVisualStyleBackColor = true;
            this.btnNum5.Click += new System.EventHandler(this.btnNum5_Click);
            // 
            // btnNum2
            // 
            this.btnNum2.Location = new System.Drawing.Point(63, 206);
            this.btnNum2.Name = "btnNum2";
            this.btnNum2.Size = new System.Drawing.Size(45, 32);
            this.btnNum2.TabIndex = 12;
            this.btnNum2.Text = "2";
            this.btnNum2.UseVisualStyleBackColor = true;
            this.btnNum2.Click += new System.EventHandler(this.btnNum2_Click);
            // 
            // btnNum0
            // 
            this.btnNum0.Location = new System.Drawing.Point(12, 243);
            this.btnNum0.Name = "btnNum0";
            this.btnNum0.Size = new System.Drawing.Size(96, 32);
            this.btnNum0.TabIndex = 6;
            this.btnNum0.Text = "0";
            this.btnNum0.UseVisualStyleBackColor = true;
            this.btnNum0.Click += new System.EventHandler(this.btnNum0_Click);
            // 
            // btnNum1
            // 
            this.btnNum1.Location = new System.Drawing.Point(12, 206);
            this.btnNum1.Name = "btnNum1";
            this.btnNum1.Size = new System.Drawing.Size(45, 32);
            this.btnNum1.TabIndex = 7;
            this.btnNum1.Text = "1";
            this.btnNum1.UseVisualStyleBackColor = true;
            this.btnNum1.Click += new System.EventHandler(this.btnNum1_Click);
            // 
            // btnNum3
            // 
            this.btnNum3.Location = new System.Drawing.Point(114, 206);
            this.btnNum3.Name = "btnNum3";
            this.btnNum3.Size = new System.Drawing.Size(45, 32);
            this.btnNum3.TabIndex = 8;
            this.btnNum3.Text = "3";
            this.btnNum3.UseVisualStyleBackColor = true;
            this.btnNum3.Click += new System.EventHandler(this.btnNum3_Click);
            // 
            // btnNum6
            // 
            this.btnNum6.Location = new System.Drawing.Point(114, 168);
            this.btnNum6.Name = "btnNum6";
            this.btnNum6.Size = new System.Drawing.Size(45, 32);
            this.btnNum6.TabIndex = 12;
            this.btnNum6.Text = "6";
            this.btnNum6.UseVisualStyleBackColor = true;
            this.btnNum6.Click += new System.EventHandler(this.btnNum6_Click);
            // 
            // btnPoint
            // 
            this.btnPoint.Location = new System.Drawing.Point(114, 243);
            this.btnPoint.Name = "btnPoint";
            this.btnPoint.Size = new System.Drawing.Size(45, 32);
            this.btnPoint.TabIndex = 13;
            this.btnPoint.Text = ".";
            this.btnPoint.UseVisualStyleBackColor = true;
            this.btnPoint.Click += new System.EventHandler(this.btnPoint_Click);
            // 
            // btnMultiply
            // 
            this.btnMultiply.Location = new System.Drawing.Point(165, 168);
            this.btnMultiply.Name = "btnMultiply";
            this.btnMultiply.Size = new System.Drawing.Size(45, 32);
            this.btnMultiply.TabIndex = 14;
            this.btnMultiply.Text = "*";
            this.btnMultiply.UseVisualStyleBackColor = true;
            this.btnMultiply.Click += new System.EventHandler(this.btnMultiply_Click);
            // 
            // btnDivde
            // 
            this.btnDivde.Location = new System.Drawing.Point(215, 168);
            this.btnDivde.Name = "btnDivde";
            this.btnDivde.Size = new System.Drawing.Size(45, 32);
            this.btnDivde.TabIndex = 15;
            this.btnDivde.Text = "/";
            this.btnDivde.UseVisualStyleBackColor = true;
            this.btnDivde.Click += new System.EventHandler(this.btnDivde_Click);
            // 
            // btnPower
            // 
            this.btnPower.Location = new System.Drawing.Point(165, 244);
            this.btnPower.Name = "btnPower";
            this.btnPower.Size = new System.Drawing.Size(45, 32);
            this.btnPower.TabIndex = 16;
            this.btnPower.Text = "^";
            this.btnPower.UseVisualStyleBackColor = true;
            this.btnPower.Click += new System.EventHandler(this.btnPower_Click);
            // 
            // btnLeftBracket
            // 
            this.btnLeftBracket.Location = new System.Drawing.Point(165, 92);
            this.btnLeftBracket.Name = "btnLeftBracket";
            this.btnLeftBracket.Size = new System.Drawing.Size(45, 32);
            this.btnLeftBracket.TabIndex = 17;
            this.btnLeftBracket.Text = "(";
            this.btnLeftBracket.UseVisualStyleBackColor = true;
            this.btnLeftBracket.Click += new System.EventHandler(this.btnLeftBracket_Click);
            // 
            // bntRightBracket
            // 
            this.bntRightBracket.Location = new System.Drawing.Point(216, 92);
            this.bntRightBracket.Name = "bntRightBracket";
            this.bntRightBracket.Size = new System.Drawing.Size(45, 32);
            this.bntRightBracket.TabIndex = 18;
            this.bntRightBracket.Text = ")";
            this.bntRightBracket.UseVisualStyleBackColor = true;
            this.bntRightBracket.Click += new System.EventHandler(this.bntRightBracket_Click);
            // 
            // btnFactorial
            // 
            this.btnFactorial.Location = new System.Drawing.Point(165, 206);
            this.btnFactorial.Name = "btnFactorial";
            this.btnFactorial.Size = new System.Drawing.Size(45, 32);
            this.btnFactorial.TabIndex = 19;
            this.btnFactorial.Text = "!";
            this.btnFactorial.UseVisualStyleBackColor = true;
            this.btnFactorial.Click += new System.EventHandler(this.btnFactorial_Click);
            // 
            // bntResult
            // 
            this.bntResult.Location = new System.Drawing.Point(216, 206);
            this.bntResult.Name = "bntResult";
            this.bntResult.Size = new System.Drawing.Size(45, 69);
            this.bntResult.TabIndex = 20;
            this.bntResult.Text = "=";
            this.bntResult.UseVisualStyleBackColor = true;
            this.bntResult.Click += new System.EventHandler(this.bntResult_Click);
            // 
            // CalcuForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(273, 286);
            this.Controls.Add(this.bntResult);
            this.Controls.Add(this.btnFactorial);
            this.Controls.Add(this.bntRightBracket);
            this.Controls.Add(this.btnLeftBracket);
            this.Controls.Add(this.btnPower);
            this.Controls.Add(this.btnDivde);
            this.Controls.Add(this.btnMultiply);
            this.Controls.Add(this.btnPoint);
            this.Controls.Add(this.btnNum6);
            this.Controls.Add(this.btnNum2);
            this.Controls.Add(this.btnNum5);
            this.Controls.Add(this.btnNum4);
            this.Controls.Add(this.btnNum3);
            this.Controls.Add(this.btnSub);
            this.Controls.Add(this.btnNum1);
            this.Controls.Add(this.btnNum9);
            this.Controls.Add(this.btnNum0);
            this.Controls.Add(this.btnNum8);
            this.Controls.Add(this.btnNum7);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.btnClean);
            this.Controls.Add(this.btnBackspace);
            this.Controls.Add(this.textbox);
            this.Controls.Add(this.menuStrip1);
            this.Name = "CalcuForm";
            this.Text = "计算器";
            this.Load += new System.EventHandler(this.CalcuForm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textbox;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menuEdit;
        private System.Windows.Forms.ToolStripMenuItem menuAbout;
        private System.Windows.Forms.Button btnBackspace;
        private System.Windows.Forms.Button btnClean;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnNum7;
        private System.Windows.Forms.Button btnNum8;
        private System.Windows.Forms.Button btnNum9;
        private System.Windows.Forms.Button btnSub;
        private System.Windows.Forms.Button btnNum4;
        private System.Windows.Forms.Button btnNum5;
        private System.Windows.Forms.Button btnNum2;
        private System.Windows.Forms.Button btnNum0;
        private System.Windows.Forms.Button btnNum1;
        private System.Windows.Forms.Button btnNum3;
        private System.Windows.Forms.Button btnNum6;
        private System.Windows.Forms.Button btnPoint;
        private System.Windows.Forms.Button btnMultiply;
        private System.Windows.Forms.Button btnDivde;
        private System.Windows.Forms.Button btnPower;
        private System.Windows.Forms.Button btnLeftBracket;
        private System.Windows.Forms.Button bntRightBracket;
        private System.Windows.Forms.Button btnFactorial;
        private System.Windows.Forms.Button bntResult;
        private System.Windows.Forms.ToolStripMenuItem menuCopy;
        private System.Windows.Forms.ToolStripMenuItem menuPaste;
        private System.Windows.Forms.ToolStripMenuItem menuAboutCal;
    }
}

