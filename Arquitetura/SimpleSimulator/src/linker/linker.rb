require 'scanf'

def subsAddrs(line,addr)
	stringRes = ""
	array = line.scanf("	%s %[^,],%[^,],%[^,]\n")	
	stringRes += "#{addr}	"
	i = -1 
	for x in array
		x = x.delete ' '
		i += 1
		if $dataAddr[x] != nil
			x = "%#{$dataAddr[x]}"
		end
		stringRes += "#{x}"
		if(i==0)
			stringRes += "\t"
		end
		if (i>0 && i<array.length-1)
			stringRes += ","
		end
	end
	return stringRes
end

def calcSize(line)
	array = line.scanf("%s %[^\t\n]")
	if (array[1] =~ /"/)
		size = (array[1].delete "\"").length
		array[1][array[1].length-1,array[1].length-1] = "\\0\""  
		return size,(array[0].delete "."),
				("#{array[1].delete "."}")
	else
		return 1,(array[0].delete "."),(array[1].delete ".")
	end
end

$dataAddr = Hash.new

def calcAddr(codigo)
	textRes = ""
	codigoRes = ""

  	flagData = false
	flagText = false;
	addr = 0
	addrAux = 0;
 	for line in codigo do
		if flagText 
			if (line.chomp <=> "global") == 1
				$dataAddr["globalStart"] = line.scanf("global %s")[0];
			else
				if line[0] == '.'
					$dataAddr[line.chomp.delete '.'] = addrAux
				else
					textRes += line
					addrAux+=1
				end
			end
		end

		if line.chomp == ".text"
			flagData = false
			flagText = true	
		end
	
	        if flagData
			res = calcSize(line)
			$dataAddr[res[1]] = addr
			if(res[2] != nil)
				codigoRes += "#{addr}\t#{res[2].strip}\n"
			end
			addr += res[0]
			addrAux = addr
		end		

		if line.chomp == ".data"
			flagData = true				
		end
		
	end
	
	linhas = textRes.split("\n")
	codigoRes = "#init #{$dataAddr[$dataAddr["globalStart"]]}\n#{codigoRes}" 
	for line in linhas do
		codigoRes += "#{subsAddrs(line,addr)}\n"
		addr += 1
	end
	return codigoRes
end


def readFile(nome)
	return File.readlines(nome)
end

arquivo = ARGV.first
puts "Linkando #{arquivo}."
codigo = readFile(arquivo)
resCodigo =  calcAddr(codigo)
fileN = "#{arquivo}.obj"
File.open(fileN,'w+') do |f| 
	f.write(resCodigo)
end
puts "Done."
