package graphics.shaders;

import com.jogamp.opengl.GL3;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ShaderLoader {
    public static int loadShaders(GL3 gl, String vertexShaderPath, String fragmentShaderPath){
        // Create shaders
        int vertexShaderID = gl.glCreateShader(gl.GL_VERTEX_SHADER);
        int fragmentShaderID = gl.glCreateShader(gl.GL_FRAGMENT_SHADER);

        // Read vertex shader code from file
        String vertexShaderString = convertShaderToString(vertexShaderPath);

        // Read vertex shader code from file
        String fragmentShaderString = convertShaderToString(fragmentShaderPath);

        // Compile vertex shader
        gl.glShaderSource(vertexShaderID, 1, new String[]{vertexShaderString}, null);
        gl.glCompileShader(vertexShaderID);

        // Compile fragment shader
        gl.glShaderSource(vertexShaderID, 1, new String[]{vertexShaderString}, null);
        gl.glCompileShader(vertexShaderID);

        int shaderProgram = gl.glCreateProgram();
        gl.glAttachShader(shaderProgram, vertexShaderID);
        gl.glAttachShader(shaderProgram, fragmentShaderID);
        gl.glBindAttribLocation(shaderProgram, 0, "in_Position");
        gl.glLinkProgram(shaderProgram);
        gl.glValidateProgram(shaderProgram);


        return shaderProgram;
    }

    private static String convertShaderToString(String shaderName){
        String ls = System.getProperty("line.separator");
        BufferedReader reader;

        try {
            reader = new BufferedReader(new FileReader(shaderName));
            StringBuilder sb = new StringBuilder();

            String line;
            while ((line = reader.readLine()) != null) {
                sb.append(line);
                sb.append(ls);
            }
            return sb.toString();

        } catch(IOException e){
            System.out.println("Failed to read shader from file!\n\tError: " + e);
        }
        return null;
    }
}
