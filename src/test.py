import netmap
import time
from Packenger import *

nm = netmap.NetmapDesc('netmap:ens160')
txr = nm.transmit_rings[0]
num_slots = txr.num_slots
for i in range(num_slots):
    pkt = str(Ethernet_Protocols("\xff" * 6, "\xaa" * 6, 0x0806)) + \
          str(ARP("\xbb" * 6, "\x0a\x01\x00\x01", "\xcc" * 6, "\x99" * 4)) + str(i)
    txr.slots[i].buf[0:len(pkt)] = pkt
    txr.slots[i].len = len(pkt)

# transmit at maximum speed until Ctr-C is pressed
cur = txr.cur
for i in range(600):
    # n = txr.tail - cur  # avail
    # if n < 0:
    #     n += num_slots
    # if n > 1:
    #     n = 1
    cur += 1
    if cur >= num_slots:
        cur -= num_slots
    txr.cur = txr.head = cur  # lazy update txr.cur and txr.head
    nm.txsync()

