using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.CommandCommands
{
    public class Connect : CommandBase
    {
        private readonly MainViewModel _mainViewModel;
        private readonly ICommunication _communication;

        public Connect(MainViewModel mainViewModel, ICommunication communication) : base(communication)
        {
            _mainViewModel = mainViewModel;
            _communication = communication;
        }

        public override void Execute(object? parameter)
        {
            _communication.Open(_mainViewModel.SelectedComPort);
            if (_communication.IsConnected)
            {
                _mainViewModel.ConnectButtonString = "Trennen";
            }
            else
            {
                _mainViewModel.ConnectButtonString = "Verbinden";
            }

        }
    }
}
