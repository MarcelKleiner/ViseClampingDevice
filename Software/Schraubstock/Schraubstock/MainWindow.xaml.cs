using Schraubstock.Communication;
using Schraubstock.UControl;
using System;
using System.Collections.Generic;
using System.IO.Ports;
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
        private USB_CDC usbCom;
        private ViewModel viewModel;

        public MainWindow()
        {
            InitializeComponent();
            usbCom = new USB_CDC();
            viewModel = new ViewModel();
            this.DataContext = viewModel;

            viewModel.ComPorts = SerialPort.GetPortNames().ToList();



            //usbCom.Connect("COM3");
            //usbCom.Write(0x10, 0x01, null);


            Setting sDeviceID = new Setting(btnDeviceIDRead, btnDeivceIDWrite, txtDeviceID)
            {
                MaxValue = 254,
                MinValue = 1,
                Register = 0x20,
                COM = usbCom
            };

            Setting sTeachSpeed = new Setting(btnTeachSpeedRead, btnTeachSpeedWrite, txtTeachSpeed)
            {
                MaxValue = 1000,
                MinValue = 1,
                Register = 0x11,
                COM = usbCom
            };
            Setting sTeachTroque = new Setting(btnTeachTorqueRead, btnTeachTorqueWrite, txtTeachTorque)
            {
                MaxValue = 100,
                MinValue = 1,
                Register = 0x10,
                COM = usbCom
            };
            Setting sDriveSpeed = new Setting(btnDriveSpeedRead, btnDriveSpeedWrite, txtDriveSpeed)
            {
                MaxValue = 1000,
                MinValue = 1,
                Register = 0x13,
                COM = usbCom
            };
            Setting sDriveTroque = new Setting(btnDriveTroqueRead, btnDriveTroqueWrite, txtDriveTroque)
            {
                MaxValue = 100,
                MinValue = 1,
                Register = 0x12,
                COM = usbCom
            };
            Setting sSelfShutdownDelay = new Setting(btnSelfShutdownDelayRead, btnSelfShutdownDelayWrite, txtSelfShutdownDelay)
            {
                MaxValue = 1000,
                MinValue = 1,
                Register = 0x14,
                COM = usbCom
            };
            Setting sHysteresis = new Setting(btnHysteresisRead, btnHysteresisWrite, txtHysteresis)
            {
                MaxValue = 250,
                MinValue = 1,
                Register = 0x15,
                COM = usbCom
            };
            Setting sOverCurrentWarning = new Setting(btnOverCurrentWarningRead, btnOverCurrentWarningWrite, txtOverCurrentWarning)
            {
                MaxValue = 120,
                MinValue = 1,
                Register = 0x19,
                COM = usbCom
            };
            Setting sOverCurrentError = new Setting(btnOverCurrentErrorRead, btnOverCurrentErrorWrite, txtOverCurrentError)
            {
                MaxValue = 120,
                MinValue = 1,
                Register = 0x1A,
                COM = usbCom
            };
            Setting sUndervoltageWarning = new Setting(btnUnderVoltageWarningRead, btnUnderVoltageWarningWrite, txtUnderVoltageWarning)
            {
                MaxValue = 20000,
                MinValue = 10000,
                Register = 0x17,
                COM = usbCom
            };
            Setting sUnderVoltageError = new Setting(btnUnderVoltageErrorRead, btnUnderVoltageErrorWrite, txtUnderVoltageError)
            {
                MaxValue = 20000,
                MinValue = 10000,
                Register = 0x18,
                COM = usbCom
            };

        }

        private void ComPort_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                ComboBox cmb = (ComboBox)sender;
                string? comPort = cmb.SelectedItem.ToString();
                if(comPort != null)
                {
                    viewModel.SelectedComPort =  comPort;
                    usbCom.Connect(comPort);
                }
            }
            catch
            {

            }
        }


    }
}
