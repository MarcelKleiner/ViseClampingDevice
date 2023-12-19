using Schraubstock_v2.Command.CommandCommands;
using Schraubstock_v2.Command.CommunicationCommands;
using Schraubstock_v2.Command.SettingCommands;
using Schraubstock_v2.Command.StatusUpdate;
using Schraubstock_v2.Common;
using Schraubstock_v2.Communication;
using Schraubstock_v2.Logger;
using Serilog;
using System.Collections.ObjectModel;
using System.IO.Ports;
using System.Windows.Input;
using System.Windows.Media;

namespace Schraubstock_v2.ViewModel
{
    public class MainViewModel : ViewModelBase
    {
        private readonly IInformer _informer;
        private readonly ICommunication _communication;
        private UpdateStatus updateStatus;

        public Message MessageCreater { get; }

        public ObservableCollection<string> ComPorts { get; set; } = new();

        private string _selectedComPort = "";
        public string SelectedComPort
        {
            get { return _selectedComPort; }
            set { _selectedComPort = value; OnPropertyChanged(); }
        }


        public bool IsDropdownOpenn
        {
            set
            {
                if (value == false)
                {
                    return;
                }
                try
                {
                    ComPorts.Clear();
                    foreach (string portName in SerialPort.GetPortNames())
                    {
                        ComPorts.Add(portName);
                    }
                    OnPropertyChanged();
                }
                catch (Exception ex)
                {
                    Log.Error(ex.Message);
                    Error.Show("Fehler beim Laden der COM-Ports");
                }

            }
        }


        //TextBox

        private string _logTextBox = "";
        public string LogTextBox
        {
            get { return _logTextBox; }
            set { _logTextBox = value; OnPropertyChanged(); }
        }

        private string _deviceAddress = "";
        public string DeviceAddress
        {
            get { return _deviceAddress; }
            set { _deviceAddress = value; OnPropertyChanged(); }
        }

        private string _teachSpeed = "";
        public string TeachSpeed
        {
            get { return _teachSpeed; }
            set { _teachSpeed = value; OnPropertyChanged(); }
        }

        private string _teachTorque = "";
        public string TeachTorque
        {
            get { return _teachTorque; }
            set { _teachTorque = value; OnPropertyChanged(); }
        }

        private string _ClampingSpeed = "";
        public string ClampingSpeed
        {
            get { return _ClampingSpeed; }
            set { _ClampingSpeed = value; OnPropertyChanged(); }
        }

        private string _ClampingTroque = "";
        public string ClampingTorque
        {
            get { return _ClampingTroque; }
            set { _ClampingTroque = value; OnPropertyChanged(); }
        }

        private string _SelfShutdownDelay = "";
        public string SelfShutdownDelay
        {
            get { return _SelfShutdownDelay; }
            set { _SelfShutdownDelay = value; OnPropertyChanged(); }
        }

        private string _Hysteresis = "";

        public string Hysteresis
        {
            get { return _Hysteresis; }
            set { _Hysteresis = value; OnPropertyChanged(); }
        }

        private string _OpeningDistance = "";
        public string OpeningDistance
        {
            get { return _OpeningDistance; }
            set { _OpeningDistance = value; OnPropertyChanged(); }
        }

        private string _OverCurrentWarning = "";
        public string OverCurrentWarning
        {
            get { return _OverCurrentWarning; }
            set { _OverCurrentWarning = value; OnPropertyChanged(); }
        }

        private string _OverCurrentError = "";
        public string OverCurrentError
        {
            get { return _OverCurrentError; }
            set { _OverCurrentError = value; OnPropertyChanged(); }
        }

        private string _UnderVoltageWarning = "";
        public string UnderVoltageWarning
        {
            get { return _UnderVoltageWarning; }
            set { _UnderVoltageWarning = value; OnPropertyChanged(); }
        }

        private string _UnderVoltageError = "";
        public string UnderVoltageError
        {
            get { return _UnderVoltageError; }
            set { _UnderVoltageError = value; OnPropertyChanged(); }
        }


        //Label
        private string _DriveStatusEnable = "";
        public string DriveStatusEnable
        {
            get { return _DriveStatusEnable; }
            set { _DriveStatusEnable = value; OnPropertyChanged(); }
        }

        private string _DriveStatusOpen = "";
        public string DriveStatusOpen
        {
            get { return _DriveStatusOpen; }
            set { _DriveStatusOpen = value; OnPropertyChanged(); }
        }

        private string _DriveStatusRun = "";
        public string DriveStatusRun
        {
            get { return _DriveStatusRun; }
            set { _DriveStatusRun = value; OnPropertyChanged(); }
        }

        private string _DriveStatusError = "";
        public string DriveStatusError
        {
            get { return _DriveStatusError; }
            set { _DriveStatusError = value; OnPropertyChanged(); }
        }

