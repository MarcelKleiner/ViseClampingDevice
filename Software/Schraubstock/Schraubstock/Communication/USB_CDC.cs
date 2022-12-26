using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace Schraubstock.Communication
{
    internal class USB_CDC
    {
        private SerialPort? sPort;
        private List<byte> rxData = new List<byte>();
        private bool isDataReady;
        private string comPort;

        public enum ReadWrite
        {
            Write,
            Read
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
            return sPort == null ? false: sPort.IsOpen;
        }

        public string GetComPort()
        {
            return comPort;
        }

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
            if(sPort != null && sPort.IsOpen)
            {
                sPort.Dispose();
                return true;
            }
            return false;
        }

        private void SPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort port = (SerialPort)sender;
            if(port.BytesToRead == 0) { return; }

            byte[] buffer = new byte[port.BytesToRead];
            var result = port.Read(buffer, 0, port.BytesToRead);
            rxData = buffer.ToList();
            IsDataReady = true;
        }

        public byte[]? Write(byte register, ReadWrite readWrite, byte[]? data = null)
        {
            int length = data != null ? data.Length : 0;
            byte[] data2Write = new byte[length + 3];

            if (sPort.IsOpen)
            {
                data2Write[0] = (byte)readWrite;
                data2Write[1] = register;

                for (int i = 0; i < length; i++)
                {
                    data2Write[i + 2] = data[i];
                }

                data2Write[length + 2] = CRC8(data2Write);
                IsDataReady = false;
                sPort.Write(data2Write, 0, data2Write.Length);

                int timeout = 1000;
                while (!IsDataReady && (--timeout) > 0)
                {
                    Thread.Sleep(1);
                }

                if(timeout == 0)
                {
                    return null;
                }

                return rxData.ToArray(); 
            }
            return null;
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
