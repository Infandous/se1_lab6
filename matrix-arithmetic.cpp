#include <iostream>
#include <stdlib.h>


#define MAXSIZE 100 //max matrix size

int** read_matrix(); //reads matrices in from matrix_input.txt. Returns 2d array with both square matrices

void print_both(int**); //function to print both matrices

void print(int**); //function to print a single matrix of size x size

int** null_matrix(); //helper func, returns a matrix of size x size where all entries are 0

int** add(int**); //takes two matrices stored in 2d array and returns the result of adding the two together

int** multiply(int**); //takes two matrices and returns the product of them

int** subtract(int**); //takes two matrices and subtracts the second from the first


int size = 0; //global size variable for matrices. Both matrices are size x size 

int main(){

    int** matrices = read_matrix(); //get matrix data

    //print matrices
    print_both(matrices);

    int** addResult = add(matrices);
    std::cout<<"Matrix Sum (A+B)"<<std::endl;
    print(addResult);

    int** multiplyResult = multiply(matrices);
    std::cout<<"Matrix Product (A*B):"<<std::endl;
    print(multiplyResult);

    int** subResult = subtract(matrices);
    std::cout<<"Matrix Difference (A-B):"<<std::endl;
    print(subResult);


    return 0;
}

int** read_matrix(){
    FILE* fp = fopen("matrix_input.txt","r"); //open file matrix_input.txt with read privileges
    if (fp==NULL){
        perror("Error opening file");
        exit(0);
    }

    fscanf(fp, "%d", &size); //read in the size of the matrices
    if (size>MAXSIZE){ //ensure matrix size is less than MAXSIZE
        perror("Matrix size must be less than 100x100");
        exit(0);
    }

    /*
    create pointer to a pointer arr and allocate memory of size 2*size*sizeof(int*)
    2*size because there are two matrices of size x size
    sizeof(int*) because it is the size to store an int pointer
    each position of arr will point to an array of integers that represents a row of the matrix
    */
    int** arr = (int**)malloc(2 * size * sizeof(int*));

    //allocate memory for each row and read in values
    for (int i = 0; i<2*size; i++){ //allocate mem
        arr[i] = (int*)malloc(size*sizeof(int));
        for (int t = 0; t<size; t++){ //read in values
            fscanf(fp,"%d",&arr[i][t]);
        }
    }

    fclose(fp); //close file
    return arr; //return matrices
}

void print_both(int** arr){
    for (int i = 0; i<2*size;i++){ //for each row
         if (i==0){//if the beginning of matrix A
            std::cout<<"Matrix A:"<<std::endl;
        }else if(i==size){ //if beginning of matrix B
            std::cout<<"Matrix B:"<<std::endl;
        }
        for (int t = 0; t<size; t++){ //for each index in the row
            std::cout<<arr[i][t]<<" ";
        }
        printf("\n"); //newline to end row
    }
}

void print(int** arr){
    for (int i = 0; i<size; i++){
        for (int t = 0; t<size; t++){
            std::cout<<arr[i][t]<<" ";
        }
        printf("\n");
    }
}

int** null_matrix(){
    //create matrix of size x size where every position has value 0
    int** matrix = (int**)malloc(size*sizeof(int*)); 
    for (int i = 0; i<size; i++){
        matrix[i] = (int*)malloc(size*sizeof(int)); 
        for (int j = 0; j<size; j++){
            matrix[i][j] = 0;
        } 
    }

    return matrix;
}

int** add(int** arr){

    int** matrix = null_matrix(); //create null matrix to store values of addition

    for (int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            matrix[i][j] = arr[i][j] + arr[i+size][j];
        }
    }

    return matrix;
}

int** multiply(int** arr){
    int** matrix = null_matrix(); //create null matrix to store values of multiplication

    for (int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            for (int t = 0; t<size; t++){ //third loop is necessary because the dot product is calculated in matrix multiplication
                matrix[i][j] += arr[i][t] * arr[t+size][j];
            } 
        }
    }

    return matrix;
}

int** subtract(int** arr){
    int** matrix = null_matrix(); //create null matrix to store values from subtraction

    for (int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            matrix[i][j] = arr[i][j] - arr[i+size][j];
        }
    }

    return matrix;
}
