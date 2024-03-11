namespace UpperPC
{
    partial class Form1
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button_scan_serial = new System.Windows.Forms.Button();
            this.comboBox_serialport = new System.Windows.Forms.ComboBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.comboBox_baudrate = new System.Windows.Forms.ComboBox();
            this.button_open_serial = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button_clear_window = new System.Windows.Forms.Button();
            this.button_save_data = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.textBox_three_way_1 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox_three_way_2 = new System.Windows.Forms.TextBox();
            this.textBox_compressor_status = new System.Windows.Forms.TextBox();
            this.textBox_compressor_speed = new System.Windows.Forms.TextBox();
            this.textBox_compressor_limit_power = new System.Windows.Forms.TextBox();
            this.textBox_temperature_basic_board = new System.Windows.Forms.TextBox();
            this.textBox_temperature_IGBT = new System.Windows.Forms.TextBox();
            this.textBox_compressor_voltage = new System.Windows.Forms.TextBox();
            this.textBox_compressor_current = new System.Windows.Forms.TextBox();
            this.textBox_EXV_CurrentPosition = new System.Windows.Forms.TextBox();
            this.textBox_EXV_initial_status = new System.Windows.Forms.TextBox();
            this.textBox_EXV_status = new System.Windows.Forms.TextBox();
            this.textBox_four_way_1 = new System.Windows.Forms.TextBox();
            this.textBox_four_way_2 = new System.Windows.Forms.TextBox();
            this.textBox_PTC_m_voltage = new System.Windows.Forms.TextBox();
            this.textBox_PTC_m_current = new System.Windows.Forms.TextBox();
            this.textBox_PTC_m_temp_out = new System.Windows.Forms.TextBox();
            this.textBox_PTC_m_temp_internel = new System.Windows.Forms.TextBox();
            this.textBox_PTC_m_status = new System.Windows.Forms.TextBox();
            this.comboBox_compressor_status = new System.Windows.Forms.ComboBox();
            this.textBox_compressor_speed_set = new System.Windows.Forms.TextBox();
            this.textBox_compressor_limit_power_set = new System.Windows.Forms.TextBox();
            this.textBox_EXV_CurrentPosition_set = new System.Windows.Forms.TextBox();
            this.textBox_three_way_1_set = new System.Windows.Forms.TextBox();
            this.textBox_three_way_2_set = new System.Windows.Forms.TextBox();
            this.textBox_four_way_1_set = new System.Windows.Forms.ComboBox();
            this.textBox_four_way_2_set = new System.Windows.Forms.ComboBox();
            this.textBox_PTC_b_heat_level = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.textBox_PTC_b_status = new System.Windows.Forms.TextBox();
            this.textBox_PTC_b_temp_internel = new System.Windows.Forms.TextBox();
            this.textBox_PTC_b_temp_out = new System.Windows.Forms.TextBox();
            this.textBox_PTC_b_current = new System.Windows.Forms.TextBox();
            this.textBox_PTC_b_voltage = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.comboBox_PTC_b_heat_level = new System.Windows.Forms.ComboBox();
            this.textBox_WPTC_b_target_temp = new System.Windows.Forms.TextBox();
            this.label29 = new System.Windows.Forms.Label();
            this.textBox_WPTC_m_target_temp = new System.Windows.Forms.TextBox();
            this.label27 = new System.Windows.Forms.Label();
            this.comboBox_PTC_m_heat_level = new System.Windows.Forms.ComboBox();
            this.textBox_PTC_m_heat_level = new System.Windows.Forms.TextBox();
            this.label30 = new System.Windows.Forms.Label();
            this.textBox_WPTC_m_target_temp_set = new System.Windows.Forms.TextBox();
            this.textBox_WPTC_b_target_temp_set = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.SuspendLayout();
            // 
            // button_scan_serial
            // 
            this.button_scan_serial.Location = new System.Drawing.Point(244, 39);
            this.button_scan_serial.Name = "button_scan_serial";
            this.button_scan_serial.Size = new System.Drawing.Size(110, 37);
            this.button_scan_serial.TabIndex = 0;
            this.button_scan_serial.Text = "扫描串口";
            this.button_scan_serial.UseVisualStyleBackColor = true;
            this.button_scan_serial.Click += new System.EventHandler(this.button1_Click);
            // 
            // comboBox_serialport
            // 
            this.comboBox_serialport.FormattingEnabled = true;
            this.comboBox_serialport.Location = new System.Drawing.Point(95, 45);
            this.comboBox_serialport.Name = "comboBox_serialport";
            this.comboBox_serialport.Size = new System.Drawing.Size(121, 26);
            this.comboBox_serialport.TabIndex = 1;
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 119600;
            this.serialPort1.ReadTimeout = 5;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.port_DataReceived);
            // 
            // comboBox_baudrate
            // 
            this.comboBox_baudrate.FormattingEnabled = true;
            this.comboBox_baudrate.Location = new System.Drawing.Point(95, 107);
            this.comboBox_baudrate.Name = "comboBox_baudrate";
            this.comboBox_baudrate.Size = new System.Drawing.Size(121, 26);
            this.comboBox_baudrate.TabIndex = 2;
            // 
            // button_open_serial
            // 
            this.button_open_serial.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_open_serial.ForeColor = System.Drawing.Color.Red;
            this.button_open_serial.Location = new System.Drawing.Point(244, 101);
            this.button_open_serial.Name = "button_open_serial";
            this.button_open_serial.Size = new System.Drawing.Size(110, 37);
            this.button_open_serial.TabIndex = 3;
            this.button_open_serial.Text = "打开串口";
            this.button_open_serial.UseVisualStyleBackColor = true;
            this.button_open_serial.Click += new System.EventHandler(this.button_open_serial_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(21, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 18);
            this.label1.TabIndex = 4;
            this.label1.Text = "串口号";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(21, 110);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 18);
            this.label2.TabIndex = 5;
            this.label2.Text = "波特率";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(24, 163);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox1.Size = new System.Drawing.Size(330, 527);
            this.textBox1.TabIndex = 6;
            // 
            // button_clear_window
            // 
            this.button_clear_window.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_clear_window.ForeColor = System.Drawing.Color.Black;
            this.button_clear_window.Location = new System.Drawing.Point(244, 712);
            this.button_clear_window.Name = "button_clear_window";
            this.button_clear_window.Size = new System.Drawing.Size(110, 43);
            this.button_clear_window.TabIndex = 15;
            this.button_clear_window.Text = "清空窗口";
            this.button_clear_window.UseVisualStyleBackColor = true;
            this.button_clear_window.Click += new System.EventHandler(this.button_clear_window_Click);
            // 
            // button_save_data
            // 
            this.button_save_data.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_save_data.ForeColor = System.Drawing.Color.Black;
            this.button_save_data.Location = new System.Drawing.Point(24, 712);
            this.button_save_data.Name = "button_save_data";
            this.button_save_data.Size = new System.Drawing.Size(110, 43);
            this.button_save_data.TabIndex = 16;
            this.button_save_data.Text = "保存数据";
            this.button_save_data.UseVisualStyleBackColor = true;
            this.button_save_data.Click += new System.EventHandler(this.button_save_data_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(413, 39);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(134, 18);
            this.label3.TabIndex = 17;
            this.label3.Text = "压缩机开启状态";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(449, 78);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(98, 18);
            this.label4.TabIndex = 18;
            this.label4.Text = "压缩机转速";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(377, 120);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(170, 18);
            this.label5.TabIndex = 19;
            this.label5.Text = "压缩机允许最大功率";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(413, 163);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(134, 18);
            this.label6.TabIndex = 20;
            this.label6.Text = "压缩机基板温度";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(413, 206);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(134, 18);
            this.label7.TabIndex = 21;
            this.label7.Text = "压缩机IGBT温度";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(413, 249);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(134, 18);
            this.label8.TabIndex = 22;
            this.label8.Text = "压缩机供电电压";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(413, 293);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(134, 18);
            this.label9.TabIndex = 23;
            this.label9.Text = "压缩机供电电流";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(476, 392);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(71, 18);
            this.label10.TabIndex = 24;
            this.label10.Text = "EXV开度";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(422, 430);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(125, 18);
            this.label11.TabIndex = 25;
            this.label11.Text = "EXV初始化状态";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(440, 472);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(107, 18);
            this.label12.TabIndex = 26;
            this.label12.Text = "EXV运行状态";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(431, 543);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(116, 18);
            this.label13.TabIndex = 27;
            this.label13.Text = "三通阀#1开度";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(431, 585);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(116, 18);
            this.label14.TabIndex = 28;
            this.label14.Text = "三通阀#2开度";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(431, 692);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(116, 18);
            this.label15.TabIndex = 30;
            this.label15.Text = "四通阀#2状态";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(431, 650);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(116, 18);
            this.label16.TabIndex = 29;
            this.label16.Text = "四通阀#1状态";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(929, 641);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(116, 18);
            this.label22.TabIndex = 40;
            this.label22.Text = "WPTC工作状态";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(929, 598);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(116, 18);
            this.label23.TabIndex = 39;
            this.label23.Text = "WPTC内部温度";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(929, 555);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(116, 18);
            this.label24.TabIndex = 38;
            this.label24.Text = "WPTC出口温度";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(965, 513);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(80, 18);
            this.label25.TabIndex = 37;
            this.label25.Text = "WPTC电流";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(965, 474);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(80, 18);
            this.label26.TabIndex = 36;
            this.label26.Text = "WPTC电压";
            // 
            // textBox_three_way_1
            // 
            this.textBox_three_way_1.Location = new System.Drawing.Point(573, 540);
            this.textBox_three_way_1.Name = "textBox_three_way_1";
            this.textBox_three_way_1.ReadOnly = true;
            this.textBox_three_way_1.Size = new System.Drawing.Size(100, 28);
            this.textBox_three_way_1.TabIndex = 41;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.ForeColor = System.Drawing.Color.Black;
            this.button1.Location = new System.Drawing.Point(1198, 732);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(110, 43);
            this.button1.TabIndex = 42;
            this.button1.Text = "确认执行";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(850, 678);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox2.Size = new System.Drawing.Size(330, 97);
            this.textBox2.TabIndex = 43;
            // 
            // textBox_three_way_2
            // 
            this.textBox_three_way_2.Location = new System.Drawing.Point(573, 582);
            this.textBox_three_way_2.Name = "textBox_three_way_2";
            this.textBox_three_way_2.ReadOnly = true;
            this.textBox_three_way_2.Size = new System.Drawing.Size(100, 28);
            this.textBox_three_way_2.TabIndex = 44;
            // 
            // textBox_compressor_status
            // 
            this.textBox_compressor_status.Location = new System.Drawing.Point(573, 36);
            this.textBox_compressor_status.Name = "textBox_compressor_status";
            this.textBox_compressor_status.ReadOnly = true;
            this.textBox_compressor_status.Size = new System.Drawing.Size(100, 28);
            this.textBox_compressor_status.TabIndex = 45;
            // 
            // textBox_compressor_speed
            // 
            this.textBox_compressor_speed.Location = new System.Drawing.Point(573, 75);
            this.textBox_compressor_speed.Name = "textBox_compressor_speed";
            this.textBox_compressor_speed.ReadOnly = true;
            this.textBox_compressor_speed.Size = new System.Drawing.Size(100, 28);
            this.textBox_compressor_speed.TabIndex = 46;
            // 
            // textBox_compressor_limit_power
            // 
            this.textBox_compressor_limit_power.Location = new System.Drawing.Point(573, 117);
            this.textBox_compressor_limit_power.Name = "textBox_compressor_limit_power";
            this.textBox_compressor_limit_power.ReadOnly = true;
            this.textBox_compressor_limit_power.Size = new System.Drawing.Size(100, 28);
            this.textBox_compressor_limit_power.TabIndex = 47;
            // 
            // textBox_temperature_basic_board
            // 
            this.textBox_temperature_basic_board.Location = new System.Drawing.Point(573, 160);
            this.textBox_temperature_basic_board.Name = "textBox_temperature_basic_board";
            this.textBox_temperature_basic_board.ReadOnly = true;
            this.textBox_temperature_basic_board.Size = new System.Drawing.Size(100, 28);
            this.textBox_temperature_basic_board.TabIndex = 48;
            // 
            // textBox_temperature_IGBT
            // 
            this.textBox_temperature_IGBT.Location = new System.Drawing.Point(573, 203);
            this.textBox_temperature_IGBT.Name = "textBox_temperature_IGBT";
            this.textBox_temperature_IGBT.ReadOnly = true;
            this.textBox_temperature_IGBT.Size = new System.Drawing.Size(100, 28);
            this.textBox_temperature_IGBT.TabIndex = 49;
            // 
            // textBox_compressor_voltage
            // 
            this.textBox_compressor_voltage.Location = new System.Drawing.Point(573, 239);
            this.textBox_compressor_voltage.Name = "textBox_compressor_voltage";
            this.textBox_compressor_voltage.ReadOnly = true;
            this.textBox_compressor_voltage.Size = new System.Drawing.Size(100, 28);
            this.textBox_compressor_voltage.TabIndex = 50;
            // 
            // textBox_compressor_current
            // 
            this.textBox_compressor_current.Location = new System.Drawing.Point(573, 290);
            this.textBox_compressor_current.Name = "textBox_compressor_current";
            this.textBox_compressor_current.ReadOnly = true;
            this.textBox_compressor_current.Size = new System.Drawing.Size(100, 28);
            this.textBox_compressor_current.TabIndex = 51;
            // 
            // textBox_EXV_CurrentPosition
            // 
            this.textBox_EXV_CurrentPosition.Location = new System.Drawing.Point(573, 389);
            this.textBox_EXV_CurrentPosition.Name = "textBox_EXV_CurrentPosition";
            this.textBox_EXV_CurrentPosition.ReadOnly = true;
            this.textBox_EXV_CurrentPosition.Size = new System.Drawing.Size(100, 28);
            this.textBox_EXV_CurrentPosition.TabIndex = 52;
            // 
            // textBox_EXV_initial_status
            // 
            this.textBox_EXV_initial_status.Location = new System.Drawing.Point(573, 427);
            this.textBox_EXV_initial_status.Name = "textBox_EXV_initial_status";
            this.textBox_EXV_initial_status.ReadOnly = true;
            this.textBox_EXV_initial_status.Size = new System.Drawing.Size(100, 28);
            this.textBox_EXV_initial_status.TabIndex = 53;
            // 
            // textBox_EXV_status
            // 
            this.textBox_EXV_status.Location = new System.Drawing.Point(573, 469);
            this.textBox_EXV_status.Name = "textBox_EXV_status";
            this.textBox_EXV_status.ReadOnly = true;
            this.textBox_EXV_status.Size = new System.Drawing.Size(100, 28);
            this.textBox_EXV_status.TabIndex = 54;
            // 
            // textBox_four_way_1
            // 
            this.textBox_four_way_1.Location = new System.Drawing.Point(573, 647);
            this.textBox_four_way_1.Name = "textBox_four_way_1";
            this.textBox_four_way_1.ReadOnly = true;
            this.textBox_four_way_1.Size = new System.Drawing.Size(100, 28);
            this.textBox_four_way_1.TabIndex = 55;
            // 
            // textBox_four_way_2
            // 
            this.textBox_four_way_2.Location = new System.Drawing.Point(573, 689);
            this.textBox_four_way_2.Name = "textBox_four_way_2";
            this.textBox_four_way_2.ReadOnly = true;
            this.textBox_four_way_2.Size = new System.Drawing.Size(100, 28);
            this.textBox_four_way_2.TabIndex = 56;
            // 
            // textBox_PTC_m_voltage
            // 
            this.textBox_PTC_m_voltage.Location = new System.Drawing.Point(1069, 471);
            this.textBox_PTC_m_voltage.Name = "textBox_PTC_m_voltage";
            this.textBox_PTC_m_voltage.ReadOnly = true;
            this.textBox_PTC_m_voltage.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_m_voltage.TabIndex = 62;
            // 
            // textBox_PTC_m_current
            // 
            this.textBox_PTC_m_current.Location = new System.Drawing.Point(1069, 510);
            this.textBox_PTC_m_current.Name = "textBox_PTC_m_current";
            this.textBox_PTC_m_current.ReadOnly = true;
            this.textBox_PTC_m_current.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_m_current.TabIndex = 63;
            // 
            // textBox_PTC_m_temp_out
            // 
            this.textBox_PTC_m_temp_out.Location = new System.Drawing.Point(1069, 552);
            this.textBox_PTC_m_temp_out.Name = "textBox_PTC_m_temp_out";
            this.textBox_PTC_m_temp_out.ReadOnly = true;
            this.textBox_PTC_m_temp_out.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_m_temp_out.TabIndex = 64;
            // 
            // textBox_PTC_m_temp_internel
            // 
            this.textBox_PTC_m_temp_internel.Location = new System.Drawing.Point(1069, 595);
            this.textBox_PTC_m_temp_internel.Name = "textBox_PTC_m_temp_internel";
            this.textBox_PTC_m_temp_internel.ReadOnly = true;
            this.textBox_PTC_m_temp_internel.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_m_temp_internel.TabIndex = 65;
            // 
            // textBox_PTC_m_status
            // 
            this.textBox_PTC_m_status.Location = new System.Drawing.Point(1069, 638);
            this.textBox_PTC_m_status.Name = "textBox_PTC_m_status";
            this.textBox_PTC_m_status.ReadOnly = true;
            this.textBox_PTC_m_status.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_m_status.TabIndex = 66;
            // 
            // comboBox_compressor_status
            // 
            this.comboBox_compressor_status.FormattingEnabled = true;
            this.comboBox_compressor_status.Location = new System.Drawing.Point(703, 36);
            this.comboBox_compressor_status.Name = "comboBox_compressor_status";
            this.comboBox_compressor_status.Size = new System.Drawing.Size(100, 26);
            this.comboBox_compressor_status.TabIndex = 67;
            // 
            // textBox_compressor_speed_set
            // 
            this.textBox_compressor_speed_set.Location = new System.Drawing.Point(703, 75);
            this.textBox_compressor_speed_set.Name = "textBox_compressor_speed_set";
            this.textBox_compressor_speed_set.Size = new System.Drawing.Size(100, 28);
            this.textBox_compressor_speed_set.TabIndex = 68;
            // 
            // textBox_compressor_limit_power_set
            // 
            this.textBox_compressor_limit_power_set.Location = new System.Drawing.Point(703, 117);
            this.textBox_compressor_limit_power_set.Name = "textBox_compressor_limit_power_set";
            this.textBox_compressor_limit_power_set.Size = new System.Drawing.Size(100, 28);
            this.textBox_compressor_limit_power_set.TabIndex = 69;
            // 
            // textBox_EXV_CurrentPosition_set
            // 
            this.textBox_EXV_CurrentPosition_set.Location = new System.Drawing.Point(703, 389);
            this.textBox_EXV_CurrentPosition_set.Name = "textBox_EXV_CurrentPosition_set";
            this.textBox_EXV_CurrentPosition_set.Size = new System.Drawing.Size(100, 28);
            this.textBox_EXV_CurrentPosition_set.TabIndex = 70;
            // 
            // textBox_three_way_1_set
            // 
            this.textBox_three_way_1_set.Location = new System.Drawing.Point(703, 540);
            this.textBox_three_way_1_set.Name = "textBox_three_way_1_set";
            this.textBox_three_way_1_set.Size = new System.Drawing.Size(100, 28);
            this.textBox_three_way_1_set.TabIndex = 71;
            // 
            // textBox_three_way_2_set
            // 
            this.textBox_three_way_2_set.Location = new System.Drawing.Point(703, 582);
            this.textBox_three_way_2_set.Name = "textBox_three_way_2_set";
            this.textBox_three_way_2_set.Size = new System.Drawing.Size(100, 28);
            this.textBox_three_way_2_set.TabIndex = 72;
            // 
            // textBox_four_way_1_set
            // 
            this.textBox_four_way_1_set.FormattingEnabled = true;
            this.textBox_four_way_1_set.Location = new System.Drawing.Point(703, 647);
            this.textBox_four_way_1_set.Name = "textBox_four_way_1_set";
            this.textBox_four_way_1_set.Size = new System.Drawing.Size(100, 26);
            this.textBox_four_way_1_set.TabIndex = 73;
            // 
            // textBox_four_way_2_set
            // 
            this.textBox_four_way_2_set.FormattingEnabled = true;
            this.textBox_four_way_2_set.Location = new System.Drawing.Point(703, 689);
            this.textBox_four_way_2_set.Name = "textBox_four_way_2_set";
            this.textBox_four_way_2_set.Size = new System.Drawing.Size(100, 26);
            this.textBox_four_way_2_set.TabIndex = 74;
            // 
            // textBox_PTC_b_heat_level
            // 
            this.textBox_PTC_b_heat_level.Location = new System.Drawing.Point(1069, 75);
            this.textBox_PTC_b_heat_level.Name = "textBox_PTC_b_heat_level";
            this.textBox_PTC_b_heat_level.ReadOnly = true;
            this.textBox_PTC_b_heat_level.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_b_heat_level.TabIndex = 88;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(929, 78);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(116, 18);
            this.label17.TabIndex = 87;
            this.label17.Text = "WPTC加热挡位";
            // 
            // textBox_PTC_b_status
            // 
            this.textBox_PTC_b_status.Location = new System.Drawing.Point(1069, 285);
            this.textBox_PTC_b_status.Name = "textBox_PTC_b_status";
            this.textBox_PTC_b_status.ReadOnly = true;
            this.textBox_PTC_b_status.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_b_status.TabIndex = 86;
            // 
            // textBox_PTC_b_temp_internel
            // 
            this.textBox_PTC_b_temp_internel.Location = new System.Drawing.Point(1069, 242);
            this.textBox_PTC_b_temp_internel.Name = "textBox_PTC_b_temp_internel";
            this.textBox_PTC_b_temp_internel.ReadOnly = true;
            this.textBox_PTC_b_temp_internel.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_b_temp_internel.TabIndex = 85;
            // 
            // textBox_PTC_b_temp_out
            // 
            this.textBox_PTC_b_temp_out.Location = new System.Drawing.Point(1069, 199);
            this.textBox_PTC_b_temp_out.Name = "textBox_PTC_b_temp_out";
            this.textBox_PTC_b_temp_out.ReadOnly = true;
            this.textBox_PTC_b_temp_out.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_b_temp_out.TabIndex = 84;
            // 
            // textBox_PTC_b_current
            // 
            this.textBox_PTC_b_current.Location = new System.Drawing.Point(1069, 157);
            this.textBox_PTC_b_current.Name = "textBox_PTC_b_current";
            this.textBox_PTC_b_current.ReadOnly = true;
            this.textBox_PTC_b_current.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_b_current.TabIndex = 83;
            // 
            // textBox_PTC_b_voltage
            // 
            this.textBox_PTC_b_voltage.Location = new System.Drawing.Point(1069, 118);
            this.textBox_PTC_b_voltage.Name = "textBox_PTC_b_voltage";
            this.textBox_PTC_b_voltage.ReadOnly = true;
            this.textBox_PTC_b_voltage.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_b_voltage.TabIndex = 82;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(929, 288);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(116, 18);
            this.label18.TabIndex = 81;
            this.label18.Text = "WPTC工作状态";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(929, 245);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(116, 18);
            this.label19.TabIndex = 80;
            this.label19.Text = "WPTC内部温度";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(929, 202);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(116, 18);
            this.label20.TabIndex = 79;
            this.label20.Text = "WPTC出口温度";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(965, 160);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(80, 18);
            this.label21.TabIndex = 78;
            this.label21.Text = "WPTC电流";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(965, 121);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(80, 18);
            this.label28.TabIndex = 77;
            this.label28.Text = "WPTC电压";
            // 
            // comboBox_PTC_b_heat_level
            // 
            this.comboBox_PTC_b_heat_level.FormattingEnabled = true;
            this.comboBox_PTC_b_heat_level.Location = new System.Drawing.Point(1198, 75);
            this.comboBox_PTC_b_heat_level.Name = "comboBox_PTC_b_heat_level";
            this.comboBox_PTC_b_heat_level.Size = new System.Drawing.Size(100, 26);
            this.comboBox_PTC_b_heat_level.TabIndex = 89;
            // 
            // textBox_WPTC_b_target_temp
            // 
            this.textBox_WPTC_b_target_temp.Location = new System.Drawing.Point(1069, 36);
            this.textBox_WPTC_b_target_temp.Name = "textBox_WPTC_b_target_temp";
            this.textBox_WPTC_b_target_temp.ReadOnly = true;
            this.textBox_WPTC_b_target_temp.Size = new System.Drawing.Size(100, 28);
            this.textBox_WPTC_b_target_temp.TabIndex = 92;
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(929, 39);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(116, 18);
            this.label29.TabIndex = 91;
            this.label29.Text = "WPTC目标温度";
            // 
            // textBox_WPTC_m_target_temp
            // 
            this.textBox_WPTC_m_target_temp.Location = new System.Drawing.Point(1069, 389);
            this.textBox_WPTC_m_target_temp.Name = "textBox_WPTC_m_target_temp";
            this.textBox_WPTC_m_target_temp.ReadOnly = true;
            this.textBox_WPTC_m_target_temp.Size = new System.Drawing.Size(100, 28);
            this.textBox_WPTC_m_target_temp.TabIndex = 98;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(929, 392);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(116, 18);
            this.label27.TabIndex = 97;
            this.label27.Text = "WPTC目标温度";
            // 
            // comboBox_PTC_m_heat_level
            // 
            this.comboBox_PTC_m_heat_level.FormattingEnabled = true;
            this.comboBox_PTC_m_heat_level.Location = new System.Drawing.Point(1198, 428);
            this.comboBox_PTC_m_heat_level.Name = "comboBox_PTC_m_heat_level";
            this.comboBox_PTC_m_heat_level.Size = new System.Drawing.Size(100, 26);
            this.comboBox_PTC_m_heat_level.TabIndex = 96;
            // 
            // textBox_PTC_m_heat_level
            // 
            this.textBox_PTC_m_heat_level.Location = new System.Drawing.Point(1069, 428);
            this.textBox_PTC_m_heat_level.Name = "textBox_PTC_m_heat_level";
            this.textBox_PTC_m_heat_level.ReadOnly = true;
            this.textBox_PTC_m_heat_level.Size = new System.Drawing.Size(100, 28);
            this.textBox_PTC_m_heat_level.TabIndex = 95;
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(929, 431);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(116, 18);
            this.label30.TabIndex = 94;
            this.label30.Text = "WPTC加热挡位";
            // 
            // textBox_WPTC_m_target_temp_set
            // 
            this.textBox_WPTC_m_target_temp_set.Location = new System.Drawing.Point(1198, 389);
            this.textBox_WPTC_m_target_temp_set.Name = "textBox_WPTC_m_target_temp_set";
            this.textBox_WPTC_m_target_temp_set.Size = new System.Drawing.Size(100, 28);
            this.textBox_WPTC_m_target_temp_set.TabIndex = 99;
            // 
            // textBox_WPTC_b_target_temp_set
            // 
            this.textBox_WPTC_b_target_temp_set.Location = new System.Drawing.Point(1198, 36);
            this.textBox_WPTC_b_target_temp_set.Name = "textBox_WPTC_b_target_temp_set";
            this.textBox_WPTC_b_target_temp_set.Size = new System.Drawing.Size(100, 28);
            this.textBox_WPTC_b_target_temp_set.TabIndex = 100;
            // 
            // groupBox1
            // 
            this.groupBox1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(880, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(434, 317);
            this.groupBox1.TabIndex = 101;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "电池";
            // 
            // groupBox2
            // 
            this.groupBox2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.Location = new System.Drawing.Point(880, 365);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(434, 308);
            this.groupBox2.TabIndex = 102;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "电机";
            // 
            // groupBox3
            // 
            this.groupBox3.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox3.Location = new System.Drawing.Point(372, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(442, 317);
            this.groupBox3.TabIndex = 103;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "压缩机";
            // 
            // groupBox4
            // 
            this.groupBox4.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox4.Location = new System.Drawing.Point(372, 365);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(442, 140);
            this.groupBox4.TabIndex = 104;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "电子膨胀阀";
            // 
            // groupBox5
            // 
            this.groupBox5.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox5.Location = new System.Drawing.Point(372, 519);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(442, 104);
            this.groupBox5.TabIndex = 105;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "三通阀";
            // 
            // groupBox6
            // 
            this.groupBox6.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox6.Location = new System.Drawing.Point(372, 629);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(442, 101);
            this.groupBox6.TabIndex = 106;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "四通阀";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1326, 787);
            this.Controls.Add(this.textBox_WPTC_b_target_temp_set);
            this.Controls.Add(this.textBox_WPTC_m_target_temp_set);
            this.Controls.Add(this.textBox_WPTC_m_target_temp);
            this.Controls.Add(this.label27);
            this.Controls.Add(this.comboBox_PTC_m_heat_level);
            this.Controls.Add(this.textBox_PTC_m_heat_level);
            this.Controls.Add(this.label30);
            this.Controls.Add(this.textBox_WPTC_b_target_temp);
            this.Controls.Add(this.label29);
            this.Controls.Add(this.comboBox_PTC_b_heat_level);
            this.Controls.Add(this.textBox_PTC_b_heat_level);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.textBox_PTC_b_status);
            this.Controls.Add(this.textBox_PTC_b_temp_internel);
            this.Controls.Add(this.textBox_PTC_b_temp_out);
            this.Controls.Add(this.textBox_PTC_b_current);
            this.Controls.Add(this.textBox_PTC_b_voltage);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.label28);
            this.Controls.Add(this.textBox_four_way_2_set);
            this.Controls.Add(this.textBox_four_way_1_set);
            this.Controls.Add(this.textBox_three_way_2_set);
            this.Controls.Add(this.textBox_three_way_1_set);
            this.Controls.Add(this.textBox_EXV_CurrentPosition_set);
            this.Controls.Add(this.textBox_compressor_limit_power_set);
            this.Controls.Add(this.textBox_compressor_speed_set);
            this.Controls.Add(this.comboBox_compressor_status);
            this.Controls.Add(this.textBox_PTC_m_status);
            this.Controls.Add(this.textBox_PTC_m_temp_internel);
            this.Controls.Add(this.textBox_PTC_m_temp_out);
            this.Controls.Add(this.textBox_PTC_m_current);
            this.Controls.Add(this.textBox_PTC_m_voltage);
            this.Controls.Add(this.textBox_four_way_2);
            this.Controls.Add(this.textBox_four_way_1);
            this.Controls.Add(this.textBox_EXV_status);
            this.Controls.Add(this.textBox_EXV_initial_status);
            this.Controls.Add(this.textBox_EXV_CurrentPosition);
            this.Controls.Add(this.textBox_compressor_current);
            this.Controls.Add(this.textBox_compressor_voltage);
            this.Controls.Add(this.textBox_temperature_IGBT);
            this.Controls.Add(this.textBox_temperature_basic_board);
            this.Controls.Add(this.textBox_compressor_limit_power);
            this.Controls.Add(this.textBox_compressor_speed);
            this.Controls.Add(this.textBox_compressor_status);
            this.Controls.Add(this.textBox_three_way_2);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox_three_way_1);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label23);
            this.Controls.Add(this.label24);
            this.Controls.Add(this.label25);
            this.Controls.Add(this.label26);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button_save_data);
            this.Controls.Add(this.button_clear_window);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_open_serial);
            this.Controls.Add(this.comboBox_baudrate);
            this.Controls.Add(this.comboBox_serialport);
            this.Controls.Add(this.button_scan_serial);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox6);
            this.Name = "Form1";
            this.Text = "R290热管理台架上位机";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_scan_serial;
        private System.Windows.Forms.ComboBox comboBox_serialport;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox comboBox_baudrate;
        private System.Windows.Forms.Button button_open_serial;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button_clear_window;
        private System.Windows.Forms.Button button_save_data;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox textBox_three_way_1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox_three_way_2;
        private System.Windows.Forms.TextBox textBox_compressor_status;
        private System.Windows.Forms.TextBox textBox_compressor_speed;
        private System.Windows.Forms.TextBox textBox_compressor_limit_power;
        private System.Windows.Forms.TextBox textBox_temperature_basic_board;
        private System.Windows.Forms.TextBox textBox_temperature_IGBT;
        private System.Windows.Forms.TextBox textBox_compressor_voltage;
        private System.Windows.Forms.TextBox textBox_compressor_current;
        private System.Windows.Forms.TextBox textBox_EXV_CurrentPosition;
        private System.Windows.Forms.TextBox textBox_EXV_initial_status;
        private System.Windows.Forms.TextBox textBox_EXV_status;
        private System.Windows.Forms.TextBox textBox_four_way_1;
        private System.Windows.Forms.TextBox textBox_four_way_2;
        private System.Windows.Forms.TextBox textBox_PTC_m_voltage;
        private System.Windows.Forms.TextBox textBox_PTC_m_current;
        private System.Windows.Forms.TextBox textBox_PTC_m_temp_out;
        private System.Windows.Forms.TextBox textBox_PTC_m_temp_internel;
        private System.Windows.Forms.TextBox textBox_PTC_m_status;
        private System.Windows.Forms.ComboBox comboBox_compressor_status;
        private System.Windows.Forms.TextBox textBox_compressor_speed_set;
        private System.Windows.Forms.TextBox textBox_compressor_limit_power_set;
        private System.Windows.Forms.TextBox textBox_EXV_CurrentPosition_set;
        private System.Windows.Forms.TextBox textBox_three_way_1_set;
        private System.Windows.Forms.TextBox textBox_three_way_2_set;
        private System.Windows.Forms.ComboBox textBox_four_way_1_set;
        private System.Windows.Forms.ComboBox textBox_four_way_2_set;
        private System.Windows.Forms.TextBox textBox_PTC_b_heat_level;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox textBox_PTC_b_status;
        private System.Windows.Forms.TextBox textBox_PTC_b_temp_internel;
        private System.Windows.Forms.TextBox textBox_PTC_b_temp_out;
        private System.Windows.Forms.TextBox textBox_PTC_b_current;
        private System.Windows.Forms.TextBox textBox_PTC_b_voltage;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.ComboBox comboBox_PTC_b_heat_level;
        private System.Windows.Forms.TextBox textBox_WPTC_b_target_temp;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.TextBox textBox_WPTC_m_target_temp;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.ComboBox comboBox_PTC_m_heat_level;
        private System.Windows.Forms.TextBox textBox_PTC_m_heat_level;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.TextBox textBox_WPTC_m_target_temp_set;
        private System.Windows.Forms.TextBox textBox_WPTC_b_target_temp_set;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.GroupBox groupBox6;
    }
}

