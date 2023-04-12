import os
import sysv_ipc
import numpy as np
import struct

KEY = 1234
C_TO_PY = 2

try:
    mq = sysv_ipc.MessageQueue(KEY, sysv_ipc.IPC_CREAT)

    while True:
        message, mtype = mq.receive(type = C_TO_PY)
        print("*** New message received ***")
        print(f"Receive message: {message.decode()}")

except sysv_ipc.ExistentialError:
    print("ERROR: message queue creation failed")