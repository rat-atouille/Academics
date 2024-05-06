/*
 * 
 */

public class MyObject implements MyObjectADT{
	
	
	private BinarySearchTree tree;
	private int id, width, height;
	private String type;
	private Location locus;
	
	public MyObject(int id, int width, int height, String type, Location pos) {
		tree = new BinarySearchTree();	
		this.height = height;
		this.id = id;
		this.width = width;
	}
	
	public void setType (String type) {
		this.type = type;
	}
	
	public int getWidth() {
		return this.width;
	}
	
	public int getHeight() {
		return this.height;
	}
	
	public String getType() {
		return this.type; }
	
	public int getId() {
		return this.id;
	}
	
	public Location getLocus() {
		return this.locus;
	}
	
	public void setLocus(Location value) {
		this.locus = value;
	}
	
	public void addPel(Pel pix) throws DuplicatedKeyException{
		try {
			tree.put(tree.getRoot(), pix);
		}
		catch(DuplicatedKeyException e) {
			System.out.println("key already exists");
		}
	}
	
	public boolean intersects(MyObject otherObject) {
		boolean valid = false;
		
		// check overlap
		if (!this.tree.getRoot().isLeaf()) {
			
			BNode fNode = this.tree.getRoot();
			BNode oNode = this.tree.getRoot();
			Pel p;
			try {
				p = this.tree.smallest(fNode);
				
				// loop until it reaches the most right node
				while (p != null) {
					
					Location f = new Location(this.tree.get(fNode,fNode.getData().getLocus()).getLocus().getx() - 
							otherObject.tree.get(oNode,oNode.getData().getLocus()).getLocus().getx() ,   
							this.tree.get(fNode,fNode.getData().getLocus()).getLocus().gety()-
							otherObject.tree.get(oNode,oNode.getData().getLocus()).getLocus().gety());
					
					// does not overlap
					if (fNode.getData().getLocus().compareTo(f) != 0) {
						p = this.tree.successor(fNode,p.getLocus());
						valid = true;
					}
					else {
						//overlap
						return (valid=false);	}
					}
				
			} catch (EmptyTreeException e) {
				e.printStackTrace();}
			}
		return valid;
	
}
}
