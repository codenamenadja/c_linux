from multiprocessing import Pool, Process

def f(x):
    return x*x

def f_2(name):
    print("hello", name)

if __name__ == "__main__":
    p = Process(target=f_2, args=('bob',))
    p.start()
    p.join()
