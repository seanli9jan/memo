# -*- coding:utf-8 -*-

import ctypes
import numpy as np
import lib.pylib

Str  = "Array :"
Rows = 5
Cols = 4
Ch   = 3

class SHAPE_T(ctypes.Structure):
    _fields_ = [('rows', ctypes.c_uint8),
                ('cols', ctypes.c_uint8),
                ('ch'  , ctypes.c_uint8)]

class DATA_T(ctypes.Structure):
    _fields_ = [('flag' , ctypes.c_bool),
                ('str'  , ctypes.c_char_p),
                ('ary'  , ctypes.POINTER(ctypes.c_float)),
                ('shape', SHAPE_T)]

def cc_init(data, flag):
    data.flag = flag
    data.str  = Str

    data.shape.rows = Rows
    data.shape.cols = Cols
    data.shape.ch   = Ch

    ary = np.zeros((data.shape.rows, \
                    data.shape.cols, \
                    data.shape.ch) , \
                    np.float32)
    data.ary = np.ctypeslib.as_ctypes(ary.ravel())

    return True, ary

def py_init(ary):
    data = lib.pylib.data_t()

    data.str = Str
    data.ary = ary
    data.shape(Rows, Cols, Ch)

    return True, data

if __name__ == '__main__':
    cc_dll = ctypes.CDLL('./lib/_func.so')
    cc_data = DATA_T()

    cc_check, ary = cc_init(cc_data, False)

    if cc_check == True:
        cc_dll.func(ctypes.byref(cc_data))

    py_check, py_data = py_init(ary)

    if py_check == True:
        lib.pylib.func(py_data)
