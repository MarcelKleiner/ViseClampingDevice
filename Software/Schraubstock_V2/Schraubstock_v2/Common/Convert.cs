namespace Schraubstock_v2.Common
{
    public static class Converter
    {
        public static byte[] ToByteArray(string input)
        {
            if (Int16.TryParse(input, out var output))
            {
                byte[] result = new byte[2];
                result[0] = Convert.ToByte(output & 0xFF);
                result[1] = Convert.ToByte(output >> 8);
                return result;
            }
            throw new ArgumentOutOfRangeException("the input is either not a number or is outside the range of a signed 16-bit Int ");
        }

        public static string FromByteArray(byte[] input)
        {
            short result = 0;
            result = (short)(((input[1]) << 8) + input[0]);
            return result.ToString();
        }
    }
}
