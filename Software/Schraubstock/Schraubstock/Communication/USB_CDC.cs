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
        SerialPort sPort;
        public USB_CDC()
        {

        }

        public List<byte> Data { get; private set; }
        private readonly List<byte> rxData = new List<byte>();

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
                MessageBox.Show($"Verbindung zu {sPort.PortName} konnte nicht hergestellt werden");
                return false;
            }
        }


        /// <summary>
        /// serial port data receive interrupt
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int counter = 0;
            byte[] buffer = new byte[5];

            try
            {
                for (int i = 0; i < 5; i++)
                {
                    buffer[i] = (byte)sPort.ReadByte();
                    counter++;
                }
            }
            catch { }

            rxData.Clear();
            for (int i = 0; i < counter; i++)
            {
                rxData.Add(buffer[i]);
            }
            IsDataReady = true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public List<byte> GetData()
        {
            return rxData;
        }


        private bool isDataReady;
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
                IsDataReady = false;
                sPort.Write(data2Write, 0, data2Write.Length);

                byte[] result = new byte[20];
                int timeout = 1000;
                while (!IsDataReady && (--timeout) > 0)
                {
                    Thread.Sleep(1);
                }

                if(timeout == 0)
                {
                    MessageBox.Show("Daten konnten nicht gelesen werden");
                }
                else
                {
                    result = rxData.ToArray();
                }

                //sPort.Read(result, 0, 20);

                return result;
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
