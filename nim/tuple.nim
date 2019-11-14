import math

type
    float2 = tuple
        x : float
        y : float

proc `+`*(l, r : float2) : float2 {.inline.} = (x : l.x+r.x, y : l.y+r.y )
proc `-`*(l, r : float2) : float2 {.inline.} = (x : l.x-r.x, y : l.y-r.y )
proc `*`*(l, r : float2) : float2 {.inline.} = (x : l.x*r.x, y : l.y*r.y )
proc `/`*(l, r : float2) : float2 {.inline.} = (x : l.x/r.x, y : l.y/r.y )

proc `*`*[T](l : float2, r : T) : float2 = l * ( x : float(r), y : float(r) ) 
proc `*`*[T](l : T, r : float2) : float2 = ( x : float(l), y : float(l) ) * r

proc `/`*[T](l : float2, r : T) : float2 = l / ( x : float(r), y : float(r) ) 

#property len
proc len*(v : float2) : float =
    math.sqrt(v.x*v.x + v.y*v.y)

#proc normalize*(v : var float2) : untyped =
#    v = v / len(v)

proc `len=`*(v : var float2, l: float) =
    echo "Set ", l
    let ol = l / v.len
    v = v * ol


when isMainModule:
    var l : float2 = (x:2.0, y:1.0)
    var r = (x:1.0, y:3.0)
    var s = l+r;
    echo "s=", s
    echo "l=", l
    echo "r=", r
    echo "len(", $l, ")=", l.len
    echo "r.len()=", r.len
#change length by property
    echo "r=", r
    r.len= 1
    echo "r=", r
    echo "r.len()=", r.len
    echo "r.len=1;r=", r, " r.len()=", r.len
    echo "l+r=", (l+r)
    echo "l-r=", (l-r)
    echo "l*r=", (l*r)
    echo "l*2=", (l*2)
    echo "2*r=", (2*r)
    echo "r/l=", (l/r)
    echo "(r+l).len()=", (r+l).len