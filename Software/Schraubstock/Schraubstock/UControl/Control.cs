using Schraubstock.Communication;
using System.Windows;
using System.Windows.Controls;

namespace Schraubstock.UControl
{
    internal class Control
    {
        public Control(Button button)
        {
            button.Click += Button_Click; ;
        }

        public USB_CDC COM { get; set; } = new();
        public byte Register { get; set; } = 0x00;


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                COM.Write(Register, USB_CDC.ReadWrite.SEND_COMMAND);
            }
            catch
            {
                MessageBox.Show("Fehler beim Schreiben der Daten", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
