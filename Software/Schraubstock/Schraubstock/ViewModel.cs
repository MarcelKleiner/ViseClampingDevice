using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Media;

namespace Schraubstock
{
    internal class ViewModel : INotifyPropertyChanged
    {
        public static Brush? _lightRed;
        public static Brush? _lightGreen;
        public static Brush? _lightYellow;

        private List<string> _comPorts = new();
        private string _selectedComPort = "";

        private string _lblEnable = string.Empty;
        private string _lblClose = string.Empty;
        private string _lblOpen = string.Empty;
        private string _lblStop = string.Empty;
        private string _lblReset = string.Empty;
        private string _lblTeach = string.Empty;

        private Brush? _lblEnableBrush = _lightRed;
        private Brush? _lblCloseBrush = _lightRed;
        private Brush? _lblOpenBrush = _lightRed;
        private Brush? _lblStopBrush = _lightRed;
        private Brush? _lblResetBrush = _lightRed;
        private Brush? _lblTeachBrush = _lightRed;

        public ViewModel()
        {
            _lightRed = (SolidColorBrush)new BrushConverter().ConvertFrom("#FFF7D7D7");
            _lightGreen = (SolidColorBrush)new BrushConverter().ConvertFrom("#FFD7F7DC") ?? throw new NullReferenceException();
            _lightYellow = (SolidColorBrush)new BrushConverter().ConvertFrom("#FFF3F0CC") ?? throw new NullReferenceException();
        }


        public List<string> ComPorts
        {
            get { return _comPorts; }
            set { _comPorts = value; OnPropertyChanged(nameof(ComPorts)); }
        }

        public string SelectedComPort
        {
            get { return _selectedComPort; }
            set { _selectedComPort = value; OnPropertyChanged(nameof(SelectedComPort)); }
        }

        public string LblEnable
        {
            get { return _lblEnable; }
            set { _lblEnable = value; OnPropertyChanged(nameof(LblEnable)); }
        }

        public string LblClose
        {
            get { return _lblClose; }
            set { _lblClose = value; OnPropertyChanged(nameof(LblClose)); }
        }

        public string LblOpen
        {
            get { return _lblOpen; }
            set { _lblOpen = value; OnPropertyChanged(nameof(LblOpen)); }
        }

        public string LblStop
        {
            get { return _lblStop; }
            set { _lblStop = value; OnPropertyChanged(nameof(LblStop)); }
        }

        public string LblReset
        {
            get { return _lblReset; }
            set { _lblReset = value; OnPropertyChanged(nameof(LblReset)); }
        }

        public string LblTeach
        {
            get { return _lblTeach; }
            set { _lblTeach = value; OnPropertyChanged(nameof(LblTeach)); }
        }




        public Brush? LblEnableBrush
        {
            get { return _lblEnableBrush; }
            set { _lblEnableBrush = value; OnPropertyChanged(nameof(LblEnableBrush)); }
        }

        public Brush? LblCloseBrush
        {
            get { return _lblCloseBrush; }
            set { _lblCloseBrush = value; OnPropertyChanged(nameof(LblCloseBrush)); }
        }

        public Brush? LblOpenBrush
        {
            get { return _lblOpenBrush; }
            set { _lblOpenBrush = value; OnPropertyChanged(nameof(LblOpenBrush)); }
        }

        public Brush? LblStopBrush
        {
            get { return _lblStopBrush; }
            set { _lblStopBrush = value; OnPropertyChanged(nameof(LblStopBrush)); }
        }

        public Brush? LblResetBrush
        {
            get { return _lblResetBrush; }
            set { _lblResetBrush = value; OnPropertyChanged(nameof(LblResetBrush)); }
        }

        public Brush? LblTeachBrush
        {
            get { return _lblTeachBrush; }
            set { _lblTeachBrush = value; OnPropertyChanged(nameof(LblTeachBrush)); }
        }





        public event PropertyChangedEventHandler? PropertyChanged;

        // Create the OnPropertyChanged method to raise the event
        // The calling member's name will be used as the parameter.
        protected void OnPropertyChanged([CallerMemberName] string? name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
