public class array{
	public static void main(String args[])
	{
		
		
		System.out.println("不传参数");
		fun();

		System.out.println("传5个参数");
		fun(5,1,4,3,2);


	}
	

	public static void fun(int... arg)
	{
		for(int tp : arg)
		System.out.println(tp);
	}


}
