using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;

namespace drawing
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort = new SerialPort();
        const int with = 80;
        const int height = 80;
        const int pixelSize = 4;

        StreamWriter tempMap = new StreamWriter("temperature_Map.txt");
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "COM34";
            textBox2.Text = "24";
            textBox3.Text = "36";
            //File.Delete("temperature_Map.txt");
            button2.Enabled = false;
            button3.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            bool swit = false;
            button2.Enabled = false;
            button1.Enabled = false;
            button3.Enabled = false;
            serialPort.PortName = textBox1.Text;
            serialPort.BaudRate = 9600;
            serialPort.Open();
            serialPort.WriteLine("HUI");
            for (int j = 0; j <= height - 1; j++)
            {
                if (checkBox1.Checked == false)
                {
                    for (int z = 0; z <= with - 1; z++)
                    {
                        try
                        {
                            int temp = Convert.ToInt32(serialPort.ReadLine());
                            CreateImage(temp, j, z);
                            tempMap.Write(temp + " ");
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Обнаружена ошибка(" + ex);
                        }
                    }
                    tempMap.WriteLine();
                }
                else
                {
                    if (swit == false)
                    {
                        for (int z = 0; z <= with - 1; z++)
                        {
                            try
                            {
                                int temp = Convert.ToInt32(serialPort.ReadLine());
                                CreateImage(temp, j, z);
                                tempMap.Write(temp + " ");
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show("Обнаружена ошибка(" + ex);
                            }
                        }
                        tempMap.WriteLine();
                        swit = true;
                    }
                    else if (swit == true)
                    {
                        for (int z = with - 1; z >= 0; z--)
                        {
                            try
                            {
                                int temp = Convert.ToInt32(serialPort.ReadLine());
                                CreateImage(temp, j, z);
                                tempMap.Write(temp + " ");
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show("Обнаружена ошибка(" + ex);
                            }
                        }
                        tempMap.WriteLine();
                        swit = false;
                    }
                }
            }
            serialPort.Close();
            tempMap.Close();
            MessageBox.Show("Готово!");
            button3.Enabled = true;
            button2.Enabled = true;
            button1.Enabled = true;
        }
        private void CreateImage(int temp, int j, int z)
        {
            SolidBrush myBrush = new SolidBrush(Color.Red);
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
                }
                else
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, arg, 255 - (arg - 125)));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                }
            }
            else if (temp >= min + T4 && temp <= min + 2 * T4)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(arg, 255, 125));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
            }
            else if (temp > min + 2 * T4 && temp <= min + 3 * T4)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, 255 - arg, 125));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
            }
            else if (temp > min + 3 * T4 && temp <= max)
            {
                if (arg <= 130)
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, arg, 125 + arg));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                }
                else
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, arg, 255));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                }
            }
            else if (temp < min)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, 0, 0));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
            }
            else if (temp > max)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, 255, 255));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
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

        private void button2_Click(object sender, EventArgs e)
        {
            Rectangle bounds = this.Bounds;
            using (Bitmap bitmap = new Bitmap(with * pixelSize, height * pixelSize))
            {
                using (Graphics g = Graphics.FromImage(bitmap))
                {
                    g.CopyFromScreen(new Point(bounds.Left + 8, bounds.Top + 30), Point.Empty, bounds.Size);
                }
                bitmap.Save("pic.jpg");
                MessageBox.Show("Изображение сохранено!\npic.jpg");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            tempMap.Close();
            MessageBox.Show("Данные сохранены в текстовый документ\ntemperatureMap.txt\nВНИМАНИЕ: Каждая вторая строка в текстовом записана наоборот.");
        }

    }
}
