def tsp2opt(t,g)
	while true
		deltaMax  = 0
		best = nil
		n = t.length - 2
		(0..(n-2)).each do |a|
			b = a+1

			if a != 0
				lim = n
			else 
				lim = n - 1
			end

			((a+2)..lim).each do |c|
				if c != n
					d = c + 1
				else
					d = 0
				end


				old_dist = 
					g.getDistance(t[a].to_i,t[b].to_i) 
				+ g.getDistance(t[c].to_i,t[d].to_i)

				new_dist = g.getDistance(t[a].to_i,t[c].to_i)
				+ g.getDistance(t[b].to_i,t[d].to_i)

				delta = old_dist - new_dist


				if delta > deltaMax
					deltaMax = delta
					best = [a,b,c,d]
				end
			end
		end
		if deltaMax != 0
			a,b,c,d = best
			aux = t[b]
			t[b] = t[c]
			t[c] = aux
		else 
			return t
		end
	end
end
