# -*- coding:utf8 -*-

import socket

HOST = ''
PORT = 24569
BUFSIZE = 1024
ADDR = (HOST, PORT)

recvsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
recvsock.bind(ADDR)
recvsock.listen(5)

while True:
    print 'waiting for connection...'
    sendsock, addr = recvsock.accept()
    print 'connect from', addr

    while True:
        data = sendsock.recv(1024)
        if not data:
            break
        print data
        sendsock.send("reply")
        #sendsock.close()
recvsock.close()
