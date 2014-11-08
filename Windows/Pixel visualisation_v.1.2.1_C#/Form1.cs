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
        
        int with;
        int height;
        int stepd;
        const int pixelSize = 5;
        bool act = false;
        
        public Form1()
        {
            InitializeComponent();
            textBox1.Text = "COM34";
            textBox2.Text = "24";
            textBox3.Text = "36";
            textBox4.Text = "1";
            textBox5.Text = "80";
            textBox6.Text = "80";
            textBox7.Text = DateTime.Now.Hour + "." + DateTime.Now.Minute + "." + DateTime.Now.Second;
            serialPort.PortName = textBox1.Text;
            serialPort.BaudRate = 9600;
           
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Thread dr = new Thread(drawFunk);

            if (act == false)
            {
                button1.Text = "Стоп";
                serialPort.Open();
                act = true;
                dr.Start();

            }
            else
            {
                dr.Abort();
                serialPort.Close();
                act = false;
                button1.Text = "Старт";
            }
        }
        private void CreateImage(int temp, int j, int z)
        {

            //Font drawFont = new Font("Arial", 8);
            Graphics img = this.CreateGraphics();
            SolidBrush forPen = new SolidBrush(Color.Black);
            Pen borsers = new Pen(forPen);
            img.DrawLine(borsers, 0, height*pixelSize, with*pixelSize, height*pixelSize);
            img.DrawLine(borsers, with * pixelSize, 0, with * pixelSize, height * pixelSize);
            int min;
            int max;
            try
            {
                 min = Convert.ToInt32(textBox2.Text) * 100;
                 max = Convert.ToInt32(textBox3.Text) * 100;
            }
            catch
            {
                min = 24;
                max = 36;
            }
            float T4 = (max - min) / 4;
            int arg = tempRGB(min, max, temp);
            if (temp <= min + T4)
            {
                if (arg <= 125)
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, arg, 255));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);

              //      //SolidBrush text = new SolidBrush(Color.Black);
                //    //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
                else
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, arg, 255 - (arg - 125)));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                  //  //SolidBrush text = new SolidBrush(Color.Black);
                    //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
            }
            else if (temp >= min + T4 && temp <= min + 2 * T4)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(arg, 255, 125));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                //SolidBrush text = new SolidBrush(Color.Black);
                //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
            }
            else if (temp > min + 2 * T4 && temp <= min + 3 * T4)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, 255 - arg, 125));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                //SolidBrush text = new SolidBrush(Color.Black);
                //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
            }
            else if (temp > min + 3 * T4 && temp <= max)
            {
                if (arg <= 130)
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, arg, 125 + arg));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                    //SolidBrush text = new SolidBrush(Color.Black);
                    //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
                else
                {
                    SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, arg, 255));
                    img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                    //SolidBrush text = new SolidBrush(Color.Black);
                    //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
                }
            }
            else if (temp < min)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(0, 0, 0));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                //SolidBrush text = new SolidBrush(Color.Black);
                //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
            }
            else if (temp > max)
            {
                SolidBrush MyBrush = new SolidBrush(Color.FromArgb(255, 255, 255));
                img.FillRectangle(MyBrush, pixelSize * z, pixelSize * j, pixelSize, pixelSize);
                //SolidBrush text = new SolidBrush(Color.Black);
                //img.DrawString(Convert.ToString(temp), drawFont, text, pixelSize * z + 5, pixelSize * j + 5);
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
            StreamWriter temtxt = new StreamWriter("bitmaps/"+textBox7.Text+".thermoscan");
            Thread.Sleep(1000);
            try
            {
                with = Convert.ToInt32(textBox5.Text);
                height = Convert.ToInt32(textBox6.Text);
                stepd = Convert.ToInt32(textBox4.Text);
            }
            catch
            {
                MessageBox.Show("Длина, ширина, или шаг имели неверный формат. \nБудут выбраны значения по умолчанию.");
                with = 80;
                height = 80;
                stepd = 1;
            }
            serialPort.WriteLine(Convert.ToString(with));
            serialPort.WriteLine(Convert.ToString(height));
            serialPort.WriteLine(Convert.ToString(stepd));
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
                        catch (Exception)
                        {
                            //MessageBox.Show("Обнаружена ошибка(" + ex);
                        }
                    }
                    temtxt.WriteLine();
                    
                }
                act = false;
                temtxt.Close();

                try
                {
                    Rectangle bounds = this.Bounds;
                    using (Bitmap bitmap = new Bitmap(with * pixelSize, height * pixelSize))
                    {
                        using (Graphics g = Graphics.FromImage(bitmap))
                        {
                            g.CopyFromScreen(new Point(bounds.Left + 8, bounds.Top + 30), Point.Empty, bounds.Size);
                        }
                        bitmap.Save("images/"+textBox7.Text + ".jpg");
                        
                    }
                }
                catch { }
        }
        
       

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (act == true)
              button1_Click(sender, e);
            Application.Restart();
        }

       
       
    }
}
