proc RetTuple() : tuple[status: int, text: string] =
    (1,"some")

var t=RetTuple()

echo t.text, t.status