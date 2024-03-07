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
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.textBox_three_way_1 = new System.Windows.Forms.TextBox();
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
            this.textBox1.Size = new System.Drawing.Size(330, 489);
            this.textBox1.TabIndex = 6;
            // 
            // button_clear_window
            // 
            this.button_clear_window.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_clear_window.ForeColor = System.Drawing.Color.Black;
            this.button_clear_window.Location = new System.Drawing.Point(244, 672);
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
            this.button_save_data.Location = new System.Drawing.Point(37, 672);
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
            this.label10.Location = new System.Drawing.Point(476, 372);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(71, 18);
            this.label10.TabIndex = 24;
            this.label10.Text = "EXV开度";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(422, 410);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(125, 18);
            this.label11.TabIndex = 25;
            this.label11.Text = "EXV初始化状态";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(440, 452);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(107, 18);
            this.label12.TabIndex = 26;
            this.label12.Text = "EXV运行状态";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(431, 523);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(116, 18);
            this.label13.TabIndex = 27;
            this.label13.Text = "三通阀#1开度";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(431, 565);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(116, 18);
            this.label14.TabIndex = 28;
            this.label14.Text = "三通阀#2开度";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(431, 672);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(116, 18);
            this.label15.TabIndex = 30;
            this.label15.Text = "四通阀#2状态";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(431, 630);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(116, 18);
            this.label16.TabIndex = 29;
            this.label16.Text = "四通阀#1状态";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(1004, 137);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(116, 18);
            this.label17.TabIndex = 33;
            this.label17.Text = "WPTC出口温度";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(1040, 95);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(80, 18);
            this.label18.TabIndex = 32;
            this.label18.Text = "WPTC电流";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(1040, 56);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(80, 18);
            this.label19.TabIndex = 31;
            this.label19.Text = "WPTC电压";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(1004, 180);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(116, 18);
            this.label20.TabIndex = 34;
            this.label20.Text = "WPTC内部温度";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(1004, 223);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(116, 18);
            this.label21.TabIndex = 35;
            this.label21.Text = "WPTC工作状态";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(1004, 484);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(116, 18);
            this.label22.TabIndex = 40;
            this.label22.Text = "WPTC工作状态";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(1004, 441);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(116, 18);
            this.label23.TabIndex = 39;
            this.label23.Text = "WPTC内部温度";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(1004, 398);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(116, 18);
            this.label24.TabIndex = 38;
            this.label24.Text = "WPTC出口温度";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(1040, 356);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(80, 18);
            this.label25.TabIndex = 37;
            this.label25.Text = "WPTC电流";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(1040, 317);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(80, 18);
            this.label26.TabIndex = 36;
            this.label26.Text = "WPTC电压";
            // 
            // textBox_three_way_1
            // 
            this.textBox_three_way_1.Location = new System.Drawing.Point(573, 520);
            this.textBox_three_way_1.Name = "textBox_three_way_1";
            this.textBox_three_way_1.Size = new System.Drawing.Size(100, 28);
            this.textBox_three_way_1.TabIndex = 41;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1326, 743);
            this.Controls.Add(this.textBox_three_way_1);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label23);
            this.Controls.Add(this.label24);
            this.Controls.Add(this.label25);
            this.Controls.Add(this.label26);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
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
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox textBox_three_way_1;
    }
}

