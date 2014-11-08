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
        static int with;
        static int height;
        int stepd;
        const int pixelSize = 5;
        bool act = false;
        bool virg = true;
        int[,] tempMap;
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
                virg = false;
                textBox7.Enabled = false;
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
        private void CreateImage(int temp, int j, int z, int min, int max)
        {

            //Font drawFont = new Font("Arial", 8);
            Graphics img = this.CreateGraphics();
            SolidBrush forPen = new SolidBrush(Color.Black);
            Pen borsers = new Pen(forPen);
            img.DrawLine(borsers, 0, height*pixelSize, with*pixelSize, height*pixelSize);
            img.DrawLine(borsers, with * pixelSize, 0, with * pixelSize, height * pixelSize);
            
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
            tempMap = new int[height, with];
            serialPort.WriteLine(Convert.ToString(with));
            serialPort.WriteLine(Convert.ToString(height));
            serialPort.WriteLine(Convert.ToString(stepd));
                for (int j = 0; j <= height - 1; j++)
                {
                    for (int z = 0; z <= with - 1; z++)
                    {
                        try
                        {
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
                            int temp = Convert.ToInt32(serialPort.ReadLine());
                            CreateImage(temp, j, z, min, max);
                            temtxt.Write(Convert.ToString(temp)+ " ");
                            tempMap[j, z] = temp;
                        }
                        catch (Exception) {}
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
        private static int MinElement(int[,] array)
        {
            int minElement = array[0, 0];
            for (int j = 0; j <= array.GetLength(0) - 1; j++)
            {
                for (int z = 0; z <= array.GetLength(1) - 1; z++)
                {
                    if (minElement > array[j, z]) minElement = array[j, z];
                }
            }
            return minElement;
        }
        private static int MaxElement(int[,] array)
        {
            int maxElement = array[0, 0];

            for (int j = 0; j < array.GetLength(0) - 1; j++)
            {
                for (int z = 0; z <= array.GetLength(1) - 1; z++)
                {
                    if (maxElement < array[j, z]) maxElement = array[j, z];

                }
            }
            return maxElement;
        }
        private void button5_Click(object sender, EventArgs e)
        {
            if (act == true)
              button1_Click(sender, e);
            Application.Restart();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            if (act == false && virg == false)
            {
                int minTemp = MinElement(tempMap);
                int maxTemp = MaxElement(tempMap);
                for (int j = 0; j <= height - 1; j++)
                {
                    for (int z = 0; z <= with - 1; z++)
                    {
                        CreateImage(tempMap[j, z], j, z, minTemp, maxTemp);
                    }
                }
                try
                {
                    Rectangle bounds = this.Bounds;
                    using (Bitmap bitmap = new Bitmap(with * pixelSize, height * pixelSize))
                    {
                        using (Graphics g = Graphics.FromImage(bitmap))
                        {
                            g.CopyFromScreen(new Point(bounds.Left + 8, bounds.Top + 30), Point.Empty, bounds.Size);
                        }
                        bitmap.Save("images/" + textBox7.Text+ "auto" + ".jpg");
                    }
                }
                catch { }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (act == false && virg == false)
            {
                int minTemp = Convert.ToInt32(textBox2.Text)*100;
                int maxTemp = Convert.ToInt32(textBox3.Text)*100;
                for (int j = 0; j <= height - 1; j++)
                {
                    for (int z = 0; z <= with - 1; z++)
                    {
                        CreateImage(tempMap[j, z], j, z, minTemp, maxTemp);
                    }
                }
                try
                {
                    Rectangle bounds = this.Bounds;
                    using (Bitmap bitmap = new Bitmap(with * pixelSize, height * pixelSize))
                    {
                        using (Graphics g = Graphics.FromImage(bitmap))
                        {
                            g.CopyFromScreen(new Point(bounds.Left + 8, bounds.Top + 30), Point.Empty, bounds.Size);
                        }
                        bitmap.Save("images/" + textBox7.Text + "_from_" + textBox2.Text + "_to_" + textBox3.Text + ".jpg");
                    }
                }
                catch { }
            }
        }
    }
}
