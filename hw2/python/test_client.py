import socket
##import netifaces as ni
import random
import time

def main():
    #HOST = ni.ifaddresses('en0')[ni.AF_INET][0]['addr']
    HOST = "172.20.10.3"
    PORT = 65431

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    while True:
        cmd = "%d %d %d" % (random.randint(-100, 100), random.randint(-100, 100), random.randint(-100, 100))
        s.send(str.encode(cmd))
        time.sleep(0.5)

if __name__ == "__main__":
    main()