using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.CommunicationCommands
{
    public class ReadUnderVoltageError : CommandBase
    {
        private readonly MainViewModel _mainViewModel;

        public ReadUnderVoltageError(MainViewModel mainViewModel, ICommunication communication) : base(communication)
        {
            _mainViewModel = mainViewModel;
        }

        public override void Execute(object? parameter)
        {
            if (IsRunInternal) { return; }
            Task.Run(ExecuteInternal);
        }

        private async Task ExecuteInternal()
        {
            byte[]? data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.REQUEST_SETTINGS,
            Adresses.RegisterAdress.UNDERVOLTAGE_ERROR_ADDR);

            _mainViewModel.UnderVoltageError = await ExecuteRequesAsync(data);
        }
    }
}
