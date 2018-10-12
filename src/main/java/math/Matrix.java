package math;

public class Matrix {

    private float[][] matrix;

    public Matrix(float[][] values){
        int width = values[0].length;
        for(int i = 1; i < values.length; i++){
            if(values[i] == null){
                throw new IllegalArgumentException("No rows can be null!");
            } else if(values[i].length != width){
                throw new IllegalArgumentException("All rows must be of equal width!");
            }
        }

        matrix = new float[values.length][values[0].length];

        for(int i = 0; i < values.length; i++){
            for(int j = 0; j < values[0].length; j++){
                matrix[i][j] = values[i][j];
            }
        }
    }

    public Matrix(int width, int height){
        matrix = new float[height][width];
    }

    public void setRow(int i, Vector vector){
        if(vector.size() != matrix[i].length){
            throw new IllegalArgumentException("Argument vector must be same size as width of matrix!");
        }
        for(int j = 0; j < vector.size(); j++){
            matrix[i][j] = vector.get(j);
        }
    }

    public void setColumn(int i, Vector vector){
        if(vector.size() != matrix.length){
           throw new IllegalArgumentException("Argument vector must be same size as height of matrix!");
        }
        for(int j = 0; j < vector.size(); j++){
            matrix[j][i] = vector.get(j);
        }
    }

    public void set(int column, int row, float value){
        matrix[row][column] = value;
    }

    public Vector getRow(int i){
        return new Vector(matrix[i]);
    }

    public Vector getColumn(int i){
        float[] values = new float[matrix.length];
        for(int j = 0; j < matrix.length; j++){
            values[j] = matrix[j][i];
        }

        return new Vector(values);
    }

    public float get(int column, int row){
        return matrix[row][column];
    }

    public Matrix copy(){
        return new Matrix(matrix);
    }

    public int[] size(){
        return new int[]{matrix[0].length, matrix.length};
    }

    public String toString(){
        StringBuilder returnString = new StringBuilder();
        returnString.append("{");
        for(int i = 0; i < matrix.length; i++){
            returnString.append("[");
            for(int j = 0; j < matrix[i].length; j++){
                returnString.append(matrix[i][j] + (
                        (j == matrix[i].length - 1) ?
                                ((i == matrix.length - 1) ? ("]}\n") : ("],\n")) :
                                (", ")));
            }
        }
        return returnString.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof Matrix)){
            return false;
        }
        int[] objSize = ((Matrix) obj).size();
        int[] thisSize = size();
        if(objSize[0] != thisSize[0] || objSize[1] != thisSize[1]){
            return false;
        }

        for(int i = 0; i < matrix.length; i++){
            for(int j = 0; j < matrix[i].length; j++){
                if(get(j, i) != ((Matrix) obj).get(j, i)){
                    return false;
                }
            }
        }

        return true;
    }

    public Matrix multiply(float value){
        float[][] newMatrixValues = new float[matrix.length][matrix[0].length];

        for(int i = 0; i < newMatrixValues.length; i++){
            for(int j = 0; j < newMatrixValues[0].length; j++){
                newMatrixValues[i][j] = matrix[i][j] * value;
            }
        }

        return new Matrix(newMatrixValues);
    }

    public Matrix dot(Matrix that){ // Todo
        return null;
    }

    public Matrix cross(Matrix that){ // Todo
        return null;
    }

    public float determinant(){
        int[] size = size();
        if(size[0] != size[1]){
            throw new IllegalArgumentException("A matrix must be quadratic to calculate the determinant!");
        }

        if(size[0] == 2){
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        } else if(size[0] == 3){
            return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
                    - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
                    + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        } else{
            throw new IllegalArgumentException("The way to find the determinant of a " + size[0] + ", " + size[1] + " matrix is not programmed!");
        }
    }

    public static void main(String[] args) {
        /*Matrix a = new Matrix(4, 3);

        a.set(0, 0, 1.0f);
        a.set(1, 0, 2.0f);
        a.set(2, 0, 3.0f);
        a.set(3, 0, 4.0f);

        a.set(0, 1, 5.0f);
        a.set(1, 1, 6.0f);
        a.set(2, 1, 7.0f);
        a.set(3, 1, 8.0f);

        a.set(0, 2, 9.0f);
        a.set(1, 2, 10.0f);
        a.set(2, 2, 11.0f);
        a.set(3, 2, 12.0f);*/
    }
}
