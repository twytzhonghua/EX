public class Primitive2String{
	public static void main(String args[]){
		
		String intstr = "123";
		int it = Integer.parseInt(intstr);
		System.out.println("it=" + it);
		
		String floatstr = "4543.9654";
		float ft = Float.parseFloat(floatstr);
		System.out.println("ft=" + ft);
		
		String ftstr = String.valueOf(2.856f);
		System.out.println("ftstr=" + ftstr);
	
		String dbstr = String.valueOf(3.7894);
		System.out.println("dbstr=" + dbstr);
		
		String boolstr = String.valueOf(true);
		System.out.println("boolstr=" + boolstr);
		
	
	}
	
}
