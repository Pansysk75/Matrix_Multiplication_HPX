# Matrix_Multiplication_HPX
Implemented a Matrix class and a few sequential & parallel functions using HPX.
#

### Sequential Matrix Product:
You can see that CPU utilization is inconsistent.

![image](https://user-images.githubusercontent.com/75637426/163678349-df4020cc-1795-4a18-902a-a9a5712f6c67.png)




### Parallel Matrix Product 1 (Bad Implementation):
Due to bad implementation, memory usage skyrockets. That is because memory is released only when the whole matrix multiplication has been completed. Thus, this implementation is terribly slow.

![image](https://user-images.githubusercontent.com/75637426/163678549-a43d2ce4-9f22-4d42-9e20-a4cada3eb2c8.png)




### Parallel Matrix Product 2 (Good Implementation):
CPU is fully utilized. This implementation runs 2-3 times faster than sequential on my machine.

![image](https://user-images.githubusercontent.com/75637426/163678505-6e126fa2-a792-428c-9c6e-24d1b3fa0733.png)



