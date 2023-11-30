using Schraubstock_v2.Common;
using Schraubstock_v2.Logger;
using Serilog;
using System.IO.Ports;

namespace Schraubstock_v2.Communication;

internal class UsbCdc : ICommunication
{
    private const int _DataLength = 7;
    private const int _timeoutMilliseconds = 4000;
    private readonly SerialPort _serialPort;
    private readonly IInformer _informer;

    public bool IsConnected => _serialPort != null && _serialPort.IsOpen;

    public UsbCdc(IInformer informer)
    {
        _serialPort = new SerialPort();
        _informer = informer;
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

    public async Task<byte[]?> WriteData(byte[]? data)
    {
        if (!IsDeviceConnected() || data == null)
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

        var result = await ReadResponse();
        if (result != null)
        {
            _informer.InformSuccess();
        }

        return result;
    }

    private async Task<byte[]?> ReadResponse()
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

                    return new byte[] { result[5], result[6] };
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
        _informer.InformFailure("Zeitüberschreitung der anforderung");
        return null;
    }



    private bool IsDeviceConnected()
    {
        if (!IsConnected)
        {
            _informer.Inform("Kein Device verbunden");
            Log.Error("No Device connected");
            return false;
        }
        return true;
    }
}
