public class test{
	public static void main(String args[]){
	
		int[] MyArray = new int[]{2,6,8,32,999};
	/*	
		Object[] objArr1;
		objArr1 = new String[] {"Albert", "中华" };

		Object[] objArr2;
		objArr2 = new String[] {"Java", "李刚" };
	*/
	
		//for(type variableName : array | collection)
		for(int array : MyArray)
		{
			System.out.println("Array=" + array);	
		}
	}
}
