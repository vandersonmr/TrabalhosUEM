def getClosest(u,g)
	smaller = -1;
	smallerDist = 0;

	g.getPlane.each do |key, v|

		aux = g.getDistance(u.to_i,key.to_i)

		if(aux>0 and smallerDist > aux or -1 == smaller)
			smaller = key
			smallerDist = aux	
		end
	end

	return smaller,smallerDist
end

def tspnn(graph)
	g = Marshal.load(Marshal.dump(graph))
	v0 = g.getPlane.first[0]
	c = [v0]
	v = v0
	cost = 0;

	while g.getPlane.length != 1

		g.rmVertex(v)	
		u,distance = getClosest(v,g) 	
		cost += distance
		c.push(u)
		v = u

	end

	cost += g.getDistance(v.to_i,v0.to_i)
	c.push(v0)

	return cost,c
end
