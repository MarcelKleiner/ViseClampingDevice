using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.CommunicationCommands
{
    public class WriteHysteresis : CommandBase
    {
        private readonly MainViewModel _mainViewModel;
        private readonly ICommunication _Communication;

        public WriteHysteresis(MainViewModel mainViewModel, ICommunication communication) : base(communication)
        {
            _mainViewModel = mainViewModel;
            _Communication = communication;
        }
        public override void Execute(object? parameter)
        {
            if (IsRunInternal) { return; }
            Task.Run(ExecuteInternal);
        }

        private async Task ExecuteInternal()
        {
            byte[]? data = _mainViewModel.MessageCreater.Create(
            Adresses.CommandAdress.SEND_SETTINGS,
            Adresses.RegisterAdress.IN_POS_DIFF_ADDR);

            await ExecuteCommandAsync(data);
        }
    }
}
