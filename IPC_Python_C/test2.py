import sys
import os
import sysv_ipc
import re

KEY = 1234
PY_TO_C = 2


class Posix_Op:
    def __init__(self):
        self.message_queue = sysv_ipc.MessageQueue(KEY, sysv_ipc.IPC_CREAT)
        self.message = None

    def send_message(self, message):
        self.message_queue.send(message.encode(), type=PY_TO_C)


Sender = Posix_Op()
Sender.send_message(f"Siuuuuuuuuuuuuuuuuuuuuuuuu!")