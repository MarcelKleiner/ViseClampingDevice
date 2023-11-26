using Schraubstock.Communication;
using Schraubstock.UControl;
using System;
using System.IO.Ports;
using System.Linq;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Control = Schraubstock.UControl.Control;

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

            InitControll();
            Thread tReadStatus = new Thread(() => ReadStatus());
            //tReadStatus.Start();
        }

        private void InitControll()
        {
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

            Setting sOpeningDistance = new Setting(btnOpeningDistanceRead, btnOpeningDistanceWrite, txtOpeningDistance)
            {
                MaxValue = 200,
                MinValue = 10,
                Register = 0x16,
                COM = usbCom
            };



            Control cClose = new Control(btnClose)
            {
                Register = 0x01,
                COM = usbCom
            };
            Control cOpen = new Control(btnOpen)
            {
                Register = 0x02,
                COM = usbCom
            };
            Control cTeach = new Control(btnTeach)
            {
                Register = 0x03,
                COM = usbCom
            };
            Control cReset = new Control(btnReset)
            {
                Register = 0x04,
                COM = usbCom
            };
            Control cEnable = new Control(btnEnable)
            {
                Register = 0x05,
                COM = usbCom
            };
            Control cDisable = new Control(btnDisable)
            {
                Register = 0x06,
                COM = usbCom
            };
            Control cStop = new Control(btnStop)
            {
                Register = 0x07,
                COM = usbCom
            };


        }


        private void ComPort_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            try
            {
                ComboBox cmb = (ComboBox)sender;
                if (cmb.SelectedItem == null)
                    return;

                string? comPort = cmb.SelectedItem.ToString();

                if (comPort == null)
                    return;

                viewModel.SelectedComPort = comPort;
                if (!usbCom.Connect(comPort))
                {
                    viewModel.SelectedComPort = "";
                    cmb.SelectedIndex = -1;
                }

            }
            catch
            {

            }
        }


        private void ComPort_DropDownOpend(object sender, EventArgs e)
        {
            if (viewModel.ComPorts != null)
            {
                viewModel.ComPorts.Clear();
                viewModel.SelectedComPort = "";
            }

            viewModel.ComPorts = SerialPort.GetPortNames().ToList();
        }




        private void ReadStatus()
        {
            while (true)
            {
                if (usbCom.IsConnected())
                {
                    viewModel.LblEnableBrush = ReadStatus(0x01);
                    Thread.Sleep(10);
                    viewModel.LblCloseBrush = ReadStatus(0x02);
                    Thread.Sleep(10);
                    viewModel.LblOpenBrush = ReadStatus(0x03);
                    Thread.Sleep(10);
                    viewModel.LblStopBrush = ReadStatus(0x04);
                    Thread.Sleep(10);
                }
                Thread.Sleep(1000);
            }
        }

        int diagnoseCounter = 0;

        private Brush? ReadStatus(byte register)
        {
            try
            {
                var data = usbCom.Write(register, USB_CDC.ReadWrite.GET_STATUS);
                if (data != null && data[1] == register)
                {
                    diagnoseCounter++;
                    return data[2] == 0 ? ViewModel._lightRed : ViewModel._lightGreen;

                }
                return ViewModel._lightYellow;
            }
            catch
            {
                //  MessageBox.Show(diagnoseCounter.ToString());
                usbCom.Dissconnect();
                usbCom.Connect(usbCom.GetComPort());
                return ViewModel._lightYellow;
            }

        }

    }
}
