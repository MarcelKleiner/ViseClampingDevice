using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Schraubstock.Communication
{
    internal class USB_CDC
    {
        SerialPort sPort;
        public USB_CDC()
        {

        }

        public List<byte> Data { get; private set; }
        public bool IsDataReady { get; private set; }

        public bool Connect(string comport)
        {
            sPort = new SerialPort();

            sPort.BaudRate = 115200;
            sPort.PortName = comport;
            sPort.Parity = Parity.None;
            sPort.StopBits = StopBits.One;
            sPort.DataBits = 8;
            sPort.ReadTimeout = 500;
            sPort.WriteTimeout = 500;
            try
            {
                sPort.Open();
                sPort.DataReceived += SPort_DataReceived;
                return true;
            }
            catch
            {
                return false;
            }
        }

        private void SPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //Data.Add(Convert.ToByte(sPort.ReadByte()));
        }


        public byte[]? Write(byte register, byte readWrite, byte[]? data)
        {
            int length = data != null ? data.Length : 0;
            byte[] data2Write = new byte[length + 3];

            if (sPort.IsOpen)
            {
                data2Write[0] = readWrite;
                data2Write[1] = register;

                for (int i = 0; i < length; i++)
                {
                    data2Write[i + 2] = data[i];
                }

                data2Write[length + 2] = CRC8(data2Write);

                sPort.Write(data2Write, 0, data2Write.Length);

                byte[] result = new byte[5];
                sPort.Read(result, 0, 5);

                return result;
            }
            return null;
        }

        private bool IsPortOpen()
        {
            return sPort.IsOpen;
        }

        private byte CRC8(byte[] data)
        {
            byte crc = 0xff;
            int i, j;
            for (i = 0; i < data.Length; i++)
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
