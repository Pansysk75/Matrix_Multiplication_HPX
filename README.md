# Matrix_Multiplication_HPX
Implemented a Matrix class and a few sequential &amp; parallel functions using HPX

Due to the implementation of the parallel algorithm, it is expected to run worse when the resulting matrix is too big (ie when m1.rows() * m2.cols() is large).
That happens because the "grain size" is too small, meaning we have split up the computation too much, so the overhead cost surpasses the gain from parallelism.
