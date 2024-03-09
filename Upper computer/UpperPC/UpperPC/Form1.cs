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
using System.Threading;
using System.Collections;

namespace UpperPC
{


    public partial class Form1 : Form
    {
        /* 声明环形缓冲区 */
        const int MAX_BUFFER_LEN = 1024;
        static RingBufferManager receiveRingBuffer = new RingBufferManager(MAX_BUFFER_LEN);

        /* 添加事件 */
        static AutoResetEvent ProcessEvent = new AutoResetEvent(false);

        /* 添加互斥锁 */
        static Mutex mutex = new Mutex();

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
            if (port_name == null)
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

                    Thread processingThread = new Thread(ProcessData);
                    processingThread.Start(); // 线程调度开始

                }
            }
            catch
            {
                MessageBox.Show("串口打开/关闭失败！", "Error");
            }
        }



        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)//串口数据接收事件
        {
            int len = serialPort1.BytesToRead;//获取可以读取的字节数
            byte[] buff = new byte[len];//创建缓存数据数组
            serialPort1.Read(buff, 0, len);


            mutex.WaitOne();// 加锁

            receiveRingBuffer.WriteBuffer(buff); // 写入环形缓冲区

            mutex.ReleaseMutex();// 解锁

            ProcessEvent.Set();// 释放信号量

            //if (buff[0] != 0xFE) // 来的不是数据帧，而是调试语句
            //{
            //    string str = Encoding.Default.GetString(buff);//Byte值根据ASCII码表转为 String
            //    textBox1.AppendText(str);//对话框追加显示数据
            //}
            //else // 来的是数据帧
            //{

            //    for (int i = 0; i < len; i++)
            //    {
            //        string str = Convert.ToString(buff[i], 16).ToUpper();//转换为大写十六进制字符串
            //        textBox1.AppendText("0x" + (str.Length == 1 ? "0" + str : str) + " ");//空位补“0” 
            //        if (i == 2)
            //        {
            //            textBox_three_way_1.Clear();
            //            textBox_three_way_1.Text = Convert.ToString(buff[i] * 0.4);
            //        }
            //    }
            //}

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            byte[] Data = new byte[1];//发送单个字节
            if (serialPort1.IsOpen)//判断串口是否打开，如果打开执行下一步操作
            {
                if (textBox2.Text != "")
                {

                    for (int i = 0; i < (textBox2.Text.Length - textBox2.Text.Length % 2) / 2; i++)//取余3运算作用是防止用户输入的字符为奇数个
                    {
                        Data[0] = Convert.ToByte(textBox2.Text.Substring(i * 2, 2), 16);
                        serialPort1.Write(Data, 0, 1);//循环发送（如果输入字符为0A0BB,则只发送0A,0B）
                    }
                    if (textBox2.Text.Length % 2 != 0)//剩下一位单独处理
                    {
                        Data[0] = Convert.ToByte(textBox2.Text.Substring(textBox2.Text.Length - 1, 1), 16);//单独发送B（0B）
                        serialPort1.Write(Data, 0, 1);//发送
                    }
                }
            }
            else
            {
                MessageBox.Show("串口未打开！", "错误");
            }
        }

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


        /* 对数据进行处理 */
        private void ProcessData()
        {

            while (true)
            {
                ProcessEvent.WaitOne();// 等待事件

                mutex.WaitOne();// 加锁

                byte[] data = new byte[receiveRingBuffer.DataCount];// 创建临时数据数组

                receiveRingBuffer.ReadBuffer(data, 0, data.Length);// 读出并存入

                mutex.ReleaseMutex();// 这个时候解锁即可

                if (data[0] != 0xFE)// 证明这段语句是调试语句，直接打印
                {
                    string str = Encoding.Default.GetString(data);//Byte值根据ASCII码表转为 String
                    textBox1.AppendText(str + "\r\n");//对话框追加显示数据
                }
                else
                {
                    Unpack(data);// 解包
                }



            }

        }

        private void Unpack(Byte[] data)
        {
            int n = data.Length;
            switch(data[1])
            {
                case 0x02:// 传输的数据
                    {
                        if (data[n - 1]!= 0xFF || data[n - 2] != n - 3) break; // 不满足帧要求，丢弃


                        /* 解包的格式如下 */
                        /*
                         *  压缩机数据 + 电子膨胀阀状态 + WPTC1 + WPTC2 + 三通阀状态 + 四通阀状态
                         * 
                         *  所有数据根据结构体的定义顺序进行传输，一共是30字节数据
                         */




                        break;
                    }
                case 0x00:
                    {
                        break;
                    }
                case 0x01:
                    {
                        break;
                    }

            }
        }





        //private void GetFrame(Byte[] data)
        //{
        //    if (data.Length == 0) return;// 如果为空直接返回
        //    int end_pos = Array.IndexOf(data, (Byte)0xFF);// 查看是否有结束符
        //    if (end_pos == -1) // 没找到结束符，证明这段语句是调试语句，直接打印
        //    {
        //        string str = Encoding.Default.GetString(data);//Byte值根据ASCII码表转为 String
        //        textBox1.AppendText(str + "\r\n");//对话框追加显示数据
        //    }
        //    else // 找到了结束符，证实这其中一定有数据帧
        //    {
        //        int start_pos = Array.IndexOf(data, (Byte)0xFE);// 查看是否有开始符
        //        if (start_pos == -1) // 没找到开始符，说明传输错误
        //        {
        //            textBox1.AppendText("传输过程出现错误!");//报错
        //            return; // 直接抛弃这段数据
        //        }
        //        else
        //        {
        //            if(end_pos - start_pos  == data[end_pos - 1]) // 确认帧结构
        //            {

        //            }
        //        }
        //    }
        //    //textBox1.AppendText(pos.ToString());
        //}


    }



}


