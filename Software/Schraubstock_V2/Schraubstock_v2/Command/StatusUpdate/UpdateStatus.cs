using Schraubstock_v2.Common;
using Schraubstock_v2.Communication;
using Schraubstock_v2.ViewModel;
using System.Windows.Media;

namespace Schraubstock_v2.Command.StatusUpdate;

public class UpdateStatus : CommandBase
{
    private readonly MainViewModel _mainViewModel;
    CancellationToken cancellation;
    private bool _IsRunning = true;

    public UpdateStatus(MainViewModel viewModel, ICommunication communication, CancellationToken cancellationToken = default) : base(communication)
    {
        _mainViewModel = viewModel;
        Run(cancellationToken);
    }

    ~UpdateStatus()
    {
        _IsRunning = false;
    }

    public override void Execute(object? parameter)
    {
        //not implemented
        throw new NotImplementedException();
    }

    public void Run(CancellationToken cancellationToken = default)
    {
        Message messageCreater = new Message();
        byte[] statusReques = messageCreater.Create(Adresses.CommandAdress.REQUEST_STATUS, Adresses.Commands.READ_ALL_STATUS) ?? throw new NullReferenceException();

        Task.Run(async () =>
        {
            while (_IsRunning || cancellation.IsCancellationRequested)
            {
                if (!_communication.IsConnected)
                {
                    await Task.Delay(100);
                    continue;
                }

                var result = await ExecuteRequesAsync(statusReques);
                if (result == null || string.IsNullOrEmpty(result))
                {
                    continue;
                }

                UInt16 statusRaw = Convert.ToUInt16(result);
                byte[] status = BitConverter.GetBytes(statusRaw);

                ErrorCode errorCode = (ErrorCode)status[1];

                if (errorCode == ErrorCode.E_NO_ERROR)
                {
                    _mainViewModel.ErrorBackgroundColor = Brushes.LightGreen;
                }
                else
                {
                    _mainViewModel.ErrorBackgroundColor = Brushes.Red;
                }

                _mainViewModel.DriveStatusError = errorCode.GetEnumDescription();
                _mainViewModel.DriveStatusOpen = ((status[0] & 0x20) == 0x01) ? "Geöffnet" : "Geschlossen";
                _mainViewModel.DriveStatusRun = ((status[0] & 0x01) == 0x01) ? "Run" : "Stop";
                _mainViewModel.DriveStatusEnable = ((status[0] & 0x04) == 0x01) ? "Enable" : "Disable";
                await Task.Delay(500);
            }
        }, cancellationToken);
    }







}
