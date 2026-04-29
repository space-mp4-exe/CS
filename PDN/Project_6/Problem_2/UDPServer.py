from socket import *

# Create a UDP socket
serverSocket = socket(AF_INET, SOCK_DGRAM)
# Bind the socket to the local IP and port 12345
serverIP = '127.0.0.1'
serverPort = 12345
serverAddress = (serverIP, serverPort)
serverSocket.bind(serverAddress)
print('The server is ready to receive')

while True:
    # Receive a byte string up to 2048 bytes long from the socket
    messageBytes, clientAddress = serverSocket.recvfrom(2048)
    clientIP, clientPort = clientAddress
    clientMessage = messageBytes.decode("utf-8")
    print(f'Message from {clientIP}:{clientPort} = {clientMessage}')

    # Parse and compute the product of the comma-separated numbers
    try:
        numbers = [float(n.strip()) for n in clientMessage.split(",")]
        if len(numbers) == 0:
            raise ValueError("No numbers provided.")
        product = 1
        for n in numbers:
            product *= n
        # Return an integer if the product is a whole number
        response = str(int(product) if product.is_integer() else product)
    except ValueError:
        response = f'ERROR: "{clientMessage}" is not a valid comma-separated list of numbers.'

    print(f'Sending response: {response}')
    serverSocket.sendto(response.encode("utf-8"), clientAddress)
