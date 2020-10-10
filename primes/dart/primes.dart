import 'dart:io';

void main()
{
	for(int i=1;i<50000;i++)
	{
		int comp=0;
		for(int j=2;j<i;j++)
		{
			double f=i+0.0;
			double rf=f/j;
			int ri=rf.round();
			if(rf==ri)
			{
				comp=1;
				break;
			}
		}
		if(comp==0)
		{
			stdout.write(i);
			print(" -- dartle");
		}
	}
}