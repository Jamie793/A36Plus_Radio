import serial
import struct

USART_FLASH_HEADER = 0xAD1991DA
USART_FLASH_END = 0xDA9119AD

USART_FLASH_CMD = 0x00
USART_FLASH_DATA = 0xFF

USART_FLASH_SHAKE_1 = 0xDF
USART_FLASH_SHAKE_2 = 0xFD
USART_FLASH_SHAKE_3 = 0x19
USART_FLASH_ACK = 0x00
USART_FLASH_NACK = 0xFF

USART_FLASH_CMD_FLASH_DATA = 0x01
USART_FLASH_CMD_PACK_DATA = 0x02

ser = serial.Serial("COM7", 115200, timeout=0xFF)
handshake_count = 1

# handshake


def send_cmd(cmd, handshake=0):
    try:
        data = struct.pack("<IBIBI", USART_FLASH_HEADER, USART_FLASH_CMD,
                           0x01, cmd, USART_FLASH_END)
        print("send cmd:", data)
        ser.write(data)
        data2 = struct.unpack("<IBIBI", ser.read(14))
        # print("rev: ", data2)
        return data2[0] == USART_FLASH_HEADER and data2[1] == USART_FLASH_CMD and data2[2] == 0x01 and data2[3] == (USART_FLASH_ACK if handshake == 0 else cmd) and data2[4] == USART_FLASH_END
    except Exception as e:
        print(e)
        return False


def send_data(data, size):
    try:
        data2 = struct.pack("<IBI", USART_FLASH_HEADER, USART_FLASH_DATA,
                            size)
        data2 += data
        data2 += struct.pack("<I", USART_FLASH_END)
        # print("send data:", data)
        ser.write(data2)
        data3 = struct.unpack("<IBIBI", ser.read(14))
        # print("rev: ", data3)
        return data3[0] == USART_FLASH_HEADER and data3[1] == USART_FLASH_CMD and data3[2] == 0x01 and data3[3] == USART_FLASH_ACK and data3[4] == USART_FLASH_END
    except Exception as e:
        print(e)
        return False


def read_splash():
    with open(r"C:\Users\Administrator\Desktop\A36plus 开机图\Talkpod.bin", 'rb') as f:
        return f.read()


while handshake_count < 4:
    if not send_cmd(USART_FLASH_SHAKE_1, 1):
        print("Excepiton: Handshake 1, try %d handshake..." % handshake_count)
        handshake_count += 1
        continue

    if not send_cmd(USART_FLASH_SHAKE_2, 1):
        print("Excepiton: Handshake 2, try %d handshake..." % handshake_count)
        handshake_count += 1
        continue

    if not send_cmd(USART_FLASH_SHAKE_3, 1):
        print("Excepiton: Handshake 3, try %d handshake..." % handshake_count)
        handshake_count += 1
        continue
    else:
        break

if (handshake_count >= 4):
    print("Handshake failed...")
    exit(-1)

print("Handshake successful...")
print()
print()

if not send_cmd(USART_FLASH_CMD_FLASH_DATA):
    print("Flash command failed...")
    exit(-1)

data = read_splash()
# print(len(data))
for i in range(0, len(data), 256):
    print("Flash data[%d:%d] to SPI Flash..." % (i, i+256))
    if not send_data(data[i:i+256], 256):
        print("Flash fatal..")
        exit(-1)

print("Flash done!")
