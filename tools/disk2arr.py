import struct
import os

class ByteStream:
    def __init__(self: 'ByteStream') -> None:
        self.bytes = b''
    
    def write_byte(self: 'ByteStream', value: int | bool) -> None:
        self.bytes += struct.pack('B', value)
    
    def write_bytes(self: 'ByteStream', bytes: bytes) -> None:
        self.bytes += bytes
        self.write_byte(0)

class Entry:
    def __init__(self: 'Entry', is_directory: bool, path: str, content: bytes) -> None:
        self.is_directory = is_directory
        self.path = path
        self.content = content
    
    def serialize(self: 'Entry') -> bytes:
        buffer = ByteStream()
        buffer.write_byte(self.is_directory)
        buffer.write_bytes(self.path.encode())
        buffer.write_bytes(self.content)
        
        return buffer.bytes

def main() -> None:
    disk = ByteStream()
    for path in os.listdir('../disk'):
        if '.' not in path:
            continue # TODO: directories are currently unsupported

        with open(f'../disk/{path}', 'rb') as file:
            entry = Entry(False, f'/{path}', file.read())
            disk.write_bytes(entry.serialize())
    
    array = 'uint8_t disk[] = { '
    for byte in disk.bytes:
        array += f'{hex(byte)}, '
    
    array = array[:-2]
    array += ' };'

    print(array)

if __name__ == '__main__':
    main()
