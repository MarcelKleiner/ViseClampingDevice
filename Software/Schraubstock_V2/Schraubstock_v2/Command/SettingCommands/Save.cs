using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.CommunicationCommands
{
    public class Save : CommandBase
    {
        private readonly MainViewModel _mainViewModel;
        private readonly ICommunication _Communication;

        public Save(MainViewModel mainViewModel, ICommunication communication) : base(communication)
        {
            _mainViewModel = mainViewModel;
            _Communication = communication;
        }

        public override void Execute(object? parameter)
        {
            Task.Run(ExecuteAsync);
        }

        private async Task ExecuteAsync()
        {
            byte[]? data = _mainViewModel.MessageCreater.Create(Adresses.CommandAdress.SEND_SETTINGS, Adresses.RegisterAdress.SAVE_SETTINGS_ADDR, Int16.MaxValue.ToString());
            await ExecuteCommandAsync(data);
        }


    }
}
