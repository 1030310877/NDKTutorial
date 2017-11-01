package joe.com.ndktutorial.activity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import joe.com.ndktutorial.R;

/**
 * JNI调用Java层方法
 * Created by joe on 2017/11/1.
 */
public class Tutorial2Activity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_2);
    }

    private void changeText() {

    }

    private static void changeStaticText() {

    }

    static {
        System.loadLibrary("tutorial-2");
    }

    public native void callMethod();

    public native void callStaticMethod();
}
