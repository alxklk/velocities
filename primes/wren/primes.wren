for (i in 0..50000){
	var comp = 0
	for (j in 2...i){
			var f=i
			var rf=f/j
			var ri=rf.floor
			// System.print("i=%(i), j=%(j), comp=%(rf==ri)")
			if(rf==ri){
				comp=1
				break
			}
	}
	if(comp==0){
		System.print("%(i) -- wipmle")
	}
}

