import macros

proc `*`(s: string, n: int) : string =
    var res : string=""
    for i in 0..n:
        res.add(s)
    return res

#proc `+@+`(i: var int): int =
#    i = i * i + i + 1
#    return i
#
#var x: int = 2
#var y: int = +@+x
#echo x
#echo y

proc rececho(stm: NimNode, level: int)=
    echo " - "*level, stm.kind, " <", stm.toStrLit, ">"
    for st in stm:
        rececho(st, level+1)

macro mtest(body: untyped): untyped =
    rececho(body,0)

mtest:
    echo "body",line
    var x=2
    echo x
