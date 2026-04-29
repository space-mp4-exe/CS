from socket import *

# Create a UDP socket
clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.bind(('127.0.0.1', 10000))

serverIP = '127.0.0.1'
serverPort = 12345
serverAddress = (serverIP, serverPort)

message = input('Enter comma-separated numbers, or "exit" to quit: ')
while message.lower() != 'exit':
    # Send the message to the server
    clientSocket.sendto(message.encode("utf-8"), serverAddress)

    # Receive the product (or error) from the server
    responseBytes, serverAddress = clientSocket.recvfrom(2048)
    response = responseBytes.decode("utf-8")
    serverIP, serverPort = serverAddress

    if response.startswith("ERROR"):
        print(f'Server error: {response}')
    else:
        print(f'Response from Server: {response}')

    message = input('Enter comma-separated numbers, or "exit" to quit: ')

clientSocket.close()
