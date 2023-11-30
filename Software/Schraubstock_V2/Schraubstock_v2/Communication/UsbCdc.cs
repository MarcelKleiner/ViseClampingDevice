using Schraubstock_v2.Common;
using Schraubstock_v2.Logger;
using Serilog;
using System.IO.Ports;

namespace Schraubstock_v2.Communication;

internal class UsbCdc : ICommunication
{
    private const int _DataLength = 7;
    private const int _timeoutMilliseconds = 2000;
    private readonly SerialPort _serialPort;
    private readonly IInformer _informer;

    private Semaphore _semaphore;

    public bool IsConnected => _serialPort != null && _serialPort.IsOpen;

    public UsbCdc(IInformer informer)
    {
        _serialPort = new SerialPort();
        _informer = informer;
        _semaphore = new(0, 1);
    }

    public bool Close()
    {
        if (!_serialPort.IsOpen)
        {
            return false;
        }

        try
        {
            _serialPort.Close();
            _informer.Inform($"Getrennt {_serialPort.PortName}");
        }
        catch (Exception ex)
        {
            Log.Error("Could not close Serialport {@ex}", ex.Message);
            _informer.Inform("Verbindung konnte nicht getrennt werden");
            return false;
        }
        return true;
    }

    public bool Open(string portName)
    {
        if (_serialPort.IsOpen)
        {
            Close();
            return true;
        }
        try
        {
            _serialPort.BaudRate = 38400;
            _serialPort.Parity = Parity.None;
            _serialPort.StopBits = StopBits.One;
            _serialPort.PortName = portName;
            _serialPort.DataBits = 8;
            _serialPort.Open();
            _informer.Inform($"Verbunden {_serialPort.PortName}/{_serialPort.BaudRate}");
        }
        catch (Exception ex)
        {
            Log.Error("Could not open Serialport {@ex}", ex.Message);
            _informer.Inform("Es konnte keine Verbindung zum Gerät hergestellt werden");
            return false;
        }
        return true;
    }

    public async Task<byte[]?> WriteData(byte[]? data, bool inform = true)
    {
        _semaphore.WaitOne(3000);
        try
        {
            if (!IsDeviceConnected(inform) || data == null)
            {
                return default;
            }

            if (data.Length != _DataLength)
            {
                _informer.InformFailure("Falsche Datengrösse");
                _informer.Inform("Daten müssen genau 7 byte gross sein");

                Log.Error("wrong datasize");
                return null;
            }

            _serialPort.Write(data, 0, data.Length);

            var result = await ReadResponse(inform);
            if (result != null && inform)
            {
                _informer.InformSuccess();
            }
            return result;
        }
        finally
        {
            _semaphore.Release();
        }
    }

    private async Task<byte[]?> ReadResponse(bool inform = true)
    {
        List<byte> result = [];
        DateTime startTime = DateTime.Now;

        while ((DateTime.Now - startTime).TotalMilliseconds < _timeoutMilliseconds)
        {
            if (_serialPort.BytesToRead > 0)
            {
                result.Add((byte)_serialPort.ReadByte());

                if (result.Count == 7 && _serialPort.BytesToRead == 0)
                {
                    if (Crc8.Calculate(result.ToArray(), 6) != result[6])
                    {
                        _informer.InformFailure("CRC Error");
                        return null;
                    }

                    return new byte[] { result[4], result[5] };
                }
                else if (result.Count == 7 && _serialPort.BytesToRead != 0)
                {
                    _ = _serialPort.ReadExisting();
                    Log.Error("Unknon datalength received");
                }
            }

            await Task.Delay(10); // Delay to avoid busy waiting
        }
        _ = _serialPort.ReadExisting();
        if (inform)
        {
            _informer.InformFailure("Zeitüberschreitung der anforderung");
        }
        return null;
    }



    private bool IsDeviceConnected(bool inform = true)
    {
        if (IsConnected)
        {
            return true;
        }

        if (inform)
        {
            _informer.Inform("Kein Device verbunden");
        }
        Log.Error("No Device connected");
        return false;
    }
}
