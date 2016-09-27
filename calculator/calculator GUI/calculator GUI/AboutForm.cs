using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace calculator_GUI
{
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        }

        private void About_Load(object sender, EventArgs e)
        {
            labelAbout.Text = "本计算器支持运算符：+ - * / ! ^ 运算符";
            labelAuthor.Text = "作者：NoGameNoLife";
        }

    }
}
