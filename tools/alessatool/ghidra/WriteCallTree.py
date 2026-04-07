#@author alessamothdream
#@category Memory of Alessa

import json

def visit_function(call_tree, func):
    func_name = func.getName()
    if func_name in call_tree:
        return
    out_nodes = list(func.getCalledFunctions(monitor))
    call_tree[func_name] = {
        "name": func_name,
        "address": "0x%s" % func.getEntryPoint(),
        "callees": map(lambda f : f.getName(), out_nodes)
    }
    for node in out_nodes:
        visit_function(call_tree, node)

def write_call_tree(call_tree, output_path):
    with open(output_path, "w") as output_file:
        json.dump(call_tree, output_file, indent=4)

def build_and_write_call_tree(call_tree_path):
    fm = currentProgram.getFunctionManager()
    call_tree = dict()
    for func in fm.getFunctions(True):
        visit_function(call_tree, func)
    write_call_tree(call_tree, call_tree_path)

def main():
    call_tree_file = askFile("Select call_tree.json", "Load")
    build_and_write_call_tree(call_tree_file.absolutePath)

main()
