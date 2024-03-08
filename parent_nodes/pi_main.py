from smbus2 import SMBus
import logging
import time

boards = {
    41:"Arduino UNO R4 WiFi",
    42:"Arduino Nano",
    43:"Raspberry Pi Pico",
    45:"ESP32 Dev Board",
    46:"Seeed XIAO ESP32C3",
    47:"Seeed nRF52840 Sense",
    00:"TinyTILE",
    48:"STM32F401CCUX",
    49:"Pro Micro 32u4",
    50:"D1 Mini ESP8266",
    51:"Teensy 4.0",
    52:"ItsyBitsy M0",
    53:"ItsyBitsy M4",
    54:"STM32G474CEU6",
    55:"STM32F103RCT6"
    }

def scan(force=False):
    devices = []
    for addr in range(0x03, 0x77 + 1):
        read = SMBus.read_byte, (addr,), {'force':force}
        write = SMBus.write_byte, (addr, 0), {'force':force}

        for func, args, kwargs in (read, write):
            try:
                with SMBus(1) as bus:
                    data = func(bus, *args, **kwargs)
                    devices.append(addr)
                    break
            except OSError as expt:
                if expt.errno == 16:
                    # just busy, maybe permanent by a kernel driver or just temporary by some user code
                    pass

    return devices

def read_from_address(bus,addr):
    try:
        data = bus.read_i2c_block_data(addr,0,19)
    except:
        return 0
    try:
        num = int(bytes(data).decode('utf-8'))
    except Exception as e:
        # logging.warn(e)
        num = 0 
    return num

def update_all_boards(bus):
    for i, addr in enumerate(boards):
        board_name = boards[addr]
        val = read_from_address(bus,addr)
        if val != 0:
            print(f'Received {val} from {board_name} board on address {addr}')
        else:
            continue
def main():
    bus = SMBus(1)
    update_all_boards(bus)

if __name__ == "__main__":
    main()

# bus = SMBus(1)
# print('Present devices')
# for addr in scan(force=True):
#     print('{:02X}'.format(addr))


# bus = SMBus(1)
# for i in range(10):
#     num = read_from_address(bus,43)
#     if num != 0:
#         print(num)
#     time.sleep(0.05)
# bus.close()
