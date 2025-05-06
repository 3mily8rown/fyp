#!/usr/bin/env python3
import os
import re
import sys
from subprocess import check_output, CalledProcessError

def demangle(sym):
    return check_output(["c++filt", sym]).decode().strip()

def sanitize_symbol(name):
    # Uppercase, replace non-alphanumeric with underscore
    return re.sub(r'\\W+', '_', name).upper()

def main():
    if len(sys.argv) != 3:
        print("generate_wasm_exports.py <input.wasm> <output.h>", file=sys.stderr)
        sys.exit(1)

    wasm_in = sys.argv[1]
    hdr_out = sys.argv[2]

    base = os.path.splitext(os.path.basename(wasm_in))[0]
    sym = f"{sanitize_symbol(base)}_EXPORT_NAMES"

    try:
        dump = check_output(["wasm-objdump", "-x", wasm_in], stderr=sys.stderr).decode("utf-8")
    except CalledProcessError as e:
        print(f"Error running wasm-objdump: {e}", file=sys.stderr)
        sys.exit(2)

    # Matches lines like: Export[  5] func[12] <_Z3fooii> -> "Z3fooii"
    pattern = re.compile(
        r'(?:Export\[\s*\d+\]|\s*-\s*)\s*func\[\d+\]\s+<[^>]+>\s+->\s+"([^"]+)"'
    )

    names = []
    for line in dump.splitlines():
        m = pattern.search(line)
        if m:
            names.append(m.group(1))

    with open(hdr_out, "w") as f:
        f.write("// AUTO-GENERATED — do not edit\n")
        f.write("#pragma once\n\n")
        f.write(f"static constexpr WasmExport {sym}[] = {{\n")
        for mangled in names:
            pretty = demangle(mangled).split('(')[0]
            f.write(f'  {{ "{pretty}", "{mangled}" }},\n')
        f.write("    nullptr  // sentinel\n")
        f.write("};\n")

if __name__ == "__main__":
    main()
