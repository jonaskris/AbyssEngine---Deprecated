package math;

public class Vector {

    private float[] vector;

    public Vector(float[] values){
        vector = new float[values.length];
        for(int i = 0; i < values.length; i++){
            vector[i] = values[i];
        }
    }

    public Vector(int length){
        vector = new float[length];
    }

    public void set(int i, float value){
        vector[i] = value;
    }

    public float get(int i){
        return vector[i];
    }

    public Vector copy(){
        return new Vector(vector);
    }

    public int size(){
        return vector.length;
    }

    public String toString(){
        StringBuilder returnString = new StringBuilder();
        returnString.append("[");
        for(int i = 0; i < vector.length; i++){
            returnString.append((i == vector.length - 1)?(vector[i] + "]\n"):(vector[i] + ", "));
        }
        return returnString.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof Vector)){
            return false;
        }

        if(((Vector) obj).size() != size()){
            return false;
        }

        for(int i = 0; i < size(); i++){
            if(get(i) != ((Vector) obj).get(i)){
                return false;
            }
        }

        return true;
    }

    public Vector add(Vector that){
        if(that.size() != size()){
            throw new IllegalArgumentException("Values must be the same length as the vector!");
        }
        float[] newVectorValues = new float[size()];
        for(int i = 0; i < newVectorValues.length; i++){
            newVectorValues[i] = this.get(i) + that.get(i);
        }
        return new Vector(newVectorValues);
    }

    public Vector add(float value){
        float[] newVectorValues = new float[size()];
        for(int i = 0; i < newVectorValues.length; i++){
            newVectorValues[i] = this.get(i) + value;
        }
        return new Vector(newVectorValues);
    }

    public Vector multiply(float value){
        float[] newVectorValues = new float[size()];

        for(int i = 0; i < newVectorValues.length; i++){
            newVectorValues[i] = vector[i] * value;
        }

        return new Vector(newVectorValues);
    }

    public float dot(Vector that){
        if(this.size() != that.size()){
            throw new IllegalArgumentException("Two vectors must be the same length to take their dot product!");
        }

        float returnValue = 0;

        for(int i = 0; i < size(); i++){
            returnValue += this.get(i) * that.get(i);
        }

        return returnValue;
    }

    public Vector cross(Vector that){
        if(this.size() != 3 || that.size() != 3){
            throw new IllegalArgumentException("Vector crossproduct is only defined for 3 dimensions");
        }

        return new Vector(new float[]{this.get(1) * that.get(2) - this.get(2) * that.get(1),
                -(this.get(0) * that.get(2) - this.get(2) * that.get(0)),
                this.get(0) * that.get(1) - this.get(1) * that.get(0)});
    }

    public double magnitude(){
        float foo = 0;

        for(int i = 0; i < vector.length; i++){
            foo += vector[i]*vector[i];
        }

        return Math.sqrt(foo);
    }

    public static void main(String[] args) {
        Vector a = new Vector(3);

        a.set(0, 2.0f);
        a.set(1, 1.0f);
        a.set(2, 1.0f);


        Vector b = new Vector(3);
        b.set(0, 4.0f);
        b.set(1, 2.0f);
        b.set(2, 2.0f);

        System.out.println(b.cross(a));
    }

}
