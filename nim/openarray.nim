import os
import sequtils

proc cacheDir() : string =
    result = "c:\\tmp\\rodappcache"


proc listDownloaded*() : seq[string] =
    result = @[]
    when not defined(js) and not defined(emscripten):
        for f in walkDir(cacheDir()):
            let name = f.path.splitFile.name
            if name.len == 40 :
                result.add(name)

proc removeUnlisted(list : seq[string]) =
    var downloaded = listDownloaded()
    for item in downloaded :
        if list.contains(item) :
            echo "delete " & item
            removeDir(cacheDir() / string(item))
        else:
            echo "leave " & item


echo "Open Array"

removeUnlisted(@["tmp", "wrk"])