        private Brush _errorBackgroundColor = Brushes.LightGreen;
        public Brush ErrorBackgroundColor
        {
            get { return _errorBackgroundColor; }
            set { _errorBackgroundColor = value; OnPropertyChanged(); }

        }

        private string _connectButtonString = "Verbinden";
        public string ConnectButtonString
        {
            get { return _connectButtonString; }
            set { _connectButtonString = value; OnPropertyChanged(); }
        }



        //Command
        public ICommand Connect { get; }
        public ICommand ReadDeviceAddress { get; }
        public ICommand WriteDeviceAddress { get; }
        public ICommand ReadTeachSpeed { get; }
        public ICommand WriteTeachSpeed { get; }
        public ICommand ReadTeachTorque { get; }
        public ICommand WriteTeachTorque { get; }
        public ICommand ReadClampingTroque { get; }
        public ICommand WriteClampingTroque { get; }
        public ICommand ReadSelfShutdownDelay { get; }
        public ICommand WriteSelfShutdownDelay { get; }
        public ICommand ReadHysteresis { get; }
        public ICommand WriteHysteresis { get; }
        public ICommand ReadOpeningDistance { get; }
        public ICommand WriteOpeningDistance { get; }
        public ICommand ReadOverCurrentWarning { get; }
        public ICommand WriteOverCurrentWarning { get; }
        public ICommand ReadOverCurrentError { get; }
        public ICommand WriteOverCurrentError { get; }
        public ICommand ReadUnderVoltageWarning { get; }
        public ICommand WriteUnderVoltageWarning { get; }
        public ICommand ReadClampingSpeed { get; }
        public ICommand WriteClampingSpeed { get; }
        public ICommand ReadUnderVoltageError { get; }
        public ICommand WriteUnderVoltageError { get; }
        public ICommand ReadAll { get; }
        public ICommand Save { get; }
        public ICommand SendEnable { get; }
        public ICommand SendDisable { get; }
        public ICommand SendOpen { get; }
        public ICommand SendClose { get; }
        public ICommand SendStop { get; }
        public ICommand SendTeach { get; }
        public ICommand SendReset { get; }
        public ICommand UploadSettings { get; }

        public MainViewModel()
        {
            _informer = new Informer(this);
            MessageCreater = new(_informer);
            _communication = new UsbCdc(_informer);
            updateStatus = new(this, _informer, _communication);

            Connect = new Connect(this, _communication);
            ReadDeviceAddress = new ReadDeviceAddress(this, _communication);
            WriteDeviceAddress = new WriteDeviceAddress(this, _communication);
            ReadTeachSpeed = new ReadTeachSpeed(this, _communication);
            WriteTeachSpeed = new WriteTeachSpeed(this, _communication);
            ReadTeachTorque = new ReadTeachTorque(this, _communication);
            WriteTeachTorque = new WriteTeachTorque(this, _communication);
            ReadClampingTroque = new ReadClampingTroque(this, _communication);
            WriteClampingTroque = new WriteClampingTroque(this, _communication);
            ReadSelfShutdownDelay = new ReadSelfShutdownDelay(this, _communication);
            WriteSelfShutdownDelay = new WriteSelfShutdownDelay(this, _communication);
            ReadHysteresis = new ReadHysteresis(this, _communication);
            WriteHysteresis = new WriteHysteresis(this, _communication);
            ReadOpeningDistance = new ReadOpeningDistance(this, _communication);
            WriteOpeningDistance = new WriteOpeningDistance(this, _communication);
            ReadOverCurrentWarning = new ReadOverCurrentWarning(this, _communication);
            WriteOverCurrentWarning = new WriteOverCurrentWarning(this, _communication);
            ReadOverCurrentError = new ReadOverCurrentError(this, _communication);
            WriteOverCurrentError = new WriteOverCurrentError(this, _communication);
            ReadUnderVoltageWarning = new ReadUnderVoltageWarning(this, _communication);
            WriteUnderVoltageWarning = new WriteUnderVoltageWarning(this, _communication);
            ReadClampingSpeed = new ReadClampingSpeed(this, _communication);
            WriteClampingSpeed = new WriteClampingSpeed(this, _communication);
            ReadUnderVoltageError = new ReadUnderVoltageError(this, _communication);
            WriteUnderVoltageError = new WriteUnderVoltageError(this, _communication);
            ReadAll = new ReadAll(this, _communication);
            Save = new Save(this, _communication);
            SendEnable = new SendEnable(this, _communication);
            SendDisable = new SendDisable(this, _communication);
            SendOpen = new SendOpen(this, _communication);
            SendClose = new SendClose(this, _communication);
            SendStop = new SendStop(this, _communication);
            SendTeach = new SendTeach(this, _communication);
            SendReset = new SendReset(this, _communication);
            UploadSettings = new UploadSettings(this, _communication);
        }


    }
}
