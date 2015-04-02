load 'FileIO.rb'
load 'Graph.rb'
load 'algorithms/tspnn.rb'
load 'algorithms/hierholzer.rb'
load 'algorithms/tsp2opt.rb'
load 'algorithms/tspMst.rb'
load 'algorithms/Heap.rb'

def printVertexs(vertexs)
	vertexs.each do |v|
		puts v
	end
end

if("ec"==ARGV[0])

	fileEC = FileEC.new
	graph = Graph.new 
	fileEC.readGraphInFile(ARGV[1],graph)

	eulerian = hierholzer(graph.getGraph)

	printVertexs(eulerian)

else
	fileTSP = FileTSP.new
	plane = CartesianPlane.new
	fileTSP.readGraphInFile(ARGV[1],plane)
	plane.calcDistances
	
	if("tsp-nn"==ARGV[0])
		cost,tspPath = tspnn(plane)
	
	elsif("tsp-mst"==ARGV[0])

		cost,tspPath = tspMst(plane)

	elsif("tsp-nn-2opt"==ARGV[0])
		cost,tspPath = tspnn(plane)
		tspPath = tsp2opt(tspPath,plane)
		cost = plane.calculateCost(tspPath)

	elsif("tsp-mst-2opt"==ARGV[0])
		cost,tspPath = tspMst(plane)
		tspPath = tsp2opt(tspPath,plane)
		cost = plane.calculateCost(tspPath)
	end
	
	puts cost
	printVertexs(tspPath)
end
