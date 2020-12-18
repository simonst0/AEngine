package local.fhs.mygame;

import android.app.Application;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.graphics.Color;
import android.view.WindowManager;
import android.widget.TextView;
import android.app.Activity;
import android.media.SoundPool;
import android.media.AudioManager;
import java.io.IOException;

public class MainActivity extends Activity {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    public void onBackPressed()
    {
        nativeOnBackPressed();
        super.onBackPressed();
    }

    private SoundPool mSoundPool = null;
    private TextView mDebugText = null;

    @Override
    protected void onPause() {
        nativePause();
        super.onPause();
    }

    @Override
    protected void onResume() {
        nativeResume();
        super.onResume();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        GLSurfaceView surfaceView = new GLSurfaceView(this);

        mSoundPool = new SoundPool(16, AudioManager.STREAM_MUSIC, 0);

        // Damit weiß der Loader, wo er sich die Assets holen soll.
        // Achtung: Eigentlich müsste man beim onDestroy() den
        // AssetManager vom Loader auf null setzen, damit nichts leakt.
        Loader.setAssetManager(getAssets());

        // Die folgende Zeile ist wichtig, damit ein ES2-Kontext erstellt
        // wird, anderenfalls wird ein ES1-Kontext erstellt.
        surfaceView.setEGLContextClientVersion(2);

        surfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent e) {
                int action = e.getActionMasked();

                /* Translate ACTION_POINTER_{UP,DOWN} to ACTION_{UP,DOWN} */
                if (action == MotionEvent.ACTION_POINTER_DOWN) {
                    action = MotionEvent.ACTION_DOWN;
                } else if (action == MotionEvent.ACTION_POINTER_UP) {
                    action = MotionEvent.ACTION_UP;
                }

                /* Down and up events are for a single touch point */
                if (action == MotionEvent.ACTION_DOWN ||
                        action == MotionEvent.ACTION_UP ||
                        action == MotionEvent.ACTION_CANCEL) {
                    int i = e.getActionIndex();
                    nativeTouch(action, e.getX(i), e.getY(i), e.getPointerId(i));
                    return true;
                }

                /* Motion events are batched, send an update for all points */
                if (action == MotionEvent.ACTION_MOVE) {
                    for (int i=0; i<e.getPointerCount(); i++) {
                        nativeTouch(action, e.getX(i), e.getY(i), e.getPointerId(i));
                    }
                    return true;
                }

                return true;
            }
        });

        SensorManager sensorManager = getSystemService(SensorManager.class);
        Sensor accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        // Wie in der Vorlesung erwähnt, muss man das register im onResume() und im onPause()
        // ein unregister machen, ansonsten läuft der Sensor auch im Hintergrund weiter.
        sensorManager.registerListener(new SensorEventListener() {
            @Override
            public void onSensorChanged(SensorEvent sensorEvent) {
                nativeAccelerometer(sensorEvent.values[0], sensorEvent.values[1], sensorEvent.values[2]);
            }

            @Override
            public void onAccuracyChanged(Sensor sensor, int i) {

            }
        }, accelerometer, SensorManager.SENSOR_DELAY_GAME);

        surfaceView.setRenderer(new GameRenderer());
        setContentView(surfaceView);

        mDebugText = new TextView(this);
        mDebugText.setTextColor(Color.WHITE);
        addContentView(mDebugText, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
                                                                     ViewGroup.LayoutParams.WRAP_CONTENT));

        nativeInit();
    }

    @Override
    protected void onDestroy() {
        nativeDestroy();
        super.onDestroy();
    }

    public void setDebugText(String debugText) {
        final String text = debugText;
        mDebugText.post(new Runnable() {
            @Override
            public void run() {
                mDebugText.setText(text);
            }
        });
    }

    public int loadSound(String filename) {
        try {
            return mSoundPool.load(getAssets().openFd(filename), 1);
        } catch (IOException ioe) {
            return -1;
        }
    }

    public void playSound(int sound) {
        mSoundPool.play(sound, 1.f, 1.f, 0, 0, 1.f);
    }

    // Das ist hier, damit wir eine Referenz auf "this" bekommen (für SoundPool)
    private native void nativeInit();

    // Und hier, damit wir die Referenz wieder frei bekommen
    private native void nativeDestroy();

    private native void nativeResume();

    private native void nativePause();

    private native void nativeTouch(int event, float x, float y, int finger);

    // Auch wieder nur ein Beispiel, ihr könnt gerne auch anderen Sensoren verwenden.
    private native void nativeAccelerometer(float x, float y, float z);

    private native void nativeOnBackPressed();
}
