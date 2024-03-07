using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UpperPC
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] baudrate = { "4800", "9600", "14400", "19200", "38400", "56000", "57600", "115200", "128000", "230400","256000",
                "512000","921600"};
            comboBox_baudrate.Items.AddRange(baudrate);
            comboBox_baudrate.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string[] port_name = SerialPort.GetPortNames();
            comboBox_serialport.Items.Clear();
            if(port_name == null)
            {
                MessageBox.Show("未检测到串口，请检查连接！", "Error");
                return;
            }
            comboBox_serialport.Items.AddRange(port_name);
            comboBox_serialport.SelectedIndex = 0;
        }

        private void button_open_serial_Click(object sender, EventArgs e)
        {
            try
            {
                if (serialPort1.IsOpen)
                {
                    serialPort1.Close(); // 关闭串口
                    button_open_serial.Text = "打开串口";
                }
                else
                {
                    serialPort1.PortName = comboBox_serialport.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox_baudrate.Text);
                    serialPort1.Open();
                    button_open_serial.Text = "关闭串口";
                }
            }
            catch
            {
                MessageBox.Show("串口打开/关闭失败！", "Error");
            }
        }


        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)//串口数据接收事件
        {

            //如果接收模式为数值接收
            //byte data;
            //data = (byte)serialPort1.ReadByte();//此处需要强制类型转换，将(int)类型数据转换为(byte类型数据，不必考虑是否会丢失数据
            //string str = Convert.ToString(data, 16).ToUpper();//转换为大写十六进制字符串
            //textBox1.AppendText("0x" + (str.Length == 1 ? "0" + str : str) + " ");//空位补“0”   
            //上一句等同为：if(str.Length == 1)
            //                  str = "0" + str;
            //              else 
            //                  str = str;
            //              textBox1.AppendText("0x" + str);
            int len = serialPort1.BytesToRead;//获取可以读取的字节数
            byte[] buff = new byte[len];//创建缓存数据数组
            serialPort1.Read(buff, 0, len);//把数据读取到buff数组
                                            //string str = Encoding.Default.GetString(buff);//Byte值根据ASCII码表转为 String
                                            //Invoke((new Action(() => //C# 3.0以后代替委托的新方法
                                            //{
                                            //    textBox1.AppendText(str);//对话框追加显示数据
                                            //})));
            if (buff[0] != 0xFE) // 来的不是数据帧，而是调试语句
            {
                string str = Encoding.Default.GetString(buff);//Byte值根据ASCII码表转为 String
                textBox1.AppendText(str);//对话框追加显示数据
            }
            else // 来的是数据帧
            {
                for (int i = 0; i < len; i++)
                {
                    string str = Convert.ToString(buff[i], 16).ToUpper();//转换为大写十六进制字符串
                    textBox1.AppendText("0x" + (str.Length == 1 ? "0" + str : str) + " ");//空位补“0” 
                    if(i == 3)
                    {
                        textBox1.Text = Convert.ToString(buff[i] * 0.4);
                    }
                }
            }

        }

        //private void button_send_Click(object sender, EventArgs e)
        //{
        //    byte[] Data = new byte[1];//发送单个字节
        //    if (serialPort1.IsOpen)//判断串口是否打开，如果打开执行下一步操作
        //    {
        //        if (textBox2.Text != "")
        //        {
        //            if (!radioButton1.Checked)//如果发送模式是字符模式
        //            {
        //                try
        //                {
        //                    serialPort1.WriteLine(textBox2.Text);//写数据
        //                }
        //                catch
        //                {
        //                    MessageBox.Show("串口数据写入错误", "错误");//出错提示
        //                    serialPort1.Close();
        //                    button_open_serial.Text = "打开串口";
        //                }
        //            }
        //            else
        //            {
        //                for (int i = 0; i < (textBox2.Text.Length - textBox2.Text.Length % 2) / 2; i++)//取余3运算作用是防止用户输入的字符为奇数个
        //                {
        //                    Data[0] = Convert.ToByte(textBox2.Text.Substring(i * 2, 2), 16);
        //                    serialPort1.Write(Data, 0, 1);//循环发送（如果输入字符为0A0BB,则只发送0A,0B）
        //                }
        //                if (textBox2.Text.Length % 2 != 0)//剩下一位单独处理
        //                {
        //                    Data[0] = Convert.ToByte(textBox2.Text.Substring(textBox2.Text.Length - 1, 1), 16);//单独发送B（0B）
        //                    serialPort1.Write(Data, 0, 1);//发送
        //                }
        //            }
        //        }
        //    }
        //    else
        //    {
        //        MessageBox.Show("串口未打开！", "错误");
        //    }
        //}

        private void button_clear_window_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
        }

        private void button_save_data_Click(object sender, EventArgs e)
        {
            try
            {
                //System.Windows.Forms.FolderBrowserDialog dialog = new System.Windows.Forms.FolderBrowserDialog();
                //dialog.Description = "请选择文件夹";
                //dialog.SelectedPath = "C:\\";
                //if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                //{
                //    Console.WriteLine("选择了文件夹路径：" + dialog.SelectedPath);
                //}
                SaveFileDialog s = new SaveFileDialog();
                //s.Filter = "图像文件|*.jpg|图像文件|*.png|所有文件|*.*";//保存的文件扩展名
                s.Filter = "文本文件|*.txt|所有文件|*.*";//保存的文件扩展名
                s.Title = "保存文件";//对话框标题
                s.DefaultExt = "文本文件|*.txt";//设置文件默认扩展名 
                s.InitialDirectory = @"C:\Users\Administrator\Desktop";//设置保存的初始目录
                if (s.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    // 创建文件，将textBox1中的内容保存到文件中
                    // saveDlg.FileName 是用户指定的文件路径
                    FileStream fs = File.Open(s.FileName,
                        FileMode.Create,
                        FileAccess.Write);
                    StreamWriter sw = new StreamWriter(fs);

                    // 保存textBox1中所有内容（所有行）
                    foreach (string line in textBox1.Lines)
                    {
                        sw.WriteLine(line);
                    }
                    //写入文件
                    sw.Flush();
                    //关闭文件
                    sw.Close();
                    fs.Close();
                    // 提示用户：文件保存的位置和文件名
                    MessageBox.Show("文件已成功保存到" + s.FileName);
                }
            }
            catch
            {
                MessageBox.Show("数据保存失败！", "Error");
            }
        }

    }
}
