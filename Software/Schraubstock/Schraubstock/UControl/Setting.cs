using Schraubstock.Communication;
using Schraubstock.Tool;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Schraubstock.UControl
{
    internal class Setting
    {

        private TextBox txtValue;
        private string currentTxtValue = "";

        public int MaxValue { get; set; } = 32767;
        public int MinValue { get; set; } = -32768;
        public byte Register { get; set; } = 0x00;
        public USB_CDC COM { get; set; }


        public Setting(Button read, Button write, TextBox txtValue)
        {
            read.Click += Read_Click;
            write.Click += Write_Click;
            txtValue.KeyUp += TxtValue_KeyUp; ;
            this.txtValue = txtValue;
        }

        private void TxtValue_KeyUp(object sender, System.Windows.Input.KeyEventArgs e)
        {
            try
            {
                if (txtValue.Text == "")
                {
                    currentTxtValue = txtValue.Text;
                    return;
                }

                short value = Convert.ToInt16(txtValue.Text);
                if (value > MaxValue)
                {
                    txtValue.Text = MaxValue.ToString();
                }
                if (value < MinValue)
                {
                    txtValue.Text = MinValue.ToString();
                }
                currentTxtValue = txtValue.Text;
            }
            catch
            {
                txtValue.Text = currentTxtValue;
            }
        }


        private void Write_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            if (COM == null || string.IsNullOrEmpty(currentTxtValue))
            {
                MessageBox.Show("Ungültige angaben", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            COM.Write(Register, 0x00, TypeConverter.Int16ToByte(Convert.ToInt16(currentTxtValue)));
        }

        private void Read_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            var data = COM.Write(Register, 0x01, null);

            if (data == null || data[0] != 0x1D)
            {
                //MessageBox.Show("Ungültige Daten");
                return;
            }
            else
            {
                txtValue.Text = TypeConverter.ByteToInt16(data, 1).ToString();
                currentTxtValue = txtValue.Text;
            }

        }



    }
}
