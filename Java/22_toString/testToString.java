class Apple{
	
	private String color;
	private float weight;
	
	public Apple(){ 
	
	}
	
	public Apple(String color, float weight){
		this.color = color;
		this.weight = weight;
	}
	/*
	 *toString 是Object的一个方法，所有对象都是Object的子类，故拥有toString方法，
	 * 如果输出System.out.println(p) 即输出p.toString(),其实就是类的自我描述。
	 */
	public String toString(){
		return "One Apple, color is" + color + ",weight:" + weight;
	}
	
}

public class testToString{
	
	public static void main(String args[]){
		
		Apple a = new Apple("red",15.6f);
		
		System.out.println(a);
	}
}
