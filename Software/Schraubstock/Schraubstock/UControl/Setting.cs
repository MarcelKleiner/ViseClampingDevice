using Schraubstock.Communication;
using Schraubstock.Tool;
using System;
using System.Windows;
using System.Windows.Controls;

namespace Schraubstock.UControl
{
    internal class Setting
    {

        private readonly TextBox _txtValue;
        private string currentTxtValue = "";

        public int MaxValue { get; set; } = 32767;
        public int MinValue { get; set; } = -32768;
        public byte Register { get; set; } = 0x00;
        public USB_CDC COM { get; set; } = new();


        public Setting(Button read, Button write, TextBox txtValue)
        {
            read.Click += Read_Click;
            write.Click += Write_Click;
            txtValue.KeyUp += TxtValue_KeyUp; ;
            _txtValue = txtValue;
        }

        private void TxtValue_KeyUp(object sender, System.Windows.Input.KeyEventArgs e)
        {
            try
            {
                if (_txtValue.Text == "")
                {
                    currentTxtValue = _txtValue.Text;
                    return;
                }

                short value = Convert.ToInt16(_txtValue.Text);
                if (value > MaxValue)
                {
                    _txtValue.Text = MaxValue.ToString();
                }
                if (value < MinValue)
                {
                    _txtValue.Text = MinValue.ToString();
                }
                currentTxtValue = _txtValue.Text;
            }
            catch
            {
                _txtValue.Text = currentTxtValue;
            }
        }

        private void Write_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (COM == null || string.IsNullOrEmpty(currentTxtValue))
                {
                    MessageBox.Show("Ungültige angaben", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                COM.Write(Register, USB_CDC.ReadWrite.SEND_SETTINGS, TypeConverter.Int16ToByte(Convert.ToInt16(currentTxtValue)));
            }
            catch
            {

            }



        }

        private void Read_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                var data = COM.Write(Register, USB_CDC.ReadWrite.GET_SETTINGS, null);

                if (data == null || data[0] != 0x1F)
                {
                    MessageBox.Show("Ungültige Daten empfangen");
                    return;
                }

                if (data[3] != Register)
                {
                    MessageBox.Show("Falsche Daten");
                    return;
                }

                _txtValue.Text = TypeConverter.ByteToInt16(data, 4).ToString();
                currentTxtValue = _txtValue.Text;
            }
            catch
            {
                MessageBox.Show("Daten konnte nicht gelesen werden");
            }
        }
    }
}
