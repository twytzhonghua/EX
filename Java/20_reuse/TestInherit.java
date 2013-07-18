class Animal{
	private void beat(){
		System.out.println("heart beating");
	}
	
	public void breath(){
		beat();
		System.out.println("吸一口气，呼一口气");
	}
}

class Bird extends Animal{
	private Animal a;
	
	public Bird(Animal a){
		this.a = a;
	}
	
	public void breath(){
		a.breath();
	}
	
	public void fly(){
		System.out.println("I can fly in the blue sky");
	
	}
	
}

class Wolf extends Animal{
	private Animal a;
	
	public Wolf(Animal a){
		this.a = a;
	}
	
	public void breath(){
		a.breath();
	}
	
	public void run(){
		System.out.println("I can run on the ground");
		
	}
}

public class TestInherit{
	public static void main(String args[]){
		Animal bird = new Animal();
		Bird b = new Bird(bird);
		
		b.breath();
		b.fly();
		
		
		Animal wolf = new Animal();
		Wolf w = new Wolf(wolf);
		
		w.breath();
		w.run();
			
	}
}
