def tspMst(graph)
	r = graph.getPlane.first[0]
	mstPrim(graph,r)
	tree = createTree(graph)
	return createPath(graph,tree)
end

def mstPrim(graph,r)
	graph.getPlane.each do |vertex,value|
		graph.setKey(vertex,Float::INFINITY)
		graph.setFather(vertex,nil)
	end
	graph.setKey(r,0)
	q = []
	graph.getPlane.each do |vertex,value|
		q.push(VertexKEY.new(vertex,graph.getKey(vertex)))
	end
	heap = Heapmin.new
	while (!q.empty?)
		u = heap.extractRoot(q)
		q.each do |vertex|
			distance = graph.getDistance(u.getVertex.to_i,vertex.getVertex.to_i) 
			if (distance < graph.getKey(vertex.getVertex))
				graph.setKey(vertex.getVertex,distance)
				graph.setFather(vertex.getVertex,u)
				vertex.setKey(distance)
			end
		end
	end
end

def createTree(graph)
	tree = Hash.new { |key,value| key[value] = Vertex.new }
	graph.getPlane.each do |index,v|
		v = graph.getFather(index)
		if (!v.nil?)
			tree[v.getVertex].addAdj(index)
		else tree[index]
		end	
	end
	return tree
end

def createPath(graph,tree)
	path = []
	preOrder(tree,tree.first[0],path)
	path.push(tree.first[0])
	cost = graph.calculateCost(path)
	return cost,path
end

def preOrder(tree,father,path)
	path.push(father)
	if (tree.has_key?(father))
		sons = tree[father]
		while (!sons.getEdges.empty?)
			descent = sons.rmEdge(sons.getEdges.first[0])
			preOrder(tree,descent,path)
		end
	end
end
