using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace calcu
{
    public class Calculate
    {
        const int N_OPTR = 10;
        public enum Operator { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE, ERROR }; //运算符集合
        static char[,] pri = new char[N_OPTR, N_OPTR] { //运算符优先等级 [栈顶] [当前]
           /*              |-------------------- 当 前 运 算 符 --------------------| */
           /*              +      -      *      /      ^      !      (      )      \0 */
           /* --  + */  {  '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>' , 'e'},
           /* |   - */  {  '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>' , 'e'},
           /* 栈  * */  {  '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>' , 'e'},
           /* 顶  / */  {  '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>' , 'e'},
           /* 运  ^ */  {  '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>' , 'e'},
           /* 算  ! */  {  '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>' , 'e'},
           /* 符  ( */  {  '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ' , 'e'},
           /* |   ) */  {  ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ' , 'e'},
           /* -- \0 */  {  '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '=' , 'e'},
           /* -error*/  {  'e',   'e',   'e',   'e',   'e',   'e',   'e',   'e',   'e' , 'e'}
        };

        // 错误消息，用于检查计算过程中是否发生异常
        public static string ErrorMessage = "";

        //去除空格和制表符
        public static string delSpace(string str)
        {
            string newExp = "";
            for (int i = 0; i < str.Count(); i++)
            {
                if (str[i] != ' ' && str[i] != '\t')
                {
                    newExp += str[i];
                }
            }
            return newExp;
        }

        public static Operator optr2rank(char op)
        {
            //由运算符转译出编号
            switch (op)
            {
                case '+': return Operator.ADD; //加
                case '-': return Operator.SUB; //减
                case '*': return Operator.MUL; //乘
                case '/': return Operator.DIV; //除
                case '^': return Operator.POW; //乘方
                case '!': return Operator.FAC; //阶乘
                case '(': return Operator.L_P; //左括号
                case ')': return Operator.R_P; //右括号
                case '\0': return Operator.EOE; //起始符与终止符
                default: return Operator.ERROR; //未知运算符
            }
        }

        // 检查括号是否匹配
        public static bool paren(string exp, int lo, int hi)
        {
            Stack<char> S = new Stack<char>();

            for (int i = 0; i < exp.Length; i++)
            {
                switch (exp[i])
                {
                    case '(':
                    case '[':
                    case '{': S.Push(exp[i]);
                        break;
                    case ')':
                        if ((S.Count == 0) || ('(' != S.Pop()))
                            return false;
                        break;
                    case ']': if ((S.Count == 0) || (']' != S.Pop()))
                            return false;
                        break;
                    case '}': if ((S.Count == 0) || ('{' != S.Pop()))
                            return false;
                        break;
                    default: break;
                }
            }
            return S.Count() == 0;
        }

        // 比较两个运算符等级
        public static char orderBetween(char op1, char op2)
        {
            return pri[Convert.ToInt32(optr2rank(op1)),
                      Convert.ToInt32(optr2rank(op2))];
        }

        // 将字符转化为数字并入栈
        public static void readNumber(ref StringBuilder str, ref Stack<double> num)
        {
            string tempStr = "";
            int i;
            for (i = 0; i < str.Length; i++)
            {
                if (!Char.IsDigit(str[i]))
                    break;
                tempStr += str[i];
            }
            if (tempStr.Count() != 0)
            {
                num.Push(Convert.ToDouble(tempStr));
                str.Remove(0, i);
            }
            return;
        }
        public static double fac(int n) //阶乘
        {
            double f = 1;
            while (n > 1)
            {
                f *= n--;
            }
            return f;
        }
        //一元符运算
        public static double calcu(char op, double num)
        {
            switch (op)
            {
                case '!': return (double)fac((int)num);
                default: return -1;                     //阶乘不能为负，有错误
            }

        }
        //二元运算
        public static double calcu(char op, double num1, double num2)
        {
            switch (op)
            {
                case '+': return num1 + num2;
                case '-': return num1 - num2;
                case '*': return num1 * num2;
                case '/': return num1 / num2;
                case '^': return Math.Pow(num1, num2);
                default: return 0;
            }
        }

        //由表达式计算结果
        public static double evalute(String s, ref StringBuilder RPN)
        {
            StringBuilder str = new StringBuilder(s, 200);
            str.Append('\0');
            Stack<double> opnd = new Stack<double>();  //运算数栈
            Stack<char> optr = new Stack<char>();       //运算符栈
            optr.Push('\0');
            while (!(optr.Count() == 0))
            {
                if (Char.IsDigit(str[0]))
                {
                    readNumber(ref str, ref opnd);
                    RPN.Append(optr.Peek());
                }
                else
                {
                    switch (orderBetween(optr.Peek(), str[0]))
                    {
                        case 'e':
                            {
                                ErrorMessage = "出现未知运算符";
                                return 0;
                            }
                        case '<':
                            optr.Push(str[0]);
                            str.Remove(0, 1);
                            break;
                        case '=':
                            optr.Pop();
                            str.Remove(0, 1);
                            break;
                        case '>':
                            {
                                char op = optr.Pop();
                                RPN.Append(op);
                                if ('!' == op)
                                {
                                    double popnd = opnd.Pop(); //取出一个操作数，
                                    opnd.Push(calcu(op, popnd)); //执行一元运算，结果入栈
                                }
                                else
                                {
                                    //取出两个操作数，执行二元运算，结果入栈
                                    double popnd2 = opnd.Pop();
                                    double popnd1 = opnd.Pop();
                                    opnd.Push(calcu(op, popnd1, popnd2));
                                }
                            }
                            break;
                    }

                }

            }
            return opnd.Pop();
        }
    }
}
