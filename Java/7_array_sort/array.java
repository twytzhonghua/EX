public class array{
	public static void main(String args[])
	{
		int score[] = {1,8,2,69,23,56,45,12,256,895};

		sort(score);
		print(score);


		System.out.println("下面使用java库函数进行排序");

		java.util.Arrays.sort(score);
		print(score);

	}
	

	public static void sort(int temp[])
	{
		int i,j;
		int tp;
		for(i=1;i<temp.length;i++)
		for(j=0;j<temp.length;j++)
		{
			if(temp[i] < temp[j])
			{
				 tp = temp[i];
				 temp[i] = temp[j];
				 temp[j] = tp;

			}
		}
	}

	public static void print(int temp[])
	{
		for(int tp : temp)
		System.out.println(tp);
	}


}
