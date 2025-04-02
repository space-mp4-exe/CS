import struct

# rotates integer a n times
def leftRotate(a, n):
    return ((a << n) | (a >> (32 - n))) & 0xFFFFFFFF


def sha1(data):
    # Pre-processing
    original_byte_len = len(data)
    original_bit_len = original_byte_len * 8
    data += b'\x80' # 1 to signal start of packing
    # add 0s to the end of the string
    while (len(data) + 8) % 64 != 0:
        data += b'\x00'
    # append length of string as 64 bit big endian integer
    data += struct.pack('>Q', original_bit_len) 
    
    # Initialize hash values
    h0, h1, h2, h3, h4 = (
        0x67452301,
        0xEFCDAB89,
        0x98BADCFE,
        0x10325476,
        0xC3D2E1F0,
    )
    
    # Process the message in successive 512-bit chunks
    for i in range(0, len(data), 64):
        # break into 16 32-bit words
        w = list(struct.unpack('>16I', data[i:i+64])) + [0] * 64
        # extend into 80 32-bit words
        for j in range(16, 80):
            w[j] = leftRotate(w[j-3] ^ w[j-8] ^ w[j-14] ^ w[j-16], 1)
        
        a, b, c, d, e = h0, h1, h2, h3, h4
        
        for j in range(80):
            if j < 20:
                f = (b & c) | ((~b) & d)
                k = 0x5A827999
            elif j < 40:
                f = b ^ c ^ d
                k = 0x6ED9EBA1
            elif j < 60:
                f = (b & c) | (b & d) | (c & d)
                k = 0x8F1BBCDC
            else:
                f = b ^ c ^ d
                k = 0xCA62C1D6
            
            # the part of the diagram on wikipedia with all the squares (addition mod 2^32)
            temp = (leftRotate(a, 5) + f + e + k + w[j]) & 0xFFFFFFFF
            e, d, c, b, a = d, c, leftRotate(b, 30), a, temp
        
        h0 = (h0 + a) & 0xFFFFFFFF
        h1 = (h1 + b) & 0xFFFFFFFF
        h2 = (h2 + c) & 0xFFFFFFFF
        h3 = (h3 + d) & 0xFFFFFFFF
        h4 = (h4 + e) & 0xFFFFFFFF
    
    return f'{h0:08x}{h1:08x}{h2:08x}{h3:08x}{h4:08x}'

# put string to hash here
data = b"Crypto"
hashResult = sha1(data)
print(hashResult)
 