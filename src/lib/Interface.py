import netifaces as ni
from Packenger import *


class Interface:
    def __init__(self, interface, packenger=None, processor=None):
        # type: (str, Packenger or None, Thread or None) -> None
        self.NETLINK = ni.ifaddresses(interface)[ni.AF_LINK][0]
        self.INET = ni.ifaddresses(interface)[ni.AF_INET][0]
        self.packenger = packenger
        self.processor = processor

    @staticmethod
    def all_interfaces():
        return [x.encode() for x in ni.interfaces() if x != 'lo']