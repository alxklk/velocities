import math

type
    float2 = object
        x* : float
        y* : float

proc `+`*(l, r : float2) : float2 {.inline.} = float2(x : l.x+r.x, y : l.y+r.y )
proc `-`*(l, r : float2) : float2 {.inline.} = float2(x : l.x-r.x, y : l.y-r.y )
proc `*`*(l, r : float2) : float2 {.inline.} = float2(x : l.x*r.x, y : l.y*r.y )
proc `/`*(l, r : float2) : float2 {.inline.} = float2(x : l.x/r.x, y : l.y/r.y )

proc `*`*[T](l : float2, r : T) : float2 = l * float2( x : float(r), y : float(r) ) 
proc `*`*[T](l : T, r : float2) : float2 = float2( x : float(l), y : float(l) ) * r

proc `/`*[T](l : float2, r : T) : float2 = l / float2( x : float(r), y : float(r) ) 

#property len
method len*(v : float2) : float {.base.} =
    return math.sqrt(v.x*v.x + v.y*v.y)
method `len=`*(v : var float2, l: float) {.base.} =
    v = v / len(v)

template fileline() : int =
    instantiationInfo().line

echo "line:",fileline()

when isMainModule:
    var l = float2(x:2, y:1)
    var r = float2(x:1, y:3)
    let ii= instantiationInfo()
    echo ii[0],"@",ii[1]

    echo "l=", l
    echo "r=", r
    echo "len(", $l, ")=", len l
    echo "r.len()=", r.len
#change length by property
    r.len = 1
    echo "r.len=1;r=", r, " r.len()=", r.len
    echo "l+r=", (l+r)
    echo "l-r=", (l-r)
    echo "l*r=", (l*r)
    echo "l*2=", (l*2)
    echo "2*r=", (2*r)
    echo "r/l=", (l/r)
    echo "(r+l).len()=", (r+l).len