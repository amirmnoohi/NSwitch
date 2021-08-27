import json


class ARPTable:
    def __init__(self):
        self.DATA = self.__fetch()

    def __fetch(self):
        with open('Data/ARPTable.json', 'r') as infile:
            self.DATA = json.load(infile)
        return self.DATA

    def save(self):
        with open('Data/ARPTable.json', 'w') as outfile:
            json.dump(self.DATA, outfile)

    def findIPAddress(self, IPAdress):
        for i in self.DATA:
            if self.DATA[i]["IPAddress"] == IPAdress:
                return i
        return False

    def findHWAddress(self, HWAddress):
        for i in self.DATA:
            if self.DATA[i]["HWAddress"] == HWAddress.lower():
                return i
        return False

    def addRecord(self, address, HWaddress, iface):
        fa = self.findAddress(address)
        fh = self.findHWAddress(HWaddress)
        if fa and fh:
            if frozenset(fa).intersection(fh):
                return -1
            self.DATA[fa][2] = iface
            return fa
        if fa >= 0:
            self.DATA[fa][1] = HWaddress
            self.DATA[fa][2] = iface
            return fa
        if fh >= 0:
            self.DATA[0] = address
            self.DATA[2] = iface
            return fh

        self.DATA.append([address, HWaddress, iface])
        self.save()
        return self.DATA.__len__()

    def deleteRecord(self):
        pass

    def updateAddress(self):
        pass

    def updateHWAddress(self):
        pass
