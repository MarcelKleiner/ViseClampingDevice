namespace Schraubstock_v2.Adresses;

public enum CommandAdress : byte
{
    SEND_SETTINGS = 0x11,
    SEND_COMMAND = 0x12,

    REQUEST_STATUS = 0x05,
    REQUEST_SETTINGS = 0x06,

    RECEIVE_SETTINGS = 0x01,
    RECEIVE_COMMAND = 0x02,
    RECEIVE_STATUS = 0x03
}
