using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using calcu;

namespace calculator_GUI
{
    public partial class CalcuForm : Form
    {
        public CalcuForm()
        {
            InitializeComponent();
        }
        private void CalcuForm_Load(object sender, EventArgs e)
        {
            textbox.Font = new Font("新宋体", 30);

        }

        // 去除文本框最后一个字符
        private void btnBackspace_Click(object sender, EventArgs e)
        {
            string textTemp = textbox.Text.Remove(textbox.Text.Length - 1);
            textbox.Text = textTemp;
        }

        // 清除文本框
        private void btnClean_Click(object sender, EventArgs e)
        {
            textbox.Clear();
        }

        // 计算结果
        private void bntResult_Click(object sender, EventArgs e)
        {
            string exp = Calculate.delSpace(textbox.Text);
            StringBuilder rpn = new StringBuilder();
            double result = 0;
            if (exp == "")
            {
                MessageBox.Show("请输入你要计算的表达式!", "提示", 
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                
            }
            else if(!Calculate.paren(exp, 0 , 0))
            {
                MessageBox.Show("请输入匹配的括号！", "提示",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                result = Calculate.evalute(exp, ref rpn);
                if (Calculate.ErrorMessage != "")
                {
                    MessageBox.Show(Calculate.ErrorMessage, "提示",
                                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Calculate.ErrorMessage = ""; // 清除错误消息
                }
                else
                {
                    textbox.Text = result.ToString();
                }
            }
        }

        private void btnNum1_Click(object sender, EventArgs e)
        {
            textbox.Text += "1";
        }

        private void btnNum2_Click(object sender, EventArgs e)
        {
            textbox.Text += "2";
        }

        private void btnNum3_Click(object sender, EventArgs e)
        {
            textbox.Text += "3";
        }

        private void btnNum4_Click(object sender, EventArgs e)
        {
            textbox.Text += "4";
        }

        private void btnNum5_Click(object sender, EventArgs e)
        {
            textbox.Text += "5";
        }

        private void btnNum6_Click(object sender, EventArgs e)
        {
            textbox.Text += "6";
        }
        private void btnNum7_Click(object sender, EventArgs e)
        {
            textbox.Text += "7";
        }

        private void btnNum8_Click(object sender, EventArgs e)
        {
            textbox.Text += "8";
        }

        private void btnNum9_Click(object sender, EventArgs e)
        {
            textbox.Text += "9";
        }

        private void btnNum0_Click(object sender, EventArgs e)
        {
            textbox.Text += "0";
        }

        private void btnPoint_Click(object sender, EventArgs e)
        {
            textbox.Text += ".";
        }

        private void btnLeftBracket_Click(object sender, EventArgs e)
        {
            textbox.Text += "(";
        }

        private void bntRightBracket_Click(object sender, EventArgs e)
        {
            textbox.Text += ")";
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            textbox.Text += "+";
        }

        private void btnSub_Click(object sender, EventArgs e)
        {
            textbox.Text += "-";
        }

        private void btnMultiply_Click(object sender, EventArgs e)
        {
            textbox.Text += "*";
        }

        private void btnDivde_Click(object sender, EventArgs e)
        {
            textbox.Text += "/";
        }

        private void btnFactorial_Click(object sender, EventArgs e)
        {
            textbox.Text += "!";
        }

        private void btnPower_Click(object sender, EventArgs e)
        {
            textbox.Text += "^";
        }

        private void menuCopy_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(textbox.Text);
        }

        private void menuPaste_Click(object sender, EventArgs e)
        {
            textbox.Text += Clipboard.GetText();
        }

        private void menuAboutCal_Click(object sender, EventArgs e)
        {
            AboutForm fm = new AboutForm();
            fm.ShowDialog();
        }
    }
}
