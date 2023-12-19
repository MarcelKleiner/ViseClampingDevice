namespace Schraubstock_v2.Common
{
    public static class Crc8
    {
        public static byte Calculate(byte[] data, byte length)
        {
            byte crc = 0xff;
            int i, j;
            for (i = 0; i < length; i++)
            {
                crc ^= data[i];
                for (j = 0; j < 8; j++)
                {
                    if ((crc & 0x80) != 0)
                        crc = (byte)((crc << 1) ^ 0x31);
                    else
                        crc <<= 1;
                }
            }
            return crc;
        }

    }
}
