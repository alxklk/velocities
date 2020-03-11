import strutils

type
    Status = enum
        OK = 0,
        ERROR = 1,
        WARNING = 2,
        NOTE = 3

var f:File
if f.open("check.txt"):
    var s = f.readLine
    echo s
    var st: Status = Status.ERROR
    try:
        st = Status(s.parseInt)
    except RangeError:
        st = Status.ERROR
    echo st
