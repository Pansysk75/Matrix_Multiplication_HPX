# Matrix_Multiplication_HPX
Implemented a Matrix class and a few sequential &amp; parallel functions using HPX
(NOT MEANT TO BE PERFORMANT)

Due to the implementation of the parallel algorithm, it sometimes performs worse than the sequential version 
(specifically when m1.rows() * m2.cols() is large, the "grain size" gets smaller than needed, resulting in too much overhead).
