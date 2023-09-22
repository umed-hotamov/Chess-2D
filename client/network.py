import socket

class Network():
    def __init__(self):
        self.host = '127.0.0.1'
        self.port = 1111 
        self.data_size = 1024

    def connect_to_server(self):
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client.connect((self.host, self.port))

        try:
            self.client.connect((self.host, self.port))
        except Exception as err:
            print(f'Connection error with exception: {err}')

        return self.client

    def send_request(self, data):
        try:
            self.client.send(data.encode())
        except Exception as err:
            print(f'Send error with exception: {err}')

    def get_response(self):
        response = None
        try:
            response = self.client.recv(self.data_size).decode()
        except Exception as err:
            print(f'Recv error with exception: {err}')

        return response

    def close_connection(self):
        self.client.close()
