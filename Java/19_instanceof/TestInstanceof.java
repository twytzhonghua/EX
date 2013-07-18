public class TestInstanceof{
	public static void main(String args[]){
		Object hello = "Hello";
		
		System.out.println("字符串是否是Object类" + (hello instanceof Object));
		
		System.out.println("字符串是否是String类" + (hello instanceof String));

		System.out.println("字符串是否是Math类" + (hello instanceof Math));

		System.out.println("字符串是否是Comparable类" + (hello instanceof Comparable));
		
		String a = "happy";
		
		System.out.println("a是否是Comparable类" + (a instanceof Comparable));
	//	System.out.println("a是否是Math类" + (a instanceof Math));
	//	由于Math 是 Object 的一个子类，所以编译无法通过，String 是 Object子类，但支持Comparable接口

		
	}

}
