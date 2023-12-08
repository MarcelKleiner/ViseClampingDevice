﻿using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;

namespace Schraubstock_v2.Command.CommunicationCommands
{
    public class WriteOverCurrentError : CommandBase
    {
        private readonly MainViewModel _mainViewModel;

        public WriteOverCurrentError(MainViewModel mainViewModel, ICommunication communication) : base(communication)
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
            Adresses.CommandAdress.SEND_SETTINGS,
            Adresses.RegisterAdress.OVER_CURRENT_ERROR_ADDR, _mainViewModel.OverCurrentError);

            await ExecuteCommandAsync(data);
        }
    }
}
