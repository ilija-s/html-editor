import subprocess
import os
import sys

def isccppfile(filename):
    return filename.endswith('.h') \
        or filename.endswith('.c') \
        or filename.endswith('.hpp') \
        or filename.endswith('.cpp') \

if __name__ == "__main__":
    args = sys.argv[1:]
    if len(args) < 1:
        print('Usage: python3 run-clang-format.py <dir>')
        exit(1)

    dir   = args[0]

    for dir, _, files in os.walk(dir):
        for filename in files:
            filepath = dir + '/' + filename
            if isccppfile(filename):
                subprocess.run('clang-format -i {}'.format(filepath), shell=True)
