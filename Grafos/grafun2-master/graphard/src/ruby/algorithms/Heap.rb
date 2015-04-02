class Heap

	def buildHeap(container)
		((container.size-1)/2).downto(0) do |i|
			heapfy(container,i)
		end
	end

	def heapfy(container,i)
		l = i*2
		r = i*2+1
		index = getIndex(container,i,l,r)
		if (index != i)
			aux = container[i]
			container[i] = container[index]
			container[index] = aux
			heapfy(container,index)
		end
	end

	def extractRoot(container)
		buildHeap(container)
		if (container.size-1 > 0)
			aux = container[0]
			container[0] = container[container.size-1]
			container[container.size-1] = aux
		end
		return container.pop
	end

end

class Heapmax < Heap

	def getIndex(container,i,l,r)
		if (l <= container.size-1) and (container[l] > container[i])
			index = l
		else
			index = i
		end
		if (r <= container.size-1) and (container[r] > container[index])
			index = r
		end
		return index
	end
end


class Heapmin < Heap

	def getIndex(container,i,l,r)
		if (l <= container.size-1) and (container[l] < container[i])
			index = l
		else
			index = i
		end
		if (r <= container.size-1) and (container[r] < container[index])
			index = r
		end
		return index
	end
end
