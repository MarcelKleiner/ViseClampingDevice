using Schraubstock_v2.Communication;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Schraubstock_v2.Command.StatusUpdate;

public class UpdateStatus : CommandBase
{
    CancellationToken cancellation;
    private bool _IsRunning = true;

    public UpdateStatus(ICommunication communication, CancellationToken cancellationToken = default) : base(communication)
    {
        Run();
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
        byte[] statusReques = messageCreater.Create(Adresses.CommandAdress.REQUEST_STATUS, Adresses.Commands.CLOSE_ADDR) ?? throw new NullReferenceException();

        Task.Run(async () =>
        {
            while (_IsRunning || cancellation.IsCancellationRequested)
            {
                var result = await ExecuteRequesAsync(statusReques);
                await Task.Delay(1000);
            }
        }, cancellationToken);
    }







}
