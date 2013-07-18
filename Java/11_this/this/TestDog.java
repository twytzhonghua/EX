class Dog{
	
	public void jump()
	{
		System.out.println("dog is jumping");
	}

	public void run()
	{
	/*
		Dog dog1 = new Dog();
		dog1.jump();
	*/
		//another method: use this pointer
		this.jump();

		//third method: omit this pointer
		jump();


		System.out.println("dog is running");
	}

}


public class TestDog{

	public static void main(String args[]){
	
		Dog dog = new Dog();

		dog.run();
	
	}


}
