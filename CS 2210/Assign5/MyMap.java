import java.io.File;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Stack;

public class MyMap {

	private Graph graph;
	private int start, end, row, col, privateRoad, construction;
	private Stack <Node> stack;
	private String matrix[][];
	
	// constructor 
	public MyMap(String inputFile) throws MapException{
		try {

			stack = new Stack<Node>();

			// read input file
		    Scanner file = new Scanner(new File(inputFile));

		    String line = file.next();
		    line = file.next();		
		    start = Integer.parseInt(line); 			// starting node

		    line =  file.next();
		    end = Integer.parseInt(line);				// destination node		  
			
		    line = file.next();
		    row = Integer.parseInt(line);				// row

		    line = file.next();
		    col = Integer.parseInt(line);				// columns 

		    graph = new Graph(row*col);					// create graph
			matrix = new String[row*col][row*col];		// create edge matrix for storing the discovered edges in path method
		   
		    line = file.next();
		    privateRoad = Integer.parseInt(line);		// number of private roads		    

		    line = file.next();
		    construction = Integer.parseInt(line);		// number of construction roads

		    line = file.next();
		    
		    int roadMap = 8;
		    int hor = 0;	
		    int ver = 0;
	    	int hCounter = 0;
	    	int vCounter = 1;

		    // iterator through the line
		    while (line != null) {
		    			    		
		    	for (int i = 0; i < line.length(); i++) {
			    	
			    	//vertical 
			    	if (i % 2 == 0 && roadMap % 2 != 0) {	
			    		// private
			    		if (line.charAt(i) == 'V') {
			    			graph.addEdge(graph.getNode(ver), graph.getNode(ver+row), "Private");}
			    		// public
			    		else if (line.charAt(i) == 'P') {
			    			graph.addEdge(graph.getNode(ver), graph.getNode(ver+row), "Public");}
			    		// construction
			    		else if (line.charAt(i) == 'C') {	
			    			graph.addEdge(graph.getNode(ver), graph.getNode(ver+row), "Construction");}	
			    		ver++;
			    	}
			    	
			    	// horizontal
			    	else if (i % 2 != 0 && roadMap % 2 == 0) {	

			    		// private
			    		if (line.charAt(i) == 'V') {		
			    			graph.addEdge(graph.getNode(hor), graph.getNode(hor+1), "Private");}
			    		// public
			    		else if (line.charAt(i) == 'P') {	
			    			graph.addEdge(graph.getNode(hor), graph.getNode(hor+1), "Public");}
			    		// Construction
			    		else if (line.charAt(i) == 'C') {	
			    			graph.addEdge(graph.getNode(hor), graph.getNode(hor+1), "Construction"); }
			    	hor++;}
			    }

			    // horizontal 
			    if (roadMap % 2 == 0 && (row*hCounter + (row-1)) < (row*col)) {
			    	hCounter++;
			    	hor = 0 + (row*hCounter);			 // reset the horizontal counter to the beginning node of current line
			    }
			    // vertical 
			    else if (roadMap %2 != 0 && (row*vCounter + (row-1)) < (row*col)) {
			    	ver = 0 + (row*vCounter);			// reset the vertical counter to the beginning node of current line
			    	vCounter++;
			    }
			    roadMap++;	
			   
			    // check if there are leftover lines
			    if (file.hasNext()) {
			    	line = file.next();}
			    
			    // if it reaches the end of the file, break out of the loop
			    else {
			    	break; }
		    }

		// catch exception
		} catch (Exception MapException){
			System.out.println("Exception in class Map");
		}
	}
	
	// return graph 
	public Graph getGraph() throws Exception{
		// graph is empty
		if (graph == null) {
			throw new Exception();
		}
		else return graph;
	}
	
	// return the starting int node
	public int getStartingNode() {
		return this.start;
	}
	
	// return the destination int node
	public int getDestinationRoad() {
		return this.end;
	}

