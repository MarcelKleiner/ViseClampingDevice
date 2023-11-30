namespace Schraubstock_v2.Communication;

public interface ICommunication
{
    public bool Open(string portName);
    public bool Close();
    public bool IsConnected { get; }
    public Task<byte[]?> WriteData(byte[]? data);
}
