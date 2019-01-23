# encoded_flatbuffer_message
Example program to encode and decode a flatbuffer message with OpenSSL.

It just creates a message, encodes it using AES, writes to file, then reads this file again and decodes it.

If you were serious about security you wouldn't store the key in plaintext in the program.
