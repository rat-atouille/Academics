/**
CS 2210 Assignment 2
*/

/**
 * This class implements a dictionary using a hash table in which collisions are resolved using separate
chaining. The hash table will store objects of the class Record
 *
 */

public class Dictionary implements DictionaryADT{
	
	private int counter;		
	private Node<Record>[] T;
	/*
	 * @param int size
	 * constructor
	 * initializes a dictionary array with an empty hash table of the specified size
	 */
	public Dictionary(int size) {
		T = new Node[size];
		for (int i=0; i<size; i++) {
			T[i] = null;}
		counter = 0;
	}
	
	
	/*
	 * @return 0 if array is empty or return 1 if an element already exist in the array (collision)
	 */ 
    public int put (Record rec) throws DuplicatedKeyException{	
    	int value = -1;
    	//String s = rec.getKey();
    	int pos = hashFunction(rec.getKey());

    	// the table is empty 
    	if (T[pos] == null){
        	T[pos] = new Node<Record>(rec);
        	value = 0; 
			counter++;	}
    	
    	else {
        	Node<Record> current = T[pos];
    		
    		//loop when the next node doesn't point to null and there are no duplicate keys
    		while ((current.getNext() != null) && (((Record) current.getRecord()).getKey()) != rec.getKey()) {
    			current = current.getNext();}
    		
    		//key already exists in the hash table
    		if (((Record) current.getRecord()).getKey() == rec.getKey()){
    			throw new DuplicatedKeyException("Key already exists");}
    		
    		// key does not exist in the hash table hence add the node storing record and the hash position 
    		else {
    			value = 1;
    			current.setNext(new Node<Record>(rec));

    		counter++;	
    		}
    	}
		return value;
    }
   
    /*
     * removes the key from the hash table, if it doesn't exist throws InexistentKeyException exception
     */
    public void remove (String key) throws InexistentKeyException{
    	
    	int pos = hashFunction(key);

    	Node<Record> current = T[pos];
    	Node<Record> previous = null;
    	
    	//search for key to be deleted
    	while ((current != null) && (current.getNext() != null) && ((current.getRecord()).getKey() != key)) {
    		previous = current;
    		current = current.getNext();}
    	
    // key is not in the hash table
    	if (current == null) {
    		throw new InexistentKeyException("This key does not exist");
	}
    	if (current.getRecord().getKey() == key) {
    		if (previous == null) {
    			T[pos] = current.getNext();
    		}
    		else {previous.setNext(current.getNext()); 
    			counter--;}	
    	}
	}
    
   
    /*@return key value or null if it doesn't contain the key value
     * 
     */
    public Record get (String key) {
    
    	int pos = hashFunction(key);
		Node<Record> current = T[pos];

    	while ((current != null) && (current.getNext() != null) && ((current.getRecord()).getKey() != key)) {
     		current = current.getNext();}
    	
    	if (current == null) return null;
    	else return current.getRecord();
		}    		

    	
    /*
     * @return the number of Record objects stored in the hash table
     */
    public int numRecords() {
    	return counter;
    }
    
    /*
     * @return int value 
     * compresses and calculates hash key value
     */
    private int hashFunction(String key) {
    
    	char[] c = key.toCharArray();
		int M = 6037;
		int x = 33;
		int k = c.length;
		int value = (int) c[k-1];
		for (int i = (k-2); i >= 0; i--) {
			value = (value * x + (int)c[i]) % M;}
		return (value % M); }
    }
