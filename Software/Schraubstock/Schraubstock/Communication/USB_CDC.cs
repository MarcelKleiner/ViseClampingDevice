using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Threading;
using System.Windows;

namespace Schraubstock.Communication
{
    internal class USB_CDC
    {
        private SerialPort? sPort;
        private List<byte> rxData = new List<byte>();
        private bool isDataReady;
        private string comPort = "";

        public enum ReadWrite
        {
            GET_SETTINGS = 0x01,
            GET_COMMAND = 0x02,
            GET_STATUS = 0x03,
            SEND_SETTINGS = 0x11,
            SEND_COMMAND = 0x12,
            SEND_STATUS = 0x13,

        }

        public bool IsDataReady
        {
            get
            {
                if (isDataReady)
                {
                    isDataReady = false;
                    return true;
                }
                return false;
            }
            set => isDataReady = value;
        }

        public bool IsConnected()
        {
            return sPort != null && sPort.IsOpen;
        }

        public string GetComPort()
        {
            return comPort;
        }

        public bool Connect(string comport)
        {
            sPort = new SerialPort
            {
                BaudRate = 115200,
                PortName = comport,
                Parity = Parity.None,
                StopBits = StopBits.One,
                DataBits = 8,
                ReadTimeout = 500,
                WriteTimeout = 500
            };
            try
            {
                sPort.Open();
                sPort.DataReceived += SPort_DataReceived;
                comPort = sPort.PortName;
                return true;
            }
            catch
            {
                MessageBox.Show($"Verbindung zu {sPort.PortName} konnte nicht hergestellt werden");
                return false;
            }
        }

        public bool Dissconnect()
        {
            if (sPort != null && sPort.IsOpen)
            {
                sPort.Dispose();
                return true;
            }
            return false;
        }

        private void SPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort port = (SerialPort)sender;
            if (port.BytesToRead == 0) { return; }

            byte[] buffer = new byte[port.BytesToRead];
            var result = port.Read(buffer, 0, port.BytesToRead);
            rxData = buffer.ToList();
            IsDataReady = true;
        }

        public byte[]? Write(byte register, ReadWrite readWrite, byte[]? data = null)
        {
            if (sPort == null || !sPort.IsOpen)
                return null;

            if (data != null && data.Length != 2)
                throw new Exception("data length must be 2");


            byte[] data2Write = new byte[7];
            data2Write[0] = 0x1F;
            data2Write[1] = 0x1F;
            data2Write[2] = (byte)readWrite;
            data2Write[3] = register;

            if (data != null)
            {
                for (int i = 0; i < 2; i++)
                {
                    data2Write[i + 4] = data[i];
                }
            }

            data2Write[6] = CRC8(data2Write);

            IsDataReady = false;

            sPort.Write(data2Write, 0, data2Write.Length);

            for (int i = 0; i < 1000; i++)
            {
                if (IsDataReady)
                    return rxData.ToArray();

                if (i == 1)
                    throw new TimeoutException();

                Thread.Sleep(1);
            }

            throw new Exception("Unknown error");
        }

        private static byte CRC8(byte[] data)
        {
            byte crc = 0xff;
            int i, j;
            for (i = 0; i < data.Length-1; i++)
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
