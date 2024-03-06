from smbus2 import SMBus

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

# bus = SMBus(1)
print('Present devices')
for addr in scan(force=True):
    print('{:02X}'.format(addr))


bus = SMBus(1)

data = bus.read_block_data(0x2b,0x00)
print(data)
print(data.decode('utf-8'))