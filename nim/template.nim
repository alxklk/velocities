type Annnouncement[T] = ref object of RootObj

proc prt[T](ann: Annnouncement[T]) =
    if T is string:
        echo "string"
    else:
        echo "not string"

type Ann1=Annnouncement[string]
type Ann2=Annnouncement[int]


var a1 = Ann1()
var a2 = Ann2()

a1.prt
a2.prt
