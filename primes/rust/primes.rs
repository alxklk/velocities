fn go()
{
	for i in 0..50000
	{
		let mut comp = 0;
		for j in 2..i
		{
			let f : f32 = i as f32;
			let rf : f32 = f / j as f32;
			let r : i32 = i / j;
			let ri : i32 = r;
			if ri as f32 == rf
			{
				comp = 1;
				break;
			}
		}
		if comp == 0 {
			println!("{} -- rumple", i);
		}
	}
}

fn main()
{
	go();
}
