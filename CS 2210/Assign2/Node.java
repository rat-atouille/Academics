/*
 * This class represents the node stored in the dictionary storing hash function value and Record object
 */


public class Node<T> {

	private Node<T> next; //reference to next node
	private T record;
	
	public Node(){
	    next = null;
	    record = null;
	    }
	    
    public Node (T val){
        next = null;
        record = val;
    }
	    
    public Node<T> getNext(){
    	return next;
	    }
    
    public void setNext (Node<T> node) {
    	next = node;
	    }
	    
    public T getRecord(){
    	return record;
	    }
}
