class Vertex

	def initialize
		@edges = Hash.new
	end

	def addAdj(edge)
		@edges[edge] = edge
	end

	def getEdges
		return @edges	
	end

	def rmEdge(edge)
		@edges.delete(edge)
	end

end

class VertexTSP

	def initialize(x,y)
		@cord = [x,y]
	end

	def getCord
		return @cord
	end

	def setKey(key)
		@key = key
	end

	def getKey
		return @key
	end

	def setFather(father)
		@father = father
	end

	def getFather
		return @father
	end

end

class VertexKEY < VertexTSP

	def initialize(vertex,key)
		@vertex = vertex
		@key = key
	end

	def getVertex
		return @vertex
	end

	def <(vertex)
		@key < vertex.getKey
	end

	def >(vertex)
		@key > vertex.getKey
	end

end

class Graph

	def initialize
		@graph = Hash.new
	end

	def addVertice(index)
		@graph[index] = Vertex.new
	end

	def addEdge(index,edge)
		@graph[index].addAdj(edge)
	end

	def getGraph
		return @graph
	end
end

class CartesianPlane

	def initialize()
		@plane = Hash.new
		@distances = Hash.new
	end

	def addVertex(index,x,y)
		@plane[index] = VertexTSP.new(x,y)
	end

	def rmVertex(index)
		@plane.delete(index)	
	end

	def getVertex(index)
		return @plane[index]
	end

	def calcDistances	
		@plane.each do |key1, v1|
			@plane.each do |key2 ,v2|
				@distances[[key1.to_i,key2.to_i]] = ((Math.sqrt(
					(v2.getCord[0].to_f - v1.getCord[0].to_f)**2 + 
					(v2.getCord[1].to_f - v1.getCord[1].to_f)**2)
													 )+0.5).to_int
			end
		end		
	end

	def getDistance(key1,key2)
		return @distances[[key1,key2]]
	end

	def setKey(index,key)
		@plane[index].setKey(key)
	end

	def getKey(index)
		return @plane[index].getKey
	end

	def setFather(index,father)
		@plane[index].setFather(father)
	end

	def getFather(index)
		return @plane[index].getFather
	end

	def getPlane
		return @plane
	end

	def getDistances
		return @distances
	end

	def calculateCost(path)
		cost = 0
		for i in 0..path.size-1
			if (i!=path.size-1)
				cost+=@distances[[path[i].to_i,
					path[i+1].to_i]]
			end
		end
		return cost
	end
end
