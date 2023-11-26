using System;

namespace Schraubstock.Tool
{
    internal class TypeConverter
    {

        public static byte[] Int16ToByte(short data)
        {
            byte[] result = new byte[2];
            result[0] = Convert.ToByte(data);
            result[1] = Convert.ToByte(data >> 8);
            return result;  
        }


        public static short ByteToInt16(byte[] data, int offset = 0)
        {
            short result = 0;   
            result = (short)(((data[offset + 1]) << 8) + data[offset + 0]);
            return result;
        }

    }
}
