import socket

def connection(ip:str, port:int):
    """Create and connect the client to a tcp_socket server

    Args:
        ip (str): Ip of the machine
        port (int): Port of the machine

    Returns:
        socket: = socket object
    """

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    client_socket.connect((ip, port))

    return client_socket