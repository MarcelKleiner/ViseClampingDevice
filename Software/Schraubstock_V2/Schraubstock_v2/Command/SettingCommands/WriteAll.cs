using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.CommunicationCommands
{
    public class WriteAll : CommandBase
    {
        private readonly MainViewModel _mainViewModel;
        private readonly ICommunication _Communication;

        public WriteAll(MainViewModel mainViewModel, ICommunication communication) : base(communication)
        {
            _mainViewModel = mainViewModel;
            _Communication = communication;
        }

        public override void Execute(object? parameter)
        {
            throw new NotImplementedException();
        }
    }
}
