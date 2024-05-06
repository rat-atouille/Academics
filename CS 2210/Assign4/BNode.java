
/**
 * This class represents the nodes of the binary search tree
 *
 */
public class BNode {
	
	private Pel data;
	private BNode left, right, parent;

	// constructor sets the node to given values
	public BNode (Pel Value, BNode left, BNode right, BNode parent) {
		this.data = Value;
		this.left = left;
		this.right = right;
		this.parent = parent;
	}
	

	/*
	 * constructor
	 * sets everything to null
	 */
	public BNode() {
		this.data = null;
		this.left = null;
		this.right = null;
		this.parent = null;
	}
	
	
	//return parent 
	public BNode parent() {
		return this.parent;
		}
	
	//sets parent
	public void setParent(BNode newParent) {
		this.parent = newParent;
	} 
	
	//sets left child
	public void setLeftChild(BNode p) {
		this.left = p;
	}
	
	// sets right child
	public void setRightChild(BNode p) {
		this.right = p;
	}
	
	// sets the data to given value
	public void setContent(Pel value) {
		this.data = value;
	}
	
	// return true if this node is the leaf
	public boolean isLeaf() {
		if (this.left == null && this.right == null) {
			return true;
		}
		else return false;
	}

	
	//return data 
	public Pel getData() {
		return this.data;
	}
	
	//return left child
	public BNode leftChild() {
		return this.left;
	}

	//return right child
	public BNode rightChild() {
		return this.right;
	}
	
	
	
}
