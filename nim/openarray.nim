type
    ituple = tuple
        s0: string
        s1: string

var
    x: seq[ituple] # a reference to a sequence of integers

x = @[] # the @ turns the array into a sequence allocated on the heap
