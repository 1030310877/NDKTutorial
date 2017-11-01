package joe.com.ndktutorial.activity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import joe.com.ndktutorial.R;

/**
 * JNI创建线程
 * Created by joe on 2017/10/27.
 */
public class Tutorial3Activity extends AppCompatActivity {

    private TextView numTv;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_3);
        findViewById(R.id.btn_tutorial_3_start).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startTimerThread();
            }
        });
        findViewById(R.id.btn_tutorial_3_stop).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopTimerThread();
            }
        });
        numTv = (TextView) findViewById(R.id.tv_tutorial_3);
    }

    public void setText(int num) {
        final int temp = num;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                numTv.setText(String.valueOf(temp));
            }
        });
    }

    static {
        System.loadLibrary("tutorial-3");
    }

    private native void startTimerThread();

    private native void stopTimerThread();
}
