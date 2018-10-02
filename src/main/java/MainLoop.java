import graphics.Renderer;
//import scenes.SceneManager;

public class MainLoop {

    public static final int TILESIZE = 32;

    private static int default_fps = 30; // This is the frames per second the game is designed for. Eg, speed of objects are defined per 1/30 sec.
    private static long default_time = 1000000000/default_fps;

    private static int target_fps = 0; // 0 is no cap
    private static long target_time = (target_fps != 0) ? 1000000000/target_fps : 0;

    public static float deltaTime = 0;



    public static void main(String[] args) {
        init();
        int counter = 0;

        while(true){
            long startTime = System.nanoTime();
            long fps;
            counter++;

            //SceneManager.updateScenes();
            Renderer.render();

            long timeTaken = System.nanoTime() - startTime;

            if(timeTaken < target_time){
                try {
                    Thread.sleep((target_time - timeTaken) / 1000000);
                } catch(InterruptedException e){
                }
            }

            timeTaken = System.nanoTime() - startTime;
            deltaTime = (float)timeTaken / (float)default_time;

            fps = 1000000000/(timeTaken);

            if(counter % 3000 == 0) {
                System.out.println("fps: " + fps);
                System.out.println("deltaTime: " + deltaTime);
            }
        }
    }

    private static void init(){
        Renderer.init();
        //SceneManager.init();
    }
}