import serial
import struct

USART_FLASH_HEADER = 0xAD1991DA
USART_FLASH_END = 0xDA9119AD

USART_FLASH_CMD = 0x00
USART_FLASH_FLAG = 0x01
USART_FLASH_DATA = 0xFF

USART_FLASH_SHAKE_1 = 0xDF
USART_FLASH_SHAKE_2 = 0xFD
USART_FLASH_SHAKE_3 = 0x19
USART_FLASH_ACK = 0x00
USART_FLASH_NACK = 0xFF

USART_FLASH_CMD_FLASH_DATA = 0x01  # // Flash data request
USART_FLASH_CMD_PACK_DATA = 0x02  # // data package
USART_FLASH_CMD_READ_DATA = 0x03  # // read data from flash

ser = serial.Serial("COM7", 115200, timeout=10)
handshake_count = 1

# handshake


def send_cmd(cmd, *args, handshake=0, wait_ack=True):
    try:
        data = struct.pack("<IB", USART_FLASH_HEADER, USART_FLASH_CMD)
        if len(args) != 0:
            l = 1
            for i in args:
                l += len(i)
            data += struct.pack("<IB", l, cmd)
            for i in args:
                data += i
        else:
            data += struct.pack("<IB", 0x01, cmd)
        data += struct.pack("<I", USART_FLASH_END)
        print("send cmd:", data)
        ser.write(data)
        if not wait_ack:
            return None
        data2 = struct.unpack("<IBIBI", ser.read(14))
        # print("rev: ", data2)
        return data2[0] == USART_FLASH_HEADER and data2[1] == USART_FLASH_CMD and data2[2] == 0x01 and data2[3] == (USART_FLASH_ACK if handshake == 0 else cmd) and data2[4] == USART_FLASH_END
    except Exception as e:
        print(e)
        return False


def send_flag(flag):
    data = struct.pack("<IBIBI", USART_FLASH_HEADER, USART_FLASH_FLAG, 0x01, flag, USART_FLASH_END)
    ser.write(data)


def send_data(data: bytes, size):
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


def write_file(file_path: str):
    if not send_cmd(USART_FLASH_CMD_FLASH_DATA):
        print("Flash command failed...")
        exit(-1)

    with open(file_path, 'rb') as f:
        data = f.read()
    print("Writing file...")
    print("File size: %d" % len(data))
    for i in range(0, len(data), 256):
        print("Flash data[%d:%d] to SPI Flash..." % (i, i+256))
        if not send_data(data[i:i+256], 256):
            print("Flash fatal..")
            exit(-1)

    send_flag(USART_FLASH_NACK)


def read_to_file(file_path: str, addr: int, size: int):
    if not send_cmd(USART_FLASH_CMD_READ_DATA, struct.pack("<II", addr, size)):
        print("Read command failed...")
        exit(-1)

    file = open(file_path, "wb")
    # if not send_data(struct.pack("<II", addr, size), 8):
    #     print("Read fatal...")
    #     exit(-1)

    send_data(struct.pack("<II", addr, size), 8)  # dummy data
    # print(ser.read())
    while True:
        data = ser.read(9)
        print(data)
        # header = struct.unpack("<IBI", data[:9])
        # # end = struct.unpack("<I", data[-4:])
        # print([hex(i) for i in header], )
        break


if __name__ == "__main__":
    print("Start handshake...")
    while handshake_count < 4:
        if not send_cmd(USART_FLASH_SHAKE_1, handshake=1):
            print("Excepiton: Handshake 1, try %d handshake..." %
                  handshake_count)
            handshake_count += 1
            continue

        if not send_cmd(USART_FLASH_SHAKE_2, handshake=1):
            print("Excepiton: Handshake 2, try %d handshake..." %
                  handshake_count)
            handshake_count += 1
            continue

        if not send_cmd(USART_FLASH_SHAKE_3, handshake=1):
            print("Excepiton: Handshake 3, try %d handshake..." %
                  handshake_count)
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

    # write_file(r"C:\Users\Administrator\Desktop\A36plus 开机图\Talkpod.bin")
    read_to_file(
        r"C:\Users\Administrator\Desktop\A36plus 开机图\Talkpod_read.bin", 0x00, 32768)

    print("Done!")
