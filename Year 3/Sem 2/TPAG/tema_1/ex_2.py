import numpy as np

a = 5
b = 3

offset = 400
scale = 70

file_name = 'ex_2.html'

def x(t):
    return ((a - b) * np.cos(t) + b * np.cos((a / b - 1) * t)) * scale
def y(t):
    return ((a - b) * np.sin(t) - b * np.sin((a / b - 1) * t)) * scale

with open(file_name, 'w') as f:
    f.writelines(['<!DOCTYPE html>\n',
                  '<html>\n',
                  '<body>\n',
                  '<svg height="800" width="800">\n'])
    p_x = x(0) + offset
    p_y = y(0) + offset
    f.write(f'<path d="M {p_x} {p_y}')

    for i in range(1, 190):
        t = i / 10
        p_x = x(t) + offset
        p_y = y(t) + offset
        f.write(f'\n         L {p_x} {p_y}')

    f.writelines([
                  '"\n',
                  '         stroke="blue"\n',
                  '         stroke-width="2"\n',
                  '         fill="none">'
                  '</svg>\n',
                  '</body>\n',
                  '</html>\n'])
