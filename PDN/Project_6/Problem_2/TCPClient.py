from socket import *

# Create a TCP socket
clientSocket = socket(AF_INET, SOCK_STREAM)
# Connect to the server
serverIP = '127.0.0.1'
serverPort = 12000
serverAddress = (serverIP, serverPort)

message = input('Enter comma-separated numbers, or "exit" to quit: ')
while message.lower() != 'exit':
    # A new connection must be made each time since the server closes
    # the connection socket after each response
    clientSocket = socket(AF_INET, SOCK_STREAM)
    clientSocket.connect(serverAddress)

    # Send the comma-separated numbers to the server
    clientSocket.send(message.encode("utf-8"))

    # Receive the product (or error) from the server
    responseBytes = clientSocket.recv(1024)
    response = responseBytes.decode("utf-8")

    if response.startswith("ERROR"):
        print(f'Server error: {response}')
    else:
        print(f'Response from Server: {response}')

    clientSocket.close()
    message = input('Enter comma-separated numbers, or "exit" to quit: ')
