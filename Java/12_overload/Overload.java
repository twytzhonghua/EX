public class Overload{

	public void test(){
		System.out.println("无参函数");
	}

	public void test(String atr){
		System.out.println("overload method=" + atr);
	}

	public static void main(String args[]){
	
		Overload ol = new Overload();

		ol.test();
		ol.test("Albert");

	}
	
}
