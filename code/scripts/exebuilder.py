import shutil
import commands

MAIN_TEMPLATE_FILEPATH   = "./code/src/main.template.c"
MAIN_GENERATED_FILE_PATH = "./code/src/main.generated.c"
OPERATIONS_PLACEHOLDER   = "<OPERATIONS>"
EXE_FILEPATH = "./main.generated.exe"

def create_main_c(ops): 
    shutil.copyfile(MAIN_TEMPLATE_FILEPATH, MAIN_GENERATED_FILE_PATH)
    _inplace_change(MAIN_GENERATED_FILE_PATH, OPERATIONS_PLACEHOLDER, _create_ops_string(ops))
    
def create_exe(ops):
    create_main_c(ops)

    (status, output) = commands.getstatusoutput(f"gcc {MAIN_GENERATED_FILE_PATH} -o {EXE_FILEPATH}")

    if (status != 0):
        print(f"Compile filed with status {status}:\n{output}")
    
def _create_ops_string(ops):
    return ";\n".join([op.getMacro() for op in ops]) + ";\n"

def _inplace_change(filename, old_string, new_string):
    # Safely read the input filename using 'with'
    with open(filename) as f:
        s = f.read()
        if old_string not in s:
            print('"{old_string}" not found in {filename}.'.format(**locals()))
            exit(1)

    # Safely write the changed content, if found in the file
    with open(filename, 'w') as f:
        s = s.replace(old_string, new_string)
        f.write(s)