import os

echo paramCount()

if paramCount()>=1:
    echo paramStr(1)
    for line in lines paramStr 1 :
        for c in line :
            write stdout, c
        write stdout, '\n'