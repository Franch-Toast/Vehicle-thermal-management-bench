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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TrayNotify;

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
            comboBox_baudrate.SelectedIndex = 3;

            string[] compressor_status = { "停机", "开机" };
            comboBox_compressor_status.Items.AddRange(compressor_status);
            comboBox_compressor_status.SelectedIndex = 0;

            string[] four_way_valve_status = { "模式1", "模式2" };
            textBox_four_way_1_set.Items.AddRange(four_way_valve_status);
            textBox_four_way_1_set.SelectedIndex = 0;
            textBox_four_way_2_set.Items.AddRange(four_way_valve_status);
            textBox_four_way_2_set.SelectedIndex = 0;



            string[] PTC_heat_level = { "0档", "1档" , "2档", "3档", "4档", "5档", "6档", "7档", "8档", "9档" };
            comboBox_PTC_b_heat_level.Items.AddRange(PTC_heat_level);
            comboBox_PTC_b_heat_level.SelectedIndex = 0;
            comboBox_PTC_m_heat_level.Items.AddRange(PTC_heat_level);
            comboBox_PTC_m_heat_level.SelectedIndex = 0;

            textBox_compressor_speed_set.Text = "0";
            textBox_compressor_limit_power_set.Text = "0";
            textBox_EXV_CurrentPosition_set.Text = "180";
            textBox_three_way_1_set.Text = "100";
            textBox_three_way_2_set.Text = "100";
            textBox_WPTC_b_target_temp_set.Text = "50";
            textBox_WPTC_m_target_temp_set.Text = "50";



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
                    processingThread.IsBackground = true; // 设定为后台线程
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


            try
            {
                mutex.WaitOne();// 加锁
                while (true)
                {


                    //Thread.Sleep(10);
                    byte[] buff = new byte[1];

                    //int len = serialPort1.BytesToRead;//获取可以读取的字节数

                    buff[0] = (byte)serialPort1.ReadByte();


                    

                    receiveRingBuffer.WriteBuffer(buff); // 写入环形缓冲区

                    
                }
            }
            catch
            {

                mutex.ReleaseMutex();// 解锁
                ProcessEvent.Set();// 释放信号量
                return;
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
            
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            //byte[] Data = new byte[1];//发送单个字节
            if (serialPort1.IsOpen)//判断串口是否打开，如果打开执行下一步操作
            {

                // 放到点击按钮方法中
                textBox_compressor_limit_power.Text = textBox_compressor_limit_power_set.Text;

                // 放到点击按钮方法中
                textBox_WPTC_b_target_temp.Text = textBox_WPTC_b_target_temp_set.Text;
                // 放到点击按钮方法中
                textBox_WPTC_m_target_temp.Text = textBox_WPTC_m_target_temp_set.Text;
                textBox_PTC_m_heat_level.Text = comboBox_PTC_m_heat_level.Text;


                Pack();
                //mutex.WaitOne();// 加锁
                //byte[] temp = { 0xFE,0x02,0x00,0x00,0x00,0x00,0x43,0x43,0xB1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x32,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0x00,0x01,0x00,0x1E,0xFF };
                //serialPort1.Write(temp, 0, 34);//发送
                //mutex.ReleaseMutex();

                //if (textBox2.Text != "")
                //{

                //    for (int i = 0; i < (textBox2.Text.Length - textBox2.Text.Length % 2) / 2; i++)//取余3运算作用是防止用户输入的字符为奇数个
                //    {
                //        Data[0] = Convert.ToByte(textBox2.Text.Substring(i * 2, 2), 16);
                //        serialPort1.Write(Data, 0, 1);//循环发送（如果输入字符为0A0BB,则只发送0A,0B）
                //    }
                //    if (textBox2.Text.Length % 2 != 0)//剩下一位单独处理
                //    {
                //        Data[0] = Convert.ToByte(textBox2.Text.Substring(textBox2.Text.Length - 1, 1), 16);//单独发送B（0B）
                //        serialPort1.Write(Data, 0, 1);//发送
                //    }
                //}
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
                
                if (data.Length == 0) 
                    continue;


                if (data[0] != 0xFE)// 证明这段语句是调试语句，直接打印
                {
                    string str = Encoding.Default.GetString(data);//Byte值根据ASCII码表转为 String
                    textBox1.AppendText(str + "\r\n");//对话框追加显示数据
                }
                else
                {

                    int len = data.Length;
                    for (int i = 0; i < len; i++)
                    {
                        string str = Convert.ToString(data[i], 16).ToUpper();//转换为大写十六进制字符串
                        textBox1.AppendText("0x" + (str.Length == 1 ? "0" + str : str) + " ");//空位补“0” 
                        //if (i == 2)
                        //{
                        //    textBox_three_way_1.Clear();
                        //    textBox_three_way_1.Text = Convert.ToString(data[i] * 0.4);
                        //}
                    }


                    Unpack(data);// 解包
                }
                


            }

        }

        private void Unpack(Byte[] data)
        {
            int n = data.Length;
            switch (data[1])
            {
                case 0x02:// 传输的数据
                    {
                        if (data[n - 1] != 0xFF || data[n - 2] != n - 4) break; // 不满足帧要求，丢弃


                        /* 解包的格式如下 */
                        /*
                         *  压缩机数据 + 电子膨胀阀状态 + WPTC1 + WPTC2 + 三通阀状态 + 四通阀状态
                         * 
                         *  所有数据根据结构体的定义顺序进行传输，一共是30字节数据
                         */


                        switch(data[Unpack_index.compressor_status])// 压缩机状态
                        {
                            case (byte)0x00:
                                {
                                    textBox_compressor_status.Text = "未运行";
                                    break;
                                }
                            case (byte)0x01:
                                {
                                    textBox_compressor_status.Text = "全功率";
                                    break;
                                }
                            case (byte)0x02:
                                {
                                    textBox_compressor_status.Text = "限制功率";
                                    break;
                                }
                            default:
                                {
                                    textBox_compressor_status.Text = "Error!";
                                    break;
                                }
                        }

                        textBox_compressor_speed.Text = Convert.ToString(data[Unpack_index.compressor_speed] * 50);// 压缩机转速
                        


                        textBox_temperature_basic_board.Text = Convert.ToString(data[Unpack_index.temperature_basic_board] - 50);
                        textBox_temperature_IGBT.Text = Convert.ToString(data[Unpack_index.temperature_IGBT] - 50);
                        textBox_compressor_voltage.Text = Convert.ToString((data[Unpack_index.compressor_voltage] + data[Unpack_index.compressor_voltage + 1] * 256) * 2);
                        textBox_compressor_current.Text = Convert.ToString((data[Unpack_index.compressor_current + 1] * 256 + data[Unpack_index.compressor_current]) * 0.1);
                        textBox_EXV_CurrentPosition.Text = Convert.ToString(data[Unpack_index.EXV_CurrentPosition + 1] * 256 + data[Unpack_index.EXV_CurrentPosition]);


                        switch (data[Unpack_index.EXV_initial_status])// EXV初始化状态
                        {
                            case (byte)0x00:
                                {
                                    textBox_EXV_initial_status.Text = "未初始化";
                                    break;
                                }
                            case (byte)0x01:
                                {
                                    textBox_EXV_initial_status.Text = "初始化中";
                                    break;
                                }
                            case (byte)0x02:
                                {
                                    textBox_EXV_initial_status.Text = "已初始化";
                                    break;
                                }
                            default:
                                {
                                    textBox_EXV_initial_status.Text = "Error!";
                                    break;
                                }
                        }
                        switch (data[Unpack_index.EXV_status])// EXV状态
                        {
                            case (byte)0x00:
                                {
                                    textBox_EXV_status.Text = "未动作";
                                    break;
                                }
                            case (byte)0x01:
                                {
                                    textBox_EXV_status.Text = "动作中";
                                    break;
                                }
                            default:
                                {
                                    textBox_EXV_status.Text = "Error!";
                                    break;
                                }
                        }



                       
                        textBox_three_way_1.Text = Convert.ToString(data[Unpack_index.three_way_1_status] * 0.4);
                        textBox_three_way_2.Text = Convert.ToString(data[Unpack_index.three_way_2_status] * 0.4);
                        textBox_four_way_1.Text = Convert.ToString(data[Unpack_index.four_way_1_status]);
                        textBox_four_way_2.Text = Convert.ToString(data[Unpack_index.four_way_2_status]);

                        // 注意在发送的时候，需要根据comoBox给出具体数值
                        textBox_PTC_b_heat_level.Text = comboBox_PTC_b_heat_level.Text;

                        textBox_PTC_b_voltage.Text = Convert.ToString(data[Unpack_index.PTC_voltage_b] * 2);
                        textBox_PTC_b_current.Text = Convert.ToString(data[Unpack_index.PTC_current_b] * 0.25);
                        textBox_PTC_b_temp_out.Text = Convert.ToString(data[Unpack_index.PTC_temp_out_b] - 50);
                        textBox_PTC_b_temp_internel.Text = Convert.ToString(data[Unpack_index.PTC_temp_internel_b] - 50);

                        switch (data[Unpack_index.PTC_status_b])// 电池PTC状态
                        {
                            case (byte)0x00:
                                {
                                    textBox_PTC_b_status.Text = "OFF";
                                    break;
                                }
                            case (byte)0x01:
                                {
                                    textBox_PTC_b_status.Text = "ON";
                                    break;
                                }
                            case (byte)0x02:
                                {
                                    textBox_PTC_b_status.Text = "Degraded";
                                    break;
                                }
                            case (byte)0x03:
                                {
                                    textBox_PTC_b_status.Text = "stopped";
                                    break;
                                }
                            case (byte)0x04:
                                {
                                    textBox_PTC_b_status.Text = "shutdown";
                                    break;
                                }
                            case (byte)0x05:
                                {
                                    textBox_PTC_b_status.Text = "shorted";
                                    break;
                                }
                            case (byte)0x06:
                                {
                                    textBox_PTC_b_status.Text = "reset not possible";
                                    break;
                                }
                            default:
                                {
                                    textBox_PTC_b_status.Text = "Error!";
                                    break;
                                }
                        }



                        

                        textBox_PTC_m_voltage.Text = Convert.ToString(data[Unpack_index.PTC_voltage_m] * 2);
                        textBox_PTC_m_current.Text = Convert.ToString(data[Unpack_index.PTC_current_m] * 0.25);
                        textBox_PTC_m_temp_out.Text = Convert.ToString(data[Unpack_index.PTC_temp_out_m] - 50);
                        textBox_PTC_m_temp_internel.Text = Convert.ToString(data[Unpack_index.PTC_temp_internel_m] - 50);

                        switch (data[Unpack_index.PTC_status_m])// 电机PTC状态
                        {
                            case (byte)0x00:
                                {
                                    textBox_PTC_m_status.Text = "OFF";
                                    break;
                                }
                            case (byte)0x01:
                                {
                                    textBox_PTC_m_status.Text = "ON";
                                    break;
                                }
                            case (byte)0x02:
                                {
                                    textBox_PTC_m_status.Text = "Degraded";
                                    break;
                                }
                            case (byte)0x03:
                                {
                                    textBox_PTC_m_status.Text = "stopped";
                                    break;
                                }
                            case (byte)0x04:
                                {
                                    textBox_PTC_m_status.Text = "shutdown";
                                    break;
                                }
                            case (byte)0x05:
                                {
                                    textBox_PTC_m_status.Text = "shorted";
                                    break;
                                }
                            case (byte)0x06:
                                {
                                    textBox_PTC_m_status.Text = "reset not possible";
                                    break;
                                }
                            default:
                                {
                                    textBox_PTC_m_status.Text = "Error!";
                                    break;
                                }
                        }

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


        private void Pack()
        {
            
            byte[] data = new byte[17];
            data[0] = (byte)0xFE;
            data[1] = (byte)0x01;

            try
            {
                /* 压缩机 */

                if (comboBox_compressor_status.Text == "开机")
                {
                    data[2] = (byte)1;
                    
                    data[3] = ((byte)(Convert.ToInt32(textBox_compressor_speed_set.Text) / 50));
                }
                else
                {
                    data[2] = ((byte)0);
                    data[3] = ((byte)0);// 没选择开机则转速给0，默认停机
                }

                data[4] = ((byte)(Convert.ToInt32(textBox_compressor_limit_power_set.Text) / 40));

                /* 电子膨胀阀 */

                data[5] = ((byte)(Convert.ToInt32(textBox_EXV_CurrentPosition_set.Text) / 256));
                data[6] = ((byte)(Convert.ToInt32(textBox_EXV_CurrentPosition_set.Text) % 256));

                /* 三通阀1和2 */

                data[7] = ((byte)(Convert.ToInt32(textBox_three_way_1_set.Text) / 0.4));
                data[8] = ((byte)(Convert.ToInt32(textBox_three_way_2_set.Text) / 0.4));

                /* 四通阀1和2 */

                data[9] = ((byte)(Convert.ToInt32(textBox_four_way_1_set.Text[2]) - 48));// 模式1/2
                data[10] = ((byte)(Convert.ToInt32(textBox_four_way_2_set.Text[2]) - 48));

                /* 电池PTC */
                data[11] = ((byte)(Convert.ToInt32(Convert.ToString(comboBox_PTC_b_heat_level.Text[0])) * 10 + 3));// 根据挡位输出加热等级数值
                data[12] = ((byte)(Convert.ToInt32(textBox_WPTC_b_target_temp_set.Text)));


                /* 电机PTC */
                data[13] = ((byte)(Convert.ToInt32(Convert.ToString(comboBox_PTC_m_heat_level.Text[0])) * 10 + 3));// 根据挡位输出加热等级数值
                data[14] = ((byte)(Convert.ToInt32(textBox_WPTC_m_target_temp_set.Text)));
                
                data[15] = ((byte)13);
                data[16] = ((byte)0xFF);

                serialPort1.Write(data, 0, data.Length);

            }
            catch
            {
                MessageBox.Show("输入有误！");
            }
        }




        static class Unpack_index
        {

            public const byte compressor_status = 2;       // 压缩机开启状态
            public const byte compressor_fault_status = 3; // 压缩机故障状态
            public const byte compressor_speed = 4;        // 压缩机转速
            public const byte compressor_limit_power = 5;  // 压缩机允许最大功率
            public const byte temperature_basic_board = 6; // 基板温度
            public const byte temperature_IGBT = 7;        // IGBT温度
            public const byte compressor_voltage = 8;     // 压缩机供电电压,uint16
            public const byte compressor_current = 10;     // 压缩机电流,uint16
            public const byte EXV_CurrentPosition = 12; // EXV膨胀阀开度
            public const byte EXV_initial_status = 14;   // EXV的初始化状态
            public const byte EXV_status = 15;           // EXV的运行状态

            public const byte PTC_current_b = 16;       // PTC电流_电池
            public const byte PTC_voltage_b = 17;       // PTC电压_电池
            public const byte PTC_temp_out_b = 18;      // PTC的出口温度_电池
            public const byte PTC_temp_internel_b = 19; // PTC的内部温度_电池
            public const byte PTC_status_b = 20;        // PTC工作状态_电池
            public const byte PTC_heat_level_b = 21;    // PTC加热挡位_电池

            public const byte PTC_current_m = 22;       // PTC电流_电机
            public const byte PTC_voltage_m = 23;       // PTC电压_电机
            public const byte PTC_temp_out_m = 24;      // PTC的出口温度_电机
            public const byte PTC_temp_internel_m = 25; // PTC的内部温度_电机
            public const byte PTC_status_m = 26;        // PTC工作状态_电机
            public const byte PTC_heat_level_m = 27;    // PTC加热挡位_电机

            public const byte three_way_1_status = 28;
            public const byte three_way_2_status = 29;

            public const byte four_way_1_status = 30;
            public const byte four_way_2_status = 31;

        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] shutdown_message = {0xFE,0x00,0x00,0xFF};
            
            serialPort1.Write(shutdown_message, 0, 4);
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


