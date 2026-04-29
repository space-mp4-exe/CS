from socket import *
# Create a TCP socket
clientSocket = socket(AF_INET, SOCK_STREAM)
# Connect to a server process using a tuple of IP and port
serverIP = '156.110.247.18'
serverPort = 80
serverAddress = (serverIP, serverPort)
clientSocket.connect(serverAddress)
# Send a byte string to the client socket
request = "GET / HTTP/1.1\r\nHost: 156.110.247.18\r\n\r\n"
clientSocket.send(request.encode("utf-8"))
# Receive a byte string from the client socket
modifiedMessageBytes = clientSocket.recv(1024)
print('From Server: ', modifiedMessageBytes.decode("utf-8"))
clientSocket.close()


