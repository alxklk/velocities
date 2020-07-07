import streams, parsecsv

var strm = newStringStream("One,Two,Three")
var parser: CsvParser
parser.open(strm, "tmp.csv")
if parser.readRow():
    echo parser.row
parser.close()
strm.close()