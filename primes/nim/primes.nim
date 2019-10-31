for i in 0..50000:
  var comp : bool = false
  for j in 2..<i:
    var rf : float = float(i)/float(j)
    var ri : int = int(rf)
    if rf==float(ri):
      comp=true
      break

  if comp==false:
    echo i," -- nimple"
