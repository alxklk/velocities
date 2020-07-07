import tables
import variant
import strutils

type AssetCache* = TableRef[string, Variant]

var a : AssetCache = {
    "hit/assets/ok/ok_1.png": newVariant("one"),
    "hit/assets/ok/ok_2.png": newVariant(2.0),
    "hit/assets/ok/ok_3.png": newVariant(3)
}.newTable

echo "*** table ***"
echo $a

echo "*** get hit/assets/ok/ok_2.png ***"
echo a.getOrDefault("hit/assets/ok/ok_2.png")

echo "*** get a ***"
echo a.getOrDefault("a")


echo "*** iterate ***"
for i,x in a:
    if i.endsWith("assets/ok/ok_1.png"):
        echo "found: ", x


var externalBundles*: TableRef[string, string]

externalBundles["1"]="23123"
