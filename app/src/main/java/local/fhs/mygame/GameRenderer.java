package local.fhs.mygame;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameRenderer implements GLSurfaceView.Renderer {
    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        surfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        drawFrame();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        surfaceCreated();
    }

    private native void surfaceChanged(int width, int height);
    private native void drawFrame();
    private native void surfaceCreated();
}
