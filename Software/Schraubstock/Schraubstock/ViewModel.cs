using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Schraubstock
{
    internal class ViewModel : INotifyPropertyChanged
    {
        private List<string> _comPorts;
        private string _selectedComPort;

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



        public event PropertyChangedEventHandler? PropertyChanged;

        // Create the OnPropertyChanged method to raise the event
        // The calling member's name will be used as the parameter.
        protected void OnPropertyChanged([CallerMemberName] string name = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }
    }
}
