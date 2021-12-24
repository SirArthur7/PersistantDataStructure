// Java program to illustrate
// CopyOnWriteArrayList class
import java.util.*;
import java.util.concurrent.*;

class Main {
	public static void main(String[] args)
	{

		CopyOnWriteArrayList<String> list
			= new CopyOnWriteArrayList<>();

		// Initial Iterator
		
		Iterator <String> itr1 = list.iterator();	// []
		Iterator <String> itr2 = list.iterator();	// ["Kank", ]
		Iterator <String> itr3 = list.iterator();	// ["Kank", "Ghos", ]
		Iterator <String> itr4 = list.iterator();	// ["Kank", "Ghos", "123", ]
		Iterator <String> itr5 = list.iterator();


//File		         java.util.concurrent.CopyOnWriteArrayList.class


//L.No. 422 		/**
//L.No. 423 		 * Appends the specified element to the end of this list.
//L.No. 424 		 *
//L.No. 425 		 * @param e element to be appended to this list
//L.No. 426 		 * @return {@code true} (as specified by {@link Collection#add})
//L.No. 427 		 */
//L.No. 428 		public boolean add(E e) {
//L.No. 429 			synchronized (lock) {
//L.No. 430				Object[] es = getArray();
//L.No. 431 				int len = es.length;
//L.No. 432 				es = Arrays.copyOf(es, len + 1);				//complete copy is created!!!!
//L.No. 433 				es[len] = e;									//another version!!
//L.No. 434 				setArray(es);
//L.No. 435 				return true;
//L.No. 436 			}
//L.No. 437 		}


		list.add("Kank");
		itr2 = list.iterator();  //VERSION 2: IT WILL NOT KNOW ANY CHANGES FOLLOWING THIS LINE
		list.add("Ghos");
		itr3 = list.iterator();
		itr5 = list.iterator();
		list.add("123");
		itr4 = list.iterator();
		
		System.out.println("V1 List contains: ");
		while (itr1.hasNext()){
			System.out.print(itr1.next() + ", ");
        }
		System.out.println("\n-----------------");
        
        System.out.println("V2 List contains: ");
		while (itr2.hasNext()){
			System.out.print(itr2.next() + ", ");
        }
		System.out.println("\n-----------------");

        System.out.println("V3 List contains: ");
		while (itr3.hasNext()){
			System.out.print(itr3.next() + ", ");
        }
		System.out.println("\n-----------------");

		System.out.println("V4 List contains: ");
		while (itr4.hasNext()){
			System.out.print(itr4.next() + ", ");
        }
		System.out.println("\n-----------------");


		//NO MODIFICATION ALLOWED
		//PERSISTENT PARTIALLY
		//ERROR IN FOLLOWING CODE

		itr5.remove();
		System.out.println("V5 (from V3)  List contains: ");
		while (itr5.hasNext()){
			System.out.print(itr5.next() + ", ");
        }
		System.out.println("\n-----------------");
	}
}
