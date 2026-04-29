from socket import *
# Create a UDP socket
serverSocket = socket(AF_INET, SOCK_DGRAM)
# Bind the socket to the local IP and port 12345
serverIP = '127.0.0.1'
serverPort = 12345
serverAddress = (serverIP, serverPort);
serverSocket.bind(serverAddress)
print('The server is ready to receive')
while True:
    # Receive a byte string up to 2048 bytes long from the socket
    # The sender address is attached with the message
    messageBytes, clientAddress = serverSocket.recvfrom(2048)
    clientIP, clientPort = clientAddress
    # decode the byte string to a string object using the UTF-8 format
    clientMessage = messageBytes.decode("utf-8")
    print(f'message from {clientIP}:{clientPort} = {clientMessage}')
    # Send a message encoded in the UTF-8 format through the socket
    message = input('Input message to send: ')
    serverSocket.sendto(message.encode("utf-8"), clientAddress)