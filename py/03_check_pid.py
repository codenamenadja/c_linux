from multiprocessing import Process
import os
from functools import wraps
from inspect import getframeinfo
from typing import Callable

DATA = 4

def stat_function(func: Callable) -> Callable:
    @wraps(func)
    def inner(*args, **kwargs):
        print("func: ", func.__name__, "<-- start")
        ret = func(*args, **kwargs)
        print("func: ", func.__name__, "---> end\n")
        return ret
    return inner


@stat_function
def info(title: str) -> None:
    print(title)
    pid = os.getpid()
    global DATA
    DATA+=1
    print("DATA:",DATA)
    print(
        f"module:{__name__}\tparent process:{os.getppid()}\tcur_process_id:{os.getpid()}"
    )


@stat_function
def f(name: str) -> None:
    print("Hello\n", name)
    info(name)


if __name__ == "__main__":
    info("main line")
    p = Process(target=f, args=("bob",))
    print(f"-------------before start-{os.getpid()}")
    p.start() # COW occur // Process.start method write all at this point.
    del DATA
    print(f"--------------before join-{os.getpid()}")
    p.join()
    print(f"----------------------end-{os.getpid()}")
