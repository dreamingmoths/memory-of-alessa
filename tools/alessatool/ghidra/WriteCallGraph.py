#@author alessamothdream
#@category Memory of Alessa

import json

class CallGraphInfo():
    def __init__(self):
        self.call_graph = dict()
        self.visited = set()
        self.duplicates = set()

def visit_function(info, func):
    name, address = get_function_info(func)
    key = get_symbol_key(info, name, address)
    if key in info.visited:
        return
    info.visited.add(key)

    out_nodes = list(func.getCalledFunctions(monitor))
    call_graph = info.call_graph
    call_graph[key] = {
        "name": name,
        "address": "0x%s" % func.getEntryPoint(),
        "callees": map(lambda f : get_symbol_key(info, *get_function_info(f)), out_nodes)
    }
    for node in out_nodes:
        visit_function(info, node)

def get_function_info(func):
    name = func.getName()
    address = "0x%s" % func.getEntryPoint()
    return (name, address)

def get_symbol_key(info, name, address):
    if name in info.duplicates:
        return "%s (%s)" % (name, address)
    return name

def write_call_graph(call_graph, output_path):
    with open(output_path, "w") as output_file:
        json.dump(call_graph, output_file, indent=4)

def build_and_write_call_graph(call_graph_path):
    fm = currentProgram.getFunctionManager()

    info = CallGraphInfo()
    duplicates = info.duplicates

    seen = set()
    for func in fm.getFunctions(True):
        name = func.getName()
        if name in seen:
            duplicates.add(name)
        seen.add(name)

    for func in fm.getFunctions(True):
        visit_function(info, func)

    write_call_graph(info.call_graph, call_graph_path)

def main():
    call_graph_file = askFile("Select JSON file path", "Save")
    build_and_write_call_graph(call_graph_file.absolutePath)

main()
