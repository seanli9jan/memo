# -*- coding:utf-8 -*-

import struct
import sys

new_data = []

read_file = open(sys.argv[1] + '.txt', 'r')

for read_lines in read_file.readlines():
    get_data = read_lines.split()

    if get_data[0] in ['ROWS', 'COLS', 'CH']:
        new_data.append(get_data[1])

    else:
        for read_data in range(len(get_data)):
            for check_data in ['[', ',', ']']:
                if check_data in get_data[read_data]:
                    get_data[read_data] = get_data[read_data].replace(check_data, '')

            new_data.append(get_data[read_data])

read_file.close()

write_file = open(sys.argv[1] + '.o', 'w')

for convert_data in new_data:
    set_data = struct.pack('<f', float(convert_data))
    write_file.write(set_data)

write_file.close()
