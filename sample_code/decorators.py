# -*- coding:utf-8 -*-

def case1():
    print("Case 1 : ")
    def hello_func(func):
        def wrapper():
            print("  Hello %s" % func.__name__)
            return func()
        return wrapper

    def func1():
        print("  Run func1")

    func1 = hello_func(func1)
    return func1()

def case2():
    print("Case 2 : ")
    def hello_func(func):
        def wrapper():
            print("  Hello %s" % func.__name__)
            return func()
        return wrapper

    @hello_func
    def func2():
        print("  Run func2")

    return func2()

def case3():
    print("Case 3 : ")
    def hello_func(level):
        def decorator(func):
            def wrapper(*args, **kwargs):
                if level == "warn":
                    print("  Hello %s" % func.__name__)
                elif level == "info":
                    print("  Hello %s" % func.__name__)
                return func(*args)
            return wrapper
        return decorator

    @hello_func(level="warn")
    def func3(name="func3"):
        print("  Run %s" % name)

    return func3()

def case4():
    print("Case 4 : ")
    class hello_func(object):
        def __init__(self, func):
            self._func = func

        def __call__(self):
            print ("  Hello %s" % self._func.__name__)
            print(self._func.__doc__)

    @hello_func
    def func4():
        """  Run func4"""

    return func4()

def main():
    case1()
    case2()
    case3()
    case4()

if __name__ == "__main__":
    main()
