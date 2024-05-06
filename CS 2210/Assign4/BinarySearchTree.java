
/**
 *
 */
public class BinarySearchTree implements BinarySearchTreeADT {

	private BNode root, curr, temp;
	private Pel p;
	
	/*
	 * constructor
	 */
	public BinarySearchTree() {
		this.root = new BNode();
	}
	
	// returns Pel object with the given Location key returns null if DNE 
	public Pel get(BNode r, Location key) {
		//System.out.println("leaf " + r.isLeaf());
		if (r.isLeaf()) {
			return null;
		}
		else {
			BNode result = getLoc(r,key); 
			return result.getData();}
		}

	
	//inserts given Pel data to the leaf node of the tree 
	public void put(BNode r, Pel newData) throws DuplicatedKeyException{
		p = get(r, newData.getLocus());
		// key already exists
		if (p != null) {
			throw new DuplicatedKeyException("already exists");
		}
		
		// add new node to the leaf node
		else if (r.isLeaf()) {
			r.setContent(newData);
			r.setLeftChild(new BNode());
			r.setRightChild(new BNode());
			r.leftChild().setParent(r);
			r.rightChild().setParent(r);
			}
		else {
			//smaller go to left
			if (r.getData().getLocus().compareTo(newData.getLocus()) == -1) {
				put(r.leftChild(),newData);}
		
			//bigger go to right
			else if (r.getData().getLocus().compareTo(newData.getLocus()) == 1) {
				put(r.rightChild(),newData);}
		}
	}

	// remove method
	public void remove(BNode r, Location key) throws InexistentKeyException {
		p = get(r,key);			//returns Pel object or null
		temp = getLoc(r,key);	// return BNode object with the object pel
		
		// doesn't exist throw exception
		if (p == null) {
			throw new InexistentKeyException("inexistent key");
		}

		// tree is empty
		else if (r.isLeaf()) {
			r = null;
		}
		else {
			// left child is a leaf
			if (temp.leftChild().isLeaf()) {
				BNode par = temp.parent();
				BNode c = temp.rightChild();
				//set child as the new root
				if (temp.parent() == null) {
					c.setParent(null);
				}
				else {
					// replace temp with child 
					par.setRightChild(c);
					c.setParent(par);
				}
			}
			// right child is a leaf
			else if (temp.rightChild().isLeaf()) {
				BNode par = temp.parent();
				BNode c = temp.leftChild();
				// set child as the new root
				if (temp.parent() == null) {
					c.setParent(null);
				}
				else {
					// replace temp with child
					par.setLeftChild(c);
					c.setParent(par);
				}
			}
			else {
				BNode s;
				s = smallestLoc(temp.rightChild());
				temp.setContent(s.getData());
				remove(s,s.getData().getLocus());}
		}
	}
		
	
	public Pel successor(BNode r, Location key) {
		BNode temp1 = null;
		BNode par = null;
		
		if (r.isLeaf()) {
			return null;
		}
		else {
			temp1 = getLoc(r,key);
			// temp is an internal node and right child is an internal node
			if (!temp1.isLeaf() && !temp1.rightChild().isLeaf()) {
				BNode sNode = smallestLoc(temp1.rightChild());
				return sNode.getData();
				//return (smallest(temp1.rightChild()));
			}
			else {
				par = temp1.parent();
				while (temp1.getData().getLocus()
						.compareTo(r.getData().getLocus()) != 0
						&& temp1.getData().getLocus()
						.compareTo(r.rightChild().getData().getLocus()) == 0) {
					temp1 = par;
					par = temp1.parent();
				}
				if (temp1.getData().getLocus()
						.compareTo(r.getData().getLocus()) == 0) {
					return null;
				}
				else {
					return par.getData();}}
			}
	}
		

	public Pel predecessor(BNode r, Location key) {
		BNode temp1 = null;
		BNode par = null;
		
		if (r.isLeaf()) {
			return null;
		}
		else {
			temp1 = getLoc(r,key);
			// temp is an internal node and right child is an internal node
			if (!temp1.isLeaf() && !temp1.leftChild().isLeaf()) {
				BNode sNode = largestLoc(temp1.leftChild());
				return sNode.getData();
				//return (smallest(temp1.rightChild()));
			}
			else {
				par = temp1.parent();
				while (temp1.getData().getLocus()
						.compareTo(r.getData().getLocus()) != 0
						&& temp1.getData().getLocus()
						.compareTo(r.leftChild().getData().getLocus()) == 0) {
					temp1 = par;
					par = temp1.parent();
				}
				if (temp1.getData().getLocus()
						.compareTo(r.getData().getLocus()) == 0) {
					return null;
				}
				else {
					return par.getData();}}
			}
	}
	
	/*
	 * @return Pel containing the smallest value 
	 */
	public Pel smallest(BNode r) throws EmptyTreeException {
		if (r.isLeaf()) {
			throw new EmptyTreeException("The tree does not contain any data");
		}
		else {
			BNode s = smallestLoc(r);
			return (s.getData());
		}
	}
	
	/*
	 * @return BNode containing the smallest value 
	 */
	private BNode smallestLoc(BNode r) {
		if (r.isLeaf()) {
			return null;
		}
		else {
			curr = r;
			while (!curr.isLeaf()) {
				curr = curr.leftChild();}
			return curr.parent();}
	}
	
	/*
	 * @return Pel containing the largest value 
	 */
	public Pel largest(BNode r) throws EmptyTreeException{
		if (r.isLeaf() == true) {
			throw new EmptyTreeException("The tree does not contain any data");
		}
		else {
			BNode l = largestLoc(r);	
			return r.getData();
		}
	}
	
	/*
	 * @return BNode containing the largest value 
	 */
	private BNode largestLoc(BNode r) {
		if (r.isLeaf()) {
			return null;}
		else {
			curr = r;
			while (!curr.isLeaf()) {
				curr = curr.rightChild();}
			return curr.parent();}
	}
	
	/*
	 * @return BNode root
	 */
	public BNode getRoot() {
		return this.root;
	}
	
	
	/*
	 * @return BNode with the given key or the location where it is supposed to be
	 */
	private BNode getLoc(BNode r, Location key) {
		if (r.isLeaf()) {
			return r;
		}
		else if (r.getData().getLocus().compareTo(key) == 0) {
			return r;
		}
		else if (r.getData().getLocus().compareTo(key) == -1) {
			return getLoc(r.leftChild(),key);
		}
		else
			return getLoc(r.rightChild(),key);
		}	
}