	// return number of private roads
	public int maxPrivateRoads() {
		return this.privateRoad;
	}
	
	// return number of construction roads
	public int maxConstructionRoads() {
		return this.construction;
	}
	
	
	// return null if no path exists or return nodes path from starting node to destination nodes
	public Iterator findPath(int start, int destination, int maxPrivate, int maxConstruction) {
		
		path(start,destination,maxPrivate,maxConstruction);		// update stack
		if (!stack.isEmpty()) {
			return stack.iterator();
		}
		// no possible path
		else return null;
	}

	
	private Boolean path(int start, int destination, int maxPrivate, int maxConstruction) {
		
		privateRoad = maxPrivate;
		construction = maxConstruction;
		
		try {
		
		stack.push(graph.getNode(start));		// push the current node to the stack

		// reach destination
		if (start == destination) {
			matrix[start][destination] = "discovered";
			matrix[destination][start] = "discovered";
			return true;}
		
		else {
				graph.getNode(start).markNode(true);
				Iterator<Edge> edges = graph.incidentEdges(graph.getNode(start));
				
				while (edges.hasNext()) {
					Edge incident = edges.next();

					// check if it is undiscovered edge
					if (matrix[incident.firstNode().getId()][incident.secondNode().getId()] != "discovered" 
							&& matrix[incident.secondNode().getId()][incident.firstNode().getId()] != "discovered") {
						
						// public road
						if (incident.getType().equals("Public")) {
							if (!incident.secondNode().getMark()) {

							matrix[incident.firstNode().getId()][incident.secondNode().getId()] = "discovered";
							matrix[incident.secondNode().getId()][incident.firstNode().getId()] = "discovered";
							
							if (path(incident.secondNode().getId(),destination,privateRoad,construction)) {
								return true;}
						}}
						
						
						// private road
						else if (incident.getType().equals("Private") && privateRoad > 0) {
							if (!incident.secondNode().getMark()) {
							privateRoad--;
							matrix[incident.firstNode().getId()][incident.secondNode().getId()] = "discovered";
							matrix[incident.secondNode().getId()][incident.firstNode().getId()] = "discovered";
							if (path(incident.secondNode().getId(),destination,privateRoad,construction)) {
								return true;}
						}}

						// construction
						else if (incident.getType().equals("Construction") && construction > 0) {
							if (!incident.secondNode().getMark()) {
							construction--;
							matrix[incident.firstNode().getId()][incident.secondNode().getId()] = "discovered";
							matrix[incident.secondNode().getId()][incident.firstNode().getId()] = "discovered";
							if (path(incident.secondNode().getId(),destination,privateRoad,construction)) {
								return true;}
							}}
				}		
			}
			
			// try another path if you reach dead end
				
			Iterator<Edge> find = graph.incidentEdges(graph.getNode(start));
			
			while (find.hasNext()){
				Edge prev = find.next();
					
				// check if the edge was discovered before
				if (matrix[prev.firstNode().getId()][prev.secondNode().getId()] == "discovered" ||
						matrix[prev.secondNode().getId()][prev.firstNode().getId()] == "discovered"){
				
					// set the matrix to null to represent unvisited edge
					matrix[prev.firstNode().getId()][prev.secondNode().getId()] = null;
					matrix[prev.secondNode().getId()][prev.firstNode().getId()] = null;
					
					// if the previous path was private increment the value
					if (prev.getType().equals("Private")){
						privateRoad++;
					}
					// if the previous path was construction increment the value
					else if ((prev.getType().equals("Construction"))) {
						construction++;
					}
					break;		// break out of the loop
				}
			}
		
		}
			(graph.getNode(start)).markNode(false);		// mark node as false
			stack.pop();								// pop the mark from the stack
			return false;	
			
			// catch exception
			} catch (GraphException e) {
				e.printStackTrace();}
		return false;
	}

	
}
