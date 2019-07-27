public class main
{
	public static void main(String[] args)
	{
		for(int i=0;i<50000;i++)
		{
			int comp=0;
			for(int j=2;j<i;j++)
			{
				float f=i;
				float rf=f/j;
				int ri=(int)rf;
				if(rf==ri)
				{
					comp=1;
					break;
				}
			}
			if(comp==0)
			{
				System.out.print(i);
				System.out.println(" -- simple");
			}
		}
	}
}