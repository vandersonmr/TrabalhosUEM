class FileIO

	def readGraphInFile(inputFile,g)
		file = File.new(inputFile,"r")
		while (line = file.gets)
			processLine(line,g)
		end
		file.close
	end

end

class FileTSP < FileIO

	def processLine(line,g)
		splited = line.split
		g.addVertex(splited[0],splited[1],splited[2])
	end

end

class FileEC < FileIO

	def processLine(line,g)
		splited = line.split
		if (splited[0].eql? "#")
			@edges = true
			return
		end
		if (!@edges)
			g.addVertice(splited[0])
		else
			g.addEdge(splited[0],splited[1]);
			g.addEdge(splited[1],splited[0]);
		end
	end

end
