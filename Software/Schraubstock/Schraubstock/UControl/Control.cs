using Schraubstock.Communication;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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

        public USB_CDC COM { get; set; }
        public byte Register { get; set; } = 0x00;


        private void Button_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            try
            {
                COM.Write(Register, USB_CDC.ReadWrite.Write);
            }
            catch
            {
                MessageBox.Show("Fehlr beim Schreiben der Daten", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

            
        }
    }
}
