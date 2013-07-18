public class NullAccessStatic{
	
	public static void test(){
		System.out.println("static method");
	}
	
	public void say(){
		System.out.println("say method");

	}
	
	public static void main(String args[]){
		NullAccessStatic na = null;
		na.test();
		
		 // 空对象可以访问本类中的static成员或方法，不能访问其他的实例成员，否则会出现异常。
		 
		na.say();
	
	}
	
}
