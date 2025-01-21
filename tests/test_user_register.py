import socket
import struct

# Define the server address and port
SERVER_ADDRESS = '127.0.0.1'
SERVER_PORT = 6969

# Define the version and question number
VERSION = 1
QUESTION = 1

def main():
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        sock.connect((SERVER_ADDRESS, SERVER_PORT))
        print("Connected to server")

        # Create the packet with version and question number
        packet = (VERSION << 5) | (QUESTION << 2)
        sock.sendall(struct.pack('B', packet))
        print(f"Sent packet: {bin(packet)}")

        # Send the username length
        uname = "birnadin erick"
        uname_len = len(uname)
        sock.sendall(struct.pack('B', uname_len))
        print(f"Sent username length: {uname_len}")

        # Send the username
        sock.sendall(uname.encode('utf-8'))
        print(f"Sent username: {uname}")

        # Receive the response
        response = sock.recv(1)
        if response:
            response_byte = struct.unpack('B', response)[0]
            version = (response_byte & 0xE0) >> 5
            uid = (response_byte & 0x1C) >> 2
            print(f"Received response: {bin(response_byte)}")
            print(f"Version: {version}, UID: {uid}")
        else:
            print("No response received")

    finally:
        # Close the socket
        sock.close()
        print("Connection closed")

if __name__ == "__main__":
    main()