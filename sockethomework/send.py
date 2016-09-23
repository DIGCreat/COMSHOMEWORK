#!/usr/bin/env python
# -*- coding:utf8 -*-

import socket

HOST = 'localhost'
PORT = 24569
BUFSIZE = 1024
ADDR = (HOST, PORT)

sendsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sendsock.connect(ADDR)

while True:
    data = raw_input('>')
    if not data:
        break
    sendsock.send(data)
    data = sendsock.recv(BUFSIZE)
    if not data:
        break
    print data
sendsock.close()
