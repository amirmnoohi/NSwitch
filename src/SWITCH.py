from multiprocessing import Process
from Packenger import *

from lib import Interface
from lib import ARPTable


class SWITCH:
    """
    Switch Class
    """

    def __init__(self, interfaces=None):
        """
        To Define Interface To Work on
        :rtype: object
        :param interfaces:
        """
        self.interfaces = self.__set_interfaces(interfaces)
        self.ARPTable = ARPTable()

    def __set_interfaces(self, interfaces):
        if interfaces is None:
            return self.__find_interfaces()
        self.interfaces = dict.fromkeys(interfaces)
        for x in self.interfaces:
            self.interfaces[x] = Interface(x)
        return self.interfaces

    def __find_interfaces(self):
        """
        Find Available Interfaces
        :rtype: object
        """
        self.interfaces = dict.fromkeys(Interface.all_interfaces())
        for x in self.interfaces:
            self.interfaces[x] = Interface(x)
        return self.interfaces

    def run(self):
        """
        Start Switch To listen on each Interface
        """
        for interface in self.interfaces.keys():
            self.interfaces[interface].packenger = Packenger(interface)
        for interface in self.interfaces.keys():
            self.interfaces[interface].processor = Process(target=self.__start_interface, args=(interface,))
            self.interfaces[interface].processor.start()

    def __start_interface(self, interface):
        print("interface " + interface + " Started Successfully with Thread ID : " + str(
            self.interfaces[interface].processor.ident))
        self.interfaces[interface].packenger.listen(self.__process_packet)

    def __process_packet(self, interface, packet):
        setattr(self.__class__, "ethernet_process", Ethernet.process)
        self.ethernet_process(interface, packet, packet.data_bytes[0:14])
