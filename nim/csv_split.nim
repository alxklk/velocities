import strutils

var s="One,Two,Three"

proc ss():string=
    s

echo ss().split(',')