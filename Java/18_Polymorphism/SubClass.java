class BaseClass{
	public int book = 6;
	
	public void base(){
		System.out.println("father's simple function");
		
	}
	
	public void test(){
		System.out.println("father's overflow function");
	}
	
}

public class SubClass extends BaseClass{
	
	public String book = "string";
	
	public void test(){
		System.out.println("son's overflow father function");

	}
	
	public void sub(){
		System.out.println("子类的普通方法");
	}
	
	public static void main(String args[]){
		
		BaseClass bc = new BaseClass();
		
		System.out.println(bc.book);
		
		bc.base();
		bc.test();
		
		SubClass sc = new SubClass();
		
		sc.base();
		sc.test();
		
		BaseClass ts = new SubClass();//以父类编译，以子类运行
		System.out.println(ts.book);
		
		ts.base();
		ts.test();
		//ts.pub();  很变态，明明是子类的对象，赋值给父类，编译会出现错误
	
	}
	
}
