namespace Schraubstock_v2.Adresses;

public enum Commands : byte
{
    None = 0x00,
    CLOSE_ADDR = 0x01,
    OPEN_ADDR = 0x02,
    TEACH_ADDR = 0x03,
    RESET_ADDR = 0x04,
    ENABLE_ADDR = 0x05,
    DISABLE_ADDR = 0x06,
    STOP_ADDR = 0x07,
    READ_ALL_STATUS = 0x08,

    UPLOAD_SETTINGS_ADDR = 0x10,
    COBOT_RESET_ADDR = 0x11,
}
