#@author alessamothdream
#@category Memory of Alessa

import os
import re
from ghidra.program.model.symbol import SourceType

def loadSymbolFile(symbol_addrs_path):
    if not os.path.exists(symbol_addrs_path):
        printerr("File not found: {}".format(symbol_addrs_path))
        return

    addr_factory = currentProgram.getAddressFactory()
    space = addr_factory.getDefaultAddressSpace()
    symbol_table = currentProgram.getSymbolTable()

    count = 0

    with open(symbol_addrs_path, 'r') as file:
        for line in file:
            line = line.strip()

            # ignore comments
            if "=" not in line or ";" not in line:
                continue
            if line.startswith("//") or line.startswith("#"):
                continue

            # get symbol name and address
            contents, _ = line.split(";")
            name, addr_str = contents.split("=")
            name = name.strip()
            addr_str = addr_str.strip()

            addr_int = int(addr_str, 16)
            addr = space.getAddress(addr_int)

            existing = symbol_table.getSymbols(addr)
            for sym in existing:
                symbol_table.removeSymbolSpecial(sym)

            symbol_table.createLabel(
                addr,
                name,
                currentProgram.getGlobalNamespace(),
                SourceType.USER_DEFINED
            )

            print("Created label {} at {}".format(name, addr))
            count += 1

    print("\nImported {} symbols.".format(count))

def main():
    symbol_addrs_file = askFile("Select symbol_addrs.txt", "Load")
    loadSymbolFile(symbol_addrs_file.absolutePath)

main()
