type
    EventHandler = object
        id : int
        handler : proc(id : int)
    EventHub = object
        handlers* : seq[EventHandler]

method AddHandler(self : var EventHub, newId : int, newHandler : proc(id : int) ) {.base.} =
    self.handlers.add(EventHandler( id: newId, handler : newHandler))

method Call(self : var EventHub) {.base.} =
    for delegate in self.handlers :
        delegate.handler(delegate.id)

var d1 : EventHub

d1.AddHandler(0, proc(id : int) = echo "Event", id )
d1.AddHandler(1, proc(id : int) = echo "MouseEvent", id )
d1.AddHandler(3, proc(id : int) = echo "KeyEvent", id )
d1.AddHandler(4, proc(id : int) = echo "Event 0", id )

d1.Call