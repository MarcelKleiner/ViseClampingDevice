using System.ComponentModel;

namespace Schraubstock_v2.Common;

public enum ErrorCode
{
    [Description("Kein Error")]
    E_NO_ERROR = 0x00,
    [Description("Flash Error")]
    E_FLASH_ERROR = 0x01,
    [Description("COM Error")]
    E_COM_ERROR = 0x02,
    [Description("USB Error")]
    E_USB_ERROR = 0x03,
    [Description("Interner Error")]
    E_UNKOWN_COMMAND_OR_ADDR_ERROR = 0x04,
    [Description("Keine Funkverbindung")]
    E_CONNECTION_LOST_ERROR = 0x05,
    [Description("CRC Error")]
    E_CRC_ERROR = 0x06,
    [Description("Unterspannung Error")]
    E_UNDERVOLTAGE_ERROR = 0x07,
    [Description("Unterspannung Warnung")]
    E_UNDERVOLTAGE_WARNING = 0x08,
    [Description("Überstrom Warnung")]
    E_OVERCURRENT_WARNING = 0x09,
    [Description("Überstrom Error")]
    E_OVERCURRENT_ERROR = 0x0A,
}
