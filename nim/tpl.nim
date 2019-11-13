proc `.**.`[T](a: T, b: int): T =
  result = ""
  for i in 0..b-1:
    result = result & a

echo "a" .**. 10