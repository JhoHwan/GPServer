using Google.FlatBuffers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Flatbuffer
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    struct PacketHeader
    {
        public ushort Size;
        public PacketContent Type;

    }

    public static class PacketUtil
    {
        public static byte[] MakeSendBuffer<T>(FlatBufferBuilder builder, PacketContent type, Offset<T> message) where T : struct
        {
            var packet = Packet.CreatePacket(builder, type, message.Value);

            builder.Finish(packet.Value);

            byte[] buffer = builder.SizedByteArray();

            byte[] header = StructToBytes(new PacketHeader { Size = (ushort)(buffer.Length + Marshal.SizeOf(typeof(PacketHeader))), Type = type });

            byte[] sendBuffer = new byte[header.Length + buffer.Length];

            Array.Copy(header, 0, sendBuffer, 0, header.Length);

            Array.Copy(buffer, 0, sendBuffer, header.Length, buffer.Length);

            return sendBuffer;
        }

        public static Packet MakePacket(byte[] recv)
        {
            if (recv.Length < 4)
            {
                throw new ArgumentException("The recv array is too short.");
            }

            var sag = new ArraySegment<byte>(recv, 0, 3);
            var header = BytesToStruct<PacketHeader>(sag);

            if (header.Size != recv.Length)
            {
                throw new Exception("Packet Size Unmatch!");
            }

            var buf = new ArraySegment<byte>(recv, 3, recv.Length - 3).ToArray(); // Adjusted the length

            ByteBuffer buffer = new ByteBuffer(buf);
            Packet packet = Packet.GetRootAsPacket(buffer);

            return packet;
        }

        public static byte[] StructToBytes<T>(T structure) where T : struct
        {
            int size = Marshal.SizeOf(typeof(T));
            byte[] bytes = new byte[size];

            IntPtr ptr = Marshal.AllocHGlobal(size);
            try
            {
                Marshal.StructureToPtr(structure, ptr, false);
                Marshal.Copy(ptr, bytes, 0, size);
            }
            finally
            {
                Marshal.FreeHGlobal(ptr);
            }

            return bytes;
        }

        public static T BytesToStruct<T>(ArraySegment<byte> bytes) where T : struct
        {
            int size = Marshal.SizeOf(typeof(T));
            if (bytes.Count != size)
                throw new ArgumentException("바이트 배열의 크기가 구조체 크기와 다릅니다.");

            IntPtr ptr = Marshal.AllocHGlobal(size);
            try
            {
                Marshal.Copy(bytes.ToArray(), 0, ptr, size);
                return Marshal.PtrToStructure<T>(ptr);
            }
            finally
            {
                Marshal.FreeHGlobal(ptr);
            }
        }
    }
}
