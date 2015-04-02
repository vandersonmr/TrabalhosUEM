import System.IO
import Data.Array.IO
import System.Environment 
import Control.Monad
import Data.Matrix
import Data.List.Split.Internals
import qualified Data.Vector as Vector
import qualified Data.Map as Map
import System.Random

---------- IO -------------------
type Grid       = [[Int]] 
type SudokuGrid = Matrix Int

-- Lê um arquivo em path e preenche o objeto SudokuGrid
readSudoku :: String -> IO SudokuGrid
readSudoku path = do  
                contents <- readFile path
                let contents' = read contents :: Grid 
                return (fromLists contents')

printSudoku :: Maybe SudokuGrid -> IO ()
printSudoku a = putStrLn $ show a

main = do
     args <- getArgs
     sudoku <- readSudoku $ (args !! 0)
     printSudoku $ Just sudoku
     let solvedSudoku = solveSudoku sudoku
     printSudoku solvedSudoku
     let solvedSudoku = solveByInformedSearch sudoku
     printSudoku solvedSudoku
     solved2Sudoku <- solveByGeneticAlgorithm sudoku 
     printSudoku $ Just solved2Sudoku

----------- PSR ----------------

type Index = (Int,Int) -- (x,y)

-- Retorna uma lista com todos os Indexs (Int,Int) que estão com 0, ou seja, 
-- estão vazios. 
getIndexs :: SudokuGrid -> [Index]
getIndexs grid = [(x,y) | x <- [1..n], y <- [1..m], 0 == (getElem x y grid)]
            where 
              n = nrows grid
              m = ncols grid

-- Retorna True se o número number na posição (x,y) segue todas as 3 regras do 
-- Sudoku, que são: - Diferentes números na linha, - Diferentes número na coluna, 
--                  - Diferentes números nos blocos (3x3) 
-- Caso contrario retorna False.
isValid :: Index -> Int -> SudokuGrid -> Bool
isValid idx number grid = (isLineValid idx number grid) && (isColValid idx number grid) && (isBlockValid idx number grid)

lineConflits :: Index -> Int -> SudokuGrid -> Int
lineConflits (x,y) number grid = (Vector.length (Vector.filter (\a -> (a == number)) (getRow x grid)))

isLineValid :: Index -> Int -> SudokuGrid -> Bool
isLineValid idx number grid = (lineConflits idx number grid)  == 0

colConflits :: Index -> Int -> SudokuGrid -> Int
colConflits (x,y) number grid = (Vector.length (Vector.filter (\a -> (a == number)) (getCol y grid))) 

isColValid :: Index -> Int -> SudokuGrid -> Bool
isColValid idx number grid = (colConflits idx number grid) == 0

blockConflits :: Index -> Int -> SudokuGrid -> Int
blockConflits (x,y) number grid = (length (filter (\(x',y') -> number == (getElem x' y' grid)) blockIndexs))
                     where
                        blockX = ((div (x - 1) 3) * 3) + 1
                        blockY = ((div (y - 1) 3) * 3) + 1
                        blockIndexs = [(x',y') | x' <- [blockX..(blockX+2)], y' <- [blockY..(blockY+2)]]

isBlockValid :: Index -> Int -> SudokuGrid -> Bool
isBlockValid idx number grid = (blockConflits idx number grid) == 0

-- Retorna uma lista com todos os números que são válidos para a posição (x,y)
possibleNumbersToPos :: Index -> SudokuGrid -> ((Int,Int) -> Int -> SudokuGrid -> Bool) -> [Int]
possibleNumbersToPos (x,y) grid filt = [z | z <- [1..9], filt (x,y) z grid]

-- Adiciona o número n no grid na posição idx
mark :: Index -> SudokuGrid -> Int -> SudokuGrid
mark idx grid n = (setElem n idx grid)

-- Retorna uma lista com Sudokus com todos os números válidos aplicados na posição (x,y)
mapMark :: Index -> SudokuGrid -> [SudokuGrid]
mapMark idx grid = map (mark idx grid) (possibleNumbersToPos idx grid isValid)

-- Cria e poda a arvore de recursão
findSolution :: [SudokuGrid] -> [Index] -> ([SudokuGrid] -> Index -> [SudokuGrid])-> Maybe SudokuGrid
findSolution []    _  heuristic             = Nothing
findSolution (h:t) [] heuristic             = Just h 
findSolution (h:t) all@((x,y):ls) heuristic = let sol = solve ls h heuristic in
                                    if sol == Nothing 
                                    then findSolution t all heuristic
                                    else sol

solve :: [Index] -> SudokuGrid -> ([SudokuGrid] -> Index -> [SudokuGrid]) -> Maybe SudokuGrid
solve []             grid heuristic = Just grid
solve idxs@((x,y):_) grid heuristic = do
                        guard((length pos) > 0)
                        findSolution pos idxs heuristic
              where 
                pos = heuristic (mapMark (x,y) grid) (x,y)
                                                                       
solveSudoku :: SudokuGrid -> Maybe SudokuGrid
solveSudoku grid = solve (getIndexs grid) grid (\a _ -> a)

--------------- Genetic Algorithm --------------

type Specimens = Map.Map Int (IO SudokuGrid) -- (Cost, DNA)

shuffle :: [a] -> IO [a]
shuffle xs = do
        ar <- newArray n xs
        forM [1..n] $ \i -> do
            j <- randomRIO (i,n)
            vi <- readArray ar i
            vj <- readArray ar j
            writeArray ar j vi
            return vj
  where
    n = length xs
    newArray :: Int -> [a] -> IO (IOArray Int a)
    newArray n xs =  newListArray (1,n) xs

generateASolution :: [Index] -> SudokuGrid -> IO SudokuGrid
generateASolution [] grid      = return grid
generateASolution ((x,y):t) grid = if (getElem x y grid) == 0 
                                   then do 
                                        z <- shuffle (possibleNumbersToPos (x,y) grid isLineValid)
                                        generateASolution t (setElem (head z) (x,y) grid)
                                   else generateASolution t grid

generatePopulation_ :: Int -> SudokuGrid -> [IO SudokuGrid]
generatePopulation_ 1 grid = [generateASolution (getIndexs grid) grid]
generatePopulation_ n grid = do
                            let specimen = generateASolution (getIndexs grid) grid
                            specimen:generatePopulation_ (n-1) grid

generatePopulation :: Int -> SudokuGrid -> IO Specimens
generatePopulation n grid = generateSpecimens n (generatePopulation_ n grid) Map.empty

generateSpecimens :: Int -> [IO SudokuGrid] -> Specimens -> IO Specimens
generateSpecimens 0 _ s = return s
generateSpecimens n (h:t) s = do
                              h' <- h
                              specimens <- generateSpecimens (n-1) t s
                              return (Map.insert (solutionCost h') h specimens)


solutionCost :: SudokuGrid -> Int
solutionCost grid = foldr (\(x,y) acc -> acc + (blockConflits (x,y) (elem x y) grid)) 
                          0 [(x,y) | x <- [1..(nrows grid)], y <- [1..(ncols grid)]]
                   where elem x y = getElem x y grid

copyLine :: Int -> SudokuGrid -> SudokuGrid -> SudokuGrid
copyLine lineN from to = mapRow (\p x -> (getElem lineN p from)) lineN to

sex_ :: SudokuGrid -> SudokuGrid -> SudokuGrid -> Int -> IO SudokuGrid
sex_ _ _ grid3 0         = return grid3
sex_ grid1 grid2 grid3 n = do 
                           ran <- (randomIO :: IO Int)
                           let ranm = mod ran 100
                           child1 <- sex_ grid1 grid2 (copyLine n grid1 grid3) (n-1)
                           child2 <- sex_ grid1 grid2 (copyLine n grid2 grid3) (n-1)
                           if (((solutionCost child1)+ranm) < (ranm+(solutionCost child2)))
                            then return child1
                            else return child2

sex :: SudokuGrid -> SudokuGrid -> IO SudokuGrid
sex grid1 grid2 = sex_ grid1 grid2 (zero (nrows grid1) (ncols grid1)) (nrows grid1)

getParent :: [IO SudokuGrid] -> IO SudokuGrid 
getParent (h:[]) = h 
getParent (h:t)  = do 
                    ran <- (randomIO :: IO Int)
                    let ranm = mod ran 100
                    if (ranm < 10)
                    then h
                    else getParent t 
                    
geneticAlgorithm :: IO Specimens -> IO Specimens
geneticAlgorithm specimens = do
                              spec <- specimens
                              let pop = Map.elems spec
                              mon   <- getParent pop
                              dad   <- getParent pop
                              let child = sex mon dad 
                              c <- child
                              return $ Map.insert (solutionCost c) child spec

runGeneticAlgorithm :: Int -> IO Specimens -> IO Specimens
runGeneticAlgorithm 0 specimens = specimens
runGeneticAlgorithm n specimens = do
                                  runGeneticAlgorithm (n-1) (geneticAlgorithm specimens)

solveByGeneticAlgorithm :: SudokuGrid -> IO SudokuGrid
solveByGeneticAlgorithm a = do
                            let popInit = generatePopulation 5000 a          
                            newPop <- runGeneticAlgorithm 16000 popInit
                            let l = Map.elems newPop
                            best <- head l
                            print $ solutionCost best
                            return best

--------------- Busca Informada ----------------

dist :: Index -> Index -> Int
dist (x,y) (x',y') = abs $ (x - x') + (y - y')

heuristicCost :: Index -> SudokuGrid -> Int
heuristicCost (x,y) grid = let neighbours = [(x',y') | x' <- [1..9], y' <- [1..9], (dist (x',y') (x,y)) == 1] 
                           in (length [(x',y') | (x',y') <- neighbours, not ((getElem x y grid) == (getElem x' y' grid))])

qsort1 :: [SudokuGrid] -> Index -> [SudokuGrid]
qsort1 []     idx = []
qsort1 (p:xs) idx = qsort1 lesser idx ++ [p] ++ qsort1 greater idx
    where
        lesser  = [ y | y <- xs, (heuristicCost idx y) < (heuristicCost idx p) ]
        greater = [ y | y <- xs, (heuristicCost idx y) >= (heuristicCost idx p) ]

heuristic :: [SudokuGrid] -> Index -> [SudokuGrid]
heuristic grids idx = qsort1 grids idx

solveByInformedSearch :: SudokuGrid -> Maybe SudokuGrid
solveByInformedSearch grid = solve (getIndexs grid) grid heuristic

-----------------------------------------------
