using Schraubstock_v2.Adresses;
using Schraubstock_v2.Common;
using Schraubstock_v2.Logger;
using Serilog;

namespace Schraubstock_v2.Communication;

public class Message
{
    private readonly IInformer _informer;
    public Message(IInformer informer)
    {
        _informer = informer;
    }

    public byte[]? Create(CommandAdress command, Commands commands, string data = "")
    {
        try
        {
            byte[] txData;
            if (string.IsNullOrEmpty(data))
            {
                txData = new byte[] { 0x00, 0x00 };
            }
            else
            {
                txData = Converter.ToByteArray(data);
            }

            byte[] result = Create((byte)command, (byte)commands, txData);
            _informer.Inform(command, commands, data);
            return result;
        }
        catch (ArgumentOutOfRangeException ex)
        {
            Error.Show("Eingabe hat das falsche Format");
            Log.Error(ex.Message);
        }
        catch (Exception ex)
        {
            Error.Show("Fehler beim erstellen der Daten");
            Log.Error("Error while creating data to send {ex}", ex);
        }
        return default;
    }


    public byte[]? Create(CommandAdress command, RegisterAdress registerAddr, string data = "")
    {
        try
        {
            byte[] txData;
            if (string.IsNullOrEmpty(data))
            {
                txData = new byte[] { 0x00, 0x00 };
            }
            else
            {
                txData = Converter.ToByteArray(data);
            }

            byte[] result = Create((byte)command, (byte)registerAddr, txData);
            _informer.Inform(command, registerAddr, data);
            return result;
        }
        catch (ArgumentOutOfRangeException ex)
        {
            Error.Show("Eingabe hat das falsche Format");
            Log.Error(ex.Message);
        }
        catch (Exception ex)
        {
            Error.Show("Fehler beim erstellen der Daten");
            Log.Error("Error while creating data to send {ex}", ex);
        }
        return default;
    }

    private static byte[] Create(byte command, byte registerAddr, byte[]? data = default)
    {
        //data[0] = 0x1F
        //data[1] = deviceAddress
        //data[2] = command (readCommand, readSettings, readStatus, writeCommand...)
        //data[3] = reg addr (close, open, setTeach...)
        //data[4..5] = Payload
        //data[6] = crc

        if (data != null && data.Length != 2)
        {
            Log.Error("data length musst be null or 2");
            Error.Show("Es können nur genau 2 bytes übertragen werden");
        }

        byte[] result = new byte[7];

        result[0] = 0x1F;
        result[1] = 0x1F;   //device address ToDo maybe change to saved device address
        result[2] = (byte)command;
        result[3] = (byte)registerAddr;
        result[4] = ((byte)(data == null ? 0x00 : data[0]));
        result[5] = ((byte)(data == null ? 0x00 : data[1]));
        result[6] = Crc8.Calculate(result, 5);

        return result;
    }
}
