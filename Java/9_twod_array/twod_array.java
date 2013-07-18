public class twod_array{
	public static void main(String args[])
	{
		int[][] a;

		a = new int[3][];

		a[0] = new int[2];
		a[0] = new int[]{1,2};

		for(int i=0;i<a[0].length;i++)
			System.out.println("a[0][" + i + "]=" + a[0][i]);
	}
	


}
