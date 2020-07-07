proc S1(s: string, p:proc(s:string)) =
    p s & s

var s = "s"
S1(s) do(s: string) :
    echo s & "_" & s
    assert(false)
