package joe.com.ndktutorial.activity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import joe.com.ndktutorial.R;

/**
 * JNI调用Java层方法
 * Created by joe on 2017/11/1.
 */
public class Tutorial2Activity extends AppCompatActivity {
    private static TextView textView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_2);
        textView = (TextView) findViewById(R.id.tv_tutorial_2);
        findViewById(R.id.btn_tutorial_2_1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                callMethod();
            }
        });
        findViewById(R.id.btn_tutorial_2_2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                callStaticMethod();
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        textView = null;
    }

    private void changeText() {
        textView.setText("JNI调用了非静态方法");
    }

    private static void changeStaticText() {
        textView.setText("JNI调用了静态方法");
    }

    static {
        System.loadLibrary("tutorial-2");
    }

    public native void callMethod();

    public native void callStaticMethod();
}
