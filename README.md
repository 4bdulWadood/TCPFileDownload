# TCPFileDownload
File download application based on TCP. A file transfer application based on TCP was implemented. 
After establishing a TCP connection between the client and the server, the user on the client
side enters the filename to the terminal, the client retrieves the filename and sends the name
to the server. When the server receives the filename, it will try to open the requested file. If
the file opening is successful, the server will send the file to the client; if it is not successful,
the server will send back an error message. Note that since the file size may be greater than
the packet size, the server may need to send multiple packets until all the data are sent. The
server closes the TCP connection after the transmission of the file or error message. On the
client side, the client must call read repeatedly until the end of transmission. To the client,
the closing of the TCP connection marks the end of the transmission. The following Figure
illustrates the case where the download is successful.

II. Additional Requirements
1. The maximum number of bytes carried by a packet is 100;
2. The file size must be greater than 100 bytes;

