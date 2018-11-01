#!/bin/env python

from __future__ import print_function
import sys
from errno import EPERM, EAGAIN
import argparse

__all__ = ["login","hello_handler","add_handler","split_handler"]

sys.path.append('/usr/local/hello/py_package')
sys.path.append('@INSTALL_PATH@/py_package')

if sys.version_info[0] == 2:
    import codecs
    open = codecs.open

try:
    import hellotool as tool
except ImportError:
    print("hellotool may be not installed, please reinstall\n" + \
        "Or check which python version you use\n" + \
        "Or contact with administrator", file=sys.stderr)
    sys.exit(EAGAIN)

hello = None
verbose = False

def login(user=None, passwd=None):
    configure = locals()
    if verbose:
        print("login arguments: ", configure)
    global hello
    hello = tool.Hello()
    ret = hello.login(user, passwd)
    if not ret:
        print("user login failed", file=sys.stderr)
        return EPERM
    if verbose:
        print("{0} login successfully".format(user if user else 'hello'))
    return 0

def check(func):
    def wrapper(*args, **kwargs):
        info = {"user":"hello", "passwd":"hello"}
        ret = login(**info)
        if ret != 0:
            return ret
        return func(*args, **kwargs)
    return wrapper

# for json.load
def ascii_encode_dict(data):
    ascii_encode = lambda x: x.encode('ascii') if isinstance(x, unicode) else x
    return dict(map(ascii_encode, pair) for pair in data.items())

@check
def hello_handler(args):
    print(hello.hello())
    return 0

@check
def add_handler(args):
    values = args.values
    if verbose:
        print('add arguments: ', values)
    print(hello.add(values))
    return 0

#split in python
#re.split('[%s]'%d,str)
@check
def split_handler(args):
    str = args.str
    if verbose:
        print('split arguments: ', str)
    ret = hello.split(str, ' \t\n\r;.,-')
    for r in ret:
        print(r, end=' ')
    print()
    return 0

def parse_cmdargs(args=None):
    parser = argparse.ArgumentParser(description='hello tool')
    parser.add_argument('-v', '--version', action="store_true",
        help="display version")
    parser.add_argument('--verbose', '-vv', action="store_true",
        help="show verbose")
    sub = parser.add_subparsers(title='support subcommands')
    sub.required = False

    h = sub.add_parser('hello', help='hello')
    h.set_defaults(func=hello_handler)

    add = sub.add_parser('add', help='add numbers')
    add.add_argument('values', help='numbers', type=int, nargs='+')
    add.set_defaults(func=add_handler)

    split = sub.add_parser('split', help='split str')
    split.add_argument('str', help='string to split')
    split.set_defaults(func=split_handler)

    parsed_args = parser.parse_args(args)
    return parser, parsed_args

def main():
    if len(sys.argv)>1 and sys.argv[1]=="-v":
        print(sys.argv[0], tool.version())
        return 0
    parser, parsed_args = parse_cmdargs()
    if parsed_args.verbose:
        global verbose
        verbose = parsed_args.verbose
    if verbose:
        print("cmd arguments: ", parsed_args)
    # fix except in python3
    try:
        return parsed_args.func(parsed_args)
    except AttributeError:
        parser.print_help()
        return 0

if __name__ == "__main__":
    sys.exit(main())

