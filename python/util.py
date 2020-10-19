import json
import os
from argparse import Namespace
import random
import string
from time import sleep


def fwrite(file, date):
    if not date:
        date = "None"
    if date == "void":
        date = ""

    try:
        f = open(file, "w")
        f.write(date)
        f.close()
    except:
        None


def fread(file):
    reading = "0"
    for n in range(100):

        if os.path.isfile(file):
            f = open(file, "r")
            reading = str(f.read().strip())
            f.close()

            if reading:
                break

        else:
            break

        sleep(0.07)

    return reading


def jread(file):
    return json.loads(
        fread(file),
        object_hook=lambda d: Namespace(**d)
    )


def jwrite(file, data):
    info = json.dumps(
        vars(data),
        sort_keys=True,
        indent=4,
        default=lambda x: x.__dict__
    )

    fwrite(file, info)


def hash_generator(keyLen):
    def base_str():
        return (string.ascii_letters + string.digits)

    keylist = [random.choice(base_str()) for i in range(keyLen)]
    return ("".join(keylist))


def makedirs(_dir):
    if not os.path.isdir(_dir):
        os.makedirs(_dir)


def makedir(_dir):
    if not os.path.isdir(_dir):
        os.mkdir(_dir)
