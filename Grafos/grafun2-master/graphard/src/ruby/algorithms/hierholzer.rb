def hierholzer(g)
	v = g.first[0]
	s = [v]
	c = []
	while (!s.empty?)	
		u = s.pop
		c.push(u) 
		while (!g[u].getEdges.empty?)
			s.push(u)
			v = g[u].rmEdge(g[u].getEdges.first[0])
			g[v].rmEdge(u);
			u = v
		end
	end
	return c
end
