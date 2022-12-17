using Schraubstock.Communication;
using Schraubstock.UControl;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Schraubstock
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            USB_CDC usbCom = new USB_CDC();
            usbCom.Connect("COM3");
            usbCom.Write(0x10, 0x01, null);


            Setting s = new Setting(btnDeviceIDRead, btnDeivceIDWrite, txtDeviceID)
            {
                MaxValue = 254,
                MinValue = 1,
                Register = 0x20,
                COM = usbCom
            };



        }
    }
}
