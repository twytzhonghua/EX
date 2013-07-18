
public class Returnthis{
	
	public int age;
	
	public Returnthis grow(){
		age++;

		return this;
	}
	
	
	public static void main(String args[]){
	
		Returnthis rt = new Returnthis();

/*
*  this pointer 的连续引用；
*/
		rt.grow()
		  .grow()
		  .grow()
		  .grow()
		  .grow();

		System.out.println("age=" + rt.age);
	}


}
