using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.SettingCommands
{
    public class SendEnable : CommandBase
    {
        private readonly MainViewModel _mainViewModel;

        public SendEnable(MainViewModel mainViewModel, ICommunication communication) : base(communication)
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
            Adresses.CommandAdress.SEND_COMMAND,
            Adresses.Commands.ENABLE_ADDR, "1");

            await ExecuteCommandAsync(data);
        }
    }
}
