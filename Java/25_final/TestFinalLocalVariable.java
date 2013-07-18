public class TestFinalLocalVariable{
	//final修饰的成员变量只能在定义或初始化快中赋值，不能在普通方法中赋值，也不能重复赋值。
	
	final int a = 6;
	final String str;
	final int c;
	final static double d;
	
	{
		str = "hello";
	}
	
	static 
	{
		d = 32.342;//在静态初始化块中可以位类属性指定初始值
	}
	
	public TestFinalLocalVariable(){
		c = 5;
	}
	
	public void changeFinal(){
		//d = 554.5;//普通方法不能为final修饰的成员变量赋值
	}
	
	
	public static void main(String[] args){
	
		TestFinalLocalVariable tf = new TestFinalLocalVariable();
		
		System.out.println(tf.a);
		System.out.println(tf.str);
		System.out.println(tf.c);
		System.out.println(tf.d);
		
	}
 }
