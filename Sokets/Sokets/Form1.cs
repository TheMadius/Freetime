using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sokets
{
    public partial class Form1 : Form
    {
        double max;
        Socket socket;
        public Form1()
        {
            InitializeComponent();
            this.button1.Enabled = false;
            this.btnConnect.Enabled = true;
            this.btnDis.Enabled = false;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                string IP = this.textBox1.Text;
                int port = Convert.ToInt32(this.textBox2.Text);;
                socket.Connect(IPAddress.Parse(IP), port);

                this.button1.Enabled = true;
                this.btnConnect.Enabled = false;
                this.btnDis.Enabled = true;
            }
            catch (Exception exc)
            {
                socket = null;
                MessageBox.Show(exc.Message);
            }
        }

        private void btnDis_Click(object sender, EventArgs e)
        {
            int type = 2;
            byte[] lengthBuffer = BitConverter.GetBytes((int)type);
            socket.Send(lengthBuffer, 4, SocketFlags.None);

            socket.Close();
            socket = null;

            this.button1.Enabled = false;
            this.btnConnect.Enabled = true;
            this.btnDis.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            max = Convert.ToDouble(this.textBox4.Text);

            int type = 1;
            byte[] lengthBuffer = BitConverter.GetBytes((int)type);
            socket.Send(lengthBuffer, 4, SocketFlags.None);

            byte[] lengthBytes = new byte[4];
            socket.Receive(lengthBytes, 4, SocketFlags.None);

            int length = BitConverter.ToInt32(lengthBytes, 0);
            byte[] buffer = new byte[length];
            socket.Receive(buffer, length, SocketFlags.None);

            string mem = Encoding.Unicode.GetString(buffer, 0, length);

            this.textBox3.Text = mem;

            if(Convert.ToDouble(mem) > max)
            {
                MessageBox.Show("Allowed level exceeded!!!");
            }
        }
    }
}
