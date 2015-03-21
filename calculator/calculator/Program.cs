using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using calcu;

namespace calculator
{
    class Program
    {
        

        static void Main(string[] args)
        {
            string isContinue = "";
            do
            {
                Console.WriteLine("请输入您要计算的表达式（输入在一行之内，支持运算符：+-*/！^和括号）:");
                string expression = Console.ReadLine();
                string newExp = Calculate.delSpace(expression);
                StringBuilder rpn = new StringBuilder();
                if (!Calculate.paren(newExp, 0, 0))
                {
                    Console.WriteLine("你输入的括号不匹配");
                    Console.ReadLine();
                    return;
                }
                double result = Calculate.evalute(newExp, ref rpn);
                if (Calculate.ErrorMessage != "")
                {
                    Console.WriteLine(Calculate.ErrorMessage + ", 请重新输入");
                    Calculate.ErrorMessage = ""; // 清除错误消息
                    continue;
                }
                Console.WriteLine("计算结果是： {0}", result);
                Console.WriteLine("输入(Q)退出, 其他键继续");
                isContinue = Console.ReadLine();
            } while (isContinue.ToLower() != "q");
            Console.WriteLine("已退出！");
            Console.ReadLine();
            return;


        }
    }
}
