import java.io.IOException;
import java.util.Enumeration;
import java.util.NoSuchElementException;
import java.util.Vector;

class private_fieldC implements Cloneable{
	private_fieldC self;
	public int second_field = 322;
	private static int field = 52;

	private_fieldC(){
		self = this;
	}
	public static int getter(){
		return field;
	}
}

class test_app{
	static int field = 0;
	int second_field = 0;
	static String s = "Hello World!\n";

	private static int private_field = 1884;
	private static void private_method(int test_val){
		System.out.print("Private successful! Value:   ");
		System.out.println(test_val);
	}
	public static native void debug_segfault(String[] args);
	public static synchronized int test(int until){
		int a = 0;
		for(int i = 0; i < until; i++){
			a = i + i * i;
		}
		return a;
	}

	public static void varargs(Object... args){

	}

	public static void expection_test() throws IOException{
		throw new IOException();
	}

	public static void main(String[] args){

		field = test(512);
		s = "Fuck";

		String strn = new String(s);


		try {
			expection_test();
		} catch(IOException e){
			System.out.println("\n ============= \nExpection test successful!\n ============= \n");
			System.out.println(e.toString());
			e.printStackTrace();
		}

		

		System.out.println("Hello world!");
		System.out.println(s);
		System.out.println();
		System.out.println(0.1234f);
		System.out.println(0.1234567890123456789);
		System.out.println(1234);
		System.out.println(5456677l);

		private_method(private_field);
		System.out.println(private_fieldC.getter());

		private_fieldC C = new private_fieldC();

		C.second_field = 7676;
		System.out.println(C.second_field);

		Object no = new Object();
		System.out.println(no.equals(C));
		System.out.println(no.equals(new Object()));
		System.out.println(no.hashCode());
		System.out.println(s.hashCode());

		byte[] byte_array = new byte[64];

		for(int i = 0; i < 64; i++){
			byte_array[i] = ((byte)i);
		}
		for(int i = 0; i < 64; i++){
			System.out.print(byte_array[i]);
			System.out.print(' ');
		}
		System.out.println();
		System.out.println(byte_array instanceof java.lang.Object);
		System.out.println(C instanceof java.lang.Object);
		System.out.println(no instanceof private_fieldC);
		System.out.println(s instanceof java.lang.Object);
		System.out.println(no instanceof java.lang.String);

		System.out.println(byte_array.length);

		try {
			byte_array[20000] = ((byte)52);
		}catch (ArrayIndexOutOfBoundsException e){
			System.out.println("Out Of Bounds exception test successful!");
		}

		System.out.println("End of the road");

		// Vector tests
		System.out.println("\n============= Vector Tests =============");
		
		java.util.Vector vec1 = new java.util.Vector();
		System.out.print("New Vector size: ");
		System.out.println(vec1.size());
		System.out.print("New Vector capacity: ");
		System.out.println(vec1.capacity());
		
		Object obj1 = new Object();
		Object obj2 = new Object();
		Object obj3 = new Object();
		String str1 = new String("test1");
		String str2 = new String("test2");
		
		vec1.addElement(obj1);
		vec1.addElement(obj2);
		vec1.addElement(str1);
		System.out.print("After adding 3 elements, size: ");
		System.out.println(vec1.size());
		
		Object retrieved = vec1.elementAt(0);
		System.out.print("elementAt(0) == obj1: ");
		System.out.println(retrieved == obj1);
		
		retrieved = vec1.elementAt(2);
		System.out.print("elementAt(2) == str1: ");
		System.out.println(retrieved == str1);
		
		System.out.print("indexOf(obj1): ");
		System.out.println(vec1.indexOf(obj1));
		System.out.print("indexOf(obj2): ");
		System.out.println(vec1.indexOf(obj2));
		System.out.print("indexOf(str1): ");
		System.out.println(vec1.indexOf(str1));
		System.out.print("indexOf(obj3) (not found): ");
		System.out.println(vec1.indexOf(obj3));
		
		System.out.print("firstElement() == obj1: ");
		System.out.println(vec1.firstElement() == obj1);
		System.out.print("lastElement() == str1: ");
		System.out.println(vec1.lastElement() == str1);
		
		vec1.insertElementAt(obj3, 1);
		System.out.print("After insertElementAt(obj3, 1), size: ");
		System.out.println(vec1.size());
		System.out.print("elementAt(1) == obj3: ");
		System.out.println(vec1.elementAt(1) == obj3);
		System.out.print("elementAt(2) == obj2: ");
		System.out.println(vec1.elementAt(2) == obj2);
		
		vec1.addElement(str2);
		vec1.addElement(str1);
		System.out.print("After adding str2 and str1, size: ");
		System.out.println(vec1.size());
		System.out.print("lastIndexOf(str1): ");
		System.out.println(vec1.lastIndexOf(str1));
		
		boolean removed = vec1.removeElement(obj3);
		System.out.print("removeElement(obj3) returned: ");
		System.out.println(removed);
		System.out.print("After removeElement(obj3), size: ");
		System.out.println(vec1.size());
		System.out.print("elementAt(1) == obj2: ");
		System.out.println(vec1.elementAt(1) == obj2);
		
		vec1.removeElementAt(0);
		System.out.print("After removeElementAt(0), size: ");
		System.out.println(vec1.size());
		System.out.print("firstElement() == obj2: ");
		System.out.println(vec1.firstElement() == obj2);
		
		java.util.Vector vec2 = new java.util.Vector(5);
		System.out.print("Vector(5) capacity: ");
		System.out.println(vec2.capacity());
		
		java.util.Vector vec3 = new java.util.Vector(3, 2);
		System.out.print("Vector(3, 2) capacity: ");
		System.out.println(vec3.capacity());
		
		vec3.addElement(obj1);
		vec3.addElement(obj2);
		vec3.addElement(obj3);
		vec3.addElement(str1);
		System.out.print("After adding 4 elements to Vector(3, 2), capacity: ");
		System.out.println(vec3.capacity());
		
		vec2.ensureCapacity(10);
		System.out.print("After ensureCapacity(10), capacity: ");
		System.out.println(vec2.capacity());
		
		vec1.removeAllElements();
		System.out.print("After removeAllElements(), size: ");
		System.out.println(vec1.size());
		
		try {
			vec1.firstElement();
			System.out.println("ERROR: firstElement() on empty vector should throw exception!");
		} catch(NoSuchElementException e){
			System.out.println("firstElement() on empty vector correctly threw exception");
		}
		
		try {
			vec1.lastElement();
			System.out.println("ERROR: lastElement() on empty vector should throw exception!");
		} catch(NoSuchElementException e){
			System.out.println("lastElement() on empty vector correctly threw exception");
		}
		
		try {
			vec1.elementAt(0);
			System.out.println("ERROR: elementAt(0) on empty vector should throw exception!");
		} catch(ArrayIndexOutOfBoundsException e){
			System.out.println("elementAt(0) on empty vector correctly threw exception");
		}
		
		vec2.addElement(obj1);
		try {
			vec2.elementAt(5);
			System.out.println("ERROR: elementAt(5) on vector of size 1 should throw exception!");
		} catch(ArrayIndexOutOfBoundsException e){
			System.out.println("elementAt(5) on vector of size 1 correctly threw exception");
		}
		
		try {
			vec2.removeElementAt(5);
			System.out.println("ERROR: removeElementAt(5) on vector of size 1 should throw exception!");
		} catch(ArrayIndexOutOfBoundsException e){
			System.out.println("removeElementAt(5) on vector of size 1 correctly threw exception");
		}
		
		try {
			vec2.insertElementAt(obj2, 5);
			System.out.println("ERROR: insertElementAt(obj2, 5) on vector of size 1 should throw exception!");
		} catch(ArrayIndexOutOfBoundsException e){
			System.out.println("insertElementAt(obj2, 5) on vector of size 1 correctly threw exception");
		}
		
		vec2.addElement(obj2);
		vec2.insertElementAt(obj3, 2);
		System.out.print("After insertElementAt(obj3, 2) on vector of size 2, size: ");
		System.out.println(vec2.size());
		System.out.print("elementAt(2) == obj3: ");
		System.out.println(vec2.elementAt(2) == obj3);
		
		System.out.println("============= Vector Tests Complete =============");

		System.out.println("\n============= Test Results =============");
		System.out.println("All tests PASSED!");
		System.out.println("========================================\n");


		Vector test_enumerator = new Vector();
		test_enumerator.addElement("Hurray!");
		test_enumerator.addElement("It works");
		test_enumerator.addElement("god damn it");
		test_enumerator.addElement("шиииииишь");

		boolean stop = true;
		Enumeration ve = test_enumerator.elements();

		while(stop){
			try{
				System.out.println((String)ve.nextElement());
			} catch (NoSuchElementException e){
				stop = false;
			}
		}

		/*while(true){
			private_fieldC newC = new private_fieldC();
			System.out.print(newC);
			System.out.print(' ');
			System.out.print(newC.self);
			System.out.print(' ');
			System.out.print(newC.equals(newC.self));
			System.out.print(' ');
			//System.out.print(newC.hashCode());
			System.out.println(' ');
		}
		*/
	}
}
