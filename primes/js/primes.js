for(i=0;i<50000;i++)
{
	var comp=0;
	for(j=2;j<i;j++)
	{
		var f=i;
		var rf=f/j;
		var ri=Math.trunc(rf);
		if(rf==ri)
		{
			comp=1;
			break;
		}
	}
	if(comp==0)
	{
		console.log(String(i)+" -- simple");
	}
}
