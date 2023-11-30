using Schraubstock_v2.Common;
using Schraubstock_v2.Communication;
using System.Windows.Input;

namespace Schraubstock_v2.Command;

public abstract class CommandBase : ICommand
{
    public event EventHandler? CanExecuteChanged;

    private readonly bool _canExecute = true;

    protected static bool IsRunInternal = false;
    protected readonly ICommunication _communication;
    protected CommandBase(ICommunication communication)
    {
        _communication = communication;
    }

    public bool CanExecute(object? parameter)
    {
        return _canExecute;
    }

    public abstract void Execute(object? parameter);


    protected virtual void OnCanExecuteChanged()
    {
        CanExecuteChanged?.Invoke(this, EventArgs.Empty);
    }


    protected async Task<string> ExecuteRequesAsync(byte[]? data)
    {
        try
        {
            IsRunInternal = true;
            var result = await _communication.WriteData(data);

            if (result != null)
            {
                return Converter.FromByteArray(result);
            }
        }
        finally
        {
            IsRunInternal = false;
        }
        return "";
    }

    protected async Task ExecuteCommandAsync(byte[]? data)
    {
        try
        {
            IsRunInternal = false;
            var result = await _communication.WriteData(data);
        }
        finally
        {
            IsRunInternal = false;
        }
    }

}
