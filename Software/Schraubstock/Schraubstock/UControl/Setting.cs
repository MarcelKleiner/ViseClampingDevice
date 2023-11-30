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

        public int MaxValue { get; set; } = 32767;
        public int MinValue { get; set; } = -32768;
        public byte Register { get; set; } = 0x00;
        public USB_CDC COM { get; set; } = new();


        public Setting(Button read, Button write, TextBox txtValue)
        {
            read.Click += Read_Click;
            write.Click += Write_Click;
            _txtValue = txtValue;
        }

        private void Write_Click(object sender, RoutedEventArgs e)
        {
            string textboxContent = _txtValue.Text; 

            try
            {
                if(!int.TryParse(textboxContent, out int value))
                {
                    MessageBox.Show("Eingabe muss eine Zahl sein", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                if(value < MinValue)
                {
                    MessageBox.Show($"Eingabe zu klein. Min Value: {MinValue}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                if (value > MaxValue)
                {
                    MessageBox.Show($"Eingabe zu gross. Max Value: {MaxValue}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                if (COM == null)
                {
                    MessageBox.Show("Keinver Verbindung zu einem Device hergestellt", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

                COM.Write(Register, USB_CDC.ReadWrite.SEND_SETTINGS, TypeConverter.Int16ToByte(Convert.ToInt16(textboxContent)));
            }
            catch
            {
                MessageBox.Show("Fehler beim Schreiben", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Read_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!COM.IsConnected())
                {
                    MessageBox.Show("Kein Device verbunden", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }

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
            }
            catch
            {
                MessageBox.Show("Daten konnte nicht gelesen werden");
            }
        }
    }
}
