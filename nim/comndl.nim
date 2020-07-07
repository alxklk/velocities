import os, parseopt

var option = initOptParser(commandLineParams())
while true:
    option.next()
    case option.kind
    of cmdEnd: break
    of cmdArgument: discard
    of cmdShortOption, cmdLongOption:
        if option.key == "prefix":
            echo " '", option.key, "' = '", option.val, "'"
