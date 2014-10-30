using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Threading;

namespace drawing
{
    public partial class Form1 : Form
    {
        private static SerialPort serialPort = new SerialPort();
        StreamWriter temtxt = new StreamWriter("input.txt");
        const int with = 16;
        const int height = 4;
        const int pixelSize = 40;
        bool swit = false;
        bool act = false;
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "COM35";
            textBox2.Text = "24";
            textBox3.Text = "36";
            //File.Delete("temperature_Map.txt");
            //button2.Enabled = false;
            button3.Enabled = false;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread dr = new Thread(drawFunk);

            if (swit == false)
            {
                //button2.Enabled = false;
                //button1.Enabled = false;
                button3.Enabled = false;
                serialPort.PortName = textBox1.Text;
                serialPort.BaudRate = 115200;
                serialPort.Open();
                act = true;
                dr.Start();
                swit = true;
            }
            else
            {
                act = false;
                Thread.Sleep(50);
                dr.Abort();
                //serialPort.Close();

                button3.Enabled = true;
                button2.Enabled = true;
                button1.Enabled = true;
                swit = false;
            }

        }
        private void CreateImage(int temp, int j, int z)
        {

            Font drawFont = new Font("Arial", 8);
            Graphics img = this.CreateGraphics();
            int min = Convert.ToInt32(textBox2.Text);
            int max = Convert.ToInt32(textBox3.Text);
            float T4 = (max - min) / 4;
            int arg = tempRGB(min, max, temp);
            if (temp <= min + T4)
            {
                if (arg <= 125)
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, arg, 255));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);

                    SolidBrush text = new SolidBrush(Color.Black);
                    img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
                else
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, arg, 255 - (arg - 125)));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                    SolidBrush text = new SolidBrush(Color.Black);
                    img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
            }
            else if (temp >= min + T4 && temp <= min + 2 * T4)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(arg, 255, 125));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                SolidBrush text = new SolidBrush(Color.Black);
                img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
            }
            else if (temp > min + 2 * T4 && temp <= min + 3 * T4)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, 255 - arg, 125));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                SolidBrush text = new SolidBrush(Color.Black);
                img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
            }
            else if (temp > min + 3 * T4 && temp <= max)
            {
                if (arg <= 130)
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, arg, 125 + arg));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                    SolidBrush text = new SolidBrush(Color.Black);
                    img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
                else
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, arg, 255));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                    SolidBrush text = new SolidBrush(Color.Black);
                    img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
            }
            else if (temp < min)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, 0, 0));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                SolidBrush text = new SolidBrush(Color.Black);
                img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
            }
            else if (temp > max)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, 255, 255));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                SolidBrush text = new SolidBrush(Color.Black);
                img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
            }
        }

        private static int tempRGB(float minTemp, float maxTemp, float temp)
        {
            float T4 = (maxTemp - minTemp) / 4;
            if (temp <= minTemp + T4 && temp >= minTemp)
            {
                float result;
                result = (255 * (temp - minTemp)) / T4;
                int res = Convert.ToInt32(result);
                return res;
            }
            else if (temp > minTemp + T4 && temp <= minTemp + 2 * T4)
            {
                float result;
                result = (255 * (temp - (T4 + minTemp))) / T4;
                int res = Convert.ToInt32(result);
                return res;
            }
            else if (temp > minTemp + 2 * T4 && temp <= minTemp + 3 * T4)
            {
                float result;
                result = (255 * (temp - (2 * T4 + minTemp))) / T4;
                int res = Convert.ToInt32(result);
                return res;
            }
            else if (temp > minTemp + 3 * T4 && temp <= maxTemp)
            {
                float result;
                result = (255 * (temp - (3 * T4 + minTemp))) / T4;
                int res = Convert.ToInt32(result);
                return res;
            }
            else
                return 0;
        }

        private void drawFunk()
        {
            while (act == true)
            {
                serialPort.WriteLine("H");
                for (int j = 0; j <= height - 1; j++)
                {

                    for (int z = 0; z <= with - 1; z++)
                    {
                        try
                        {
                            int temp = Convert.ToInt32(serialPort.ReadLine());
                            CreateImage(temp, j, z);
                            temtxt.Write(Convert.ToString(temp)+ " ");

                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Обнаружена ошибка(" + ex);
                        }

                        
                    }
                    temtxt.WriteLine();
                }
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Rectangle bounds = this.Bounds;
            using (Bitmap bitmap = new Bitmap(with * pixelSize, height * pixelSize))
            {
                using (Graphics g = Graphics.FromImage(bitmap))
                {
                    g.CopyFromScreen(new Point(bounds.Left + 8, bounds.Top + 30), Point.Empty, bounds.Size);
                }
                bitmap.Save(DateTime.Now.Hour + "." + DateTime.Now.Minute + "." + DateTime.Now.Second + ".jpg");
               // MessageBox.Show("Изображение сохранено!\npic.jpg");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            temtxt.Close();
            MessageBox.Show("Данные сохранены!");
        }



    }
}
