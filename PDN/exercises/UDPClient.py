from socket import *
# Create a UDP socket
clientSocket = socket(AF_INET, SOCK_DGRAM)
# Binding a socket is optional on the client side
clientSocket.bind(('127.0.0.1', 10000))
# Input a message and encode it to a byte string in the UTF-8 format
message = input('Input message to send, or "exit" to quit: ')
while message.lower() != 'exit':
    messageBytes = message.encode("utf-8")
    # Send a message through the client socket
    # The destination is specified by a tuple of IP and port
    serverIP = '127.0.0.1'
    serverPort = 12345
    serverAddress = (serverIP, serverPort);
    clientSocket.sendto(messageBytes, serverAddress)
    # Receive a byte string up to 2048 bytes long from the client socket
    # The sender information is attached with the message
    modifiedMessageBytes, serverAddress = clientSocket.recvfrom(2048)
    modifiedMessage = modifiedMessageBytes.decode("utf-8")
    serverIP, serverPort = serverAddress
    print(f'message from {serverIP}:{serverPort} = {modifiedMessage}')
    message = input('Input message to send, or "exit" to quit: ')
clientSocket.close()