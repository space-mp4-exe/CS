from socket import *

# Create a TCP welcoming socket
welcomeSocket = socket(AF_INET, SOCK_STREAM)
# Bind it to the local IP and port 12000
serverIP = '127.0.0.1'
serverPort = 12000
serverAddress = (serverIP, serverPort)
welcomeSocket.bind(('', serverPort))
# Welcome socket begins listening for incoming TCP requests
# Allows up to 1 pending requests for connection in the queue
welcomeSocket.listen(1)
print('The server is ready to receive')

while True:
    # Server waits on accept() for incoming requests
    # A new connection socket is created on return
    connectionSocket, clientAddress = welcomeSocket.accept()
    clientIP, clientPort = clientAddress

    # Receive a byte string from the connection socket
    messageBytes = connectionSocket.recv(1024)
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
    connectionSocket.send(response.encode("utf-8"))

    # Close the connection socket to this client
    connectionSocket.close()
