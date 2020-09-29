for i in 1..50000
{
	mut comp := false
	for j in 2..i-1
	{
		mut rf := f32(i)/(j)
		mut ri := int(rf)
		if rf==f32(ri)
		{
		comp=true
			break
		}
	}
	if comp==false{
		println("${i} -- vimple")
	}
}
