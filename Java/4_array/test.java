public class test{
	public static void main(String args[]){
	
		//static declare
		int[] MyArray = new int[]{2,6,8,32,999};
		
		Object[] objArr1;
		objArr1 = new String[] {"Albert", "中华" };

		Object[] objArr2;
		objArr2 = new String[] {"Java", "李刚" };
	
		System.out.println("objArrr1=" + objArr1[1]);	
		System.out.println("objArrr2=" + objArr2[1]);	
	}
}
