package joe.com.ndktutorial.activity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import joe.com.ndktutorial.R;

/**
 * Jni socket通信
 * Created by joe on 2017/11/3.
 */
public class Tutorial5Activity extends AppCompatActivity {

    private TextView receiveTv;
    private EditText contentEdt;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tutorial_5);
        receiveTv = (TextView) findViewById(R.id.tv_tutorial_5);
        contentEdt = (EditText) findViewById(R.id.edt_tutorial_5);

        findViewById(R.id.btn_tutorial_5_1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startServer();
            }
        });
        findViewById(R.id.btn_tutorial_5_2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startClient();
            }
        });

        findViewById(R.id.btn_tutorial_5_3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            }
        });
    }

    private native void startServer();

    private native void startClient();

    private native void sendMsg(String content);

    static {
        System.loadLibrary("tutorial-5");
    }
}
