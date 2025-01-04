import struct
import time
from datetime import datetime
import socket

def main():
    HOST = "127.0.0.1"
    PORT = 6969

    byte_to_send = bytes([0b00101010])

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            print(f"Connected to {HOST}:{PORT}")

            print(f"Sending byte: {byte_to_send.hex()}")
            s.sendall(byte_to_send)

            response = s.recv(1024)
            if len(response) < 2:
                print("failed to recv")
                return

            print("Response (hex):", response.hex())

            first_byte = response[0]
            print("First byte (binary):", bin(first_byte)[2:].zfill(8))

            version = (first_byte & 0b11100000) >> 5
            print("version byte:", int(version))

            players_num = (first_byte & 0b00011111)
            print("players num:", int(players_num))

            timestamp_value = struct.unpack(">Q", response[1:])[0]
            human_readable_time = datetime.fromtimestamp(timestamp_value)
            print("game start: ", human_readable_time)

    except ConnectionRefusedError:
        print("Failed to connect to the server. Is it running?")
    except Exception as e:
        print("An error occurred:", e)

if __name__ == "__main__":
    main()

